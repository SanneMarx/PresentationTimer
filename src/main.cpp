#include <Ticker.h>
#include <PxMatrix.h>

#include "interactableScreen.h"
#include "timer.h"
#include "eyes.h"

Ticker display_ticker;

// Pins for LED MATRIX
#define P_LAT 16
#define P_A 5
#define P_B 4
#define P_C 15
#define P_OE 2
#define P_D 12
#define P_PLAYPAUZE 10
#define P_RESET 0

enum MODE {TIMER, EYES};

PxMATRIX display(64, 32, P_LAT, P_OE, P_A, P_B, P_C, P_D);
Timer timer = Timer(&display);
Eyes eyes = Eyes(&display);
MODE mode = EYES;
InteractableScreen* active_screen = &eyes;

const int on_time = 5; // determines brightness, between 0-100
const int scan_lines = 16;

bool play_pauze_pressed = false;
bool play_pauze_pressed_prev = false;
bool reset_pressed = false;
bool reset_pressed_prev = false;

// ISR for display refresh
void display_updater()
{
    display.display(on_time);
}

void switchDisplayMode(){
    mode = (mode == EYES) ? TIMER : EYES;
    active_screen = (mode == EYES) ? (InteractableScreen*)&eyes : (InteractableScreen*)&timer;
    display.clearDisplay();
    active_screen->handleBecameActive();
}

void handleInputs(){
    // Reverse press logic since pins are pull-up
    play_pauze_pressed = !digitalRead(P_PLAYPAUZE);
    reset_pressed = !digitalRead(P_RESET);
    if (play_pauze_pressed && reset_pressed && (!play_pauze_pressed_prev || !reset_pressed_prev)) {
        switchDisplayMode();
    } else {
        if (play_pauze_pressed && !play_pauze_pressed_prev){
            active_screen->handlePlayPauze();
        }
        if (reset_pressed && !reset_pressed_prev){
            active_screen->handleReset();
        }
    }
    play_pauze_pressed_prev = play_pauze_pressed;
    reset_pressed_prev = reset_pressed;
}


void loop()
{
    handleInputs();
    active_screen->update();
    delay(1); // delaying helps with less twitchy inputs
}

void setup()
{
    pinMode(P_PLAYPAUZE, INPUT);
    pinMode(P_RESET, INPUT);
    Serial.begin(9600);
    display.begin(scan_lines);
    display.clearDisplay();
    display_ticker.attach(0.002, display_updater);
    yield();
    delay(500);
    active_screen->handleBecameActive();
}