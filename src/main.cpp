#include <Ticker.h>
#include <PxMatrix.h>
#include <Fonts/FreeSansBold12pt7b.h>

#include "colors.h"
#include "timer.h"

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

PxMATRIX display(64, 32, P_LAT, P_OE, P_A, P_B, P_C, P_D);
Timer timer = Timer();

const int on_time = 5; // determines brightness, between 10-100
const int scan_lines = 16;

enum CLOCK_STATE {RUNNING, PAUZE};
CLOCK_STATE clock_state = PAUZE;

bool play_pauze_pressed = false;
bool play_pauze_pressed_prev = false;
bool reset_pressed = false;
bool reset_pressed_prev = false;

unsigned long clock_start_millis = 0;
int last_display_seconds = 0;
const int presenter_time_limit_s = 9 * 60;
const unsigned int speed_mult = 1; // 1 for normal speed, >1 for speeding up the countdown for testing

int remaining_time_s = 0;

bool draw_colon = true;
bool draw_time = true;
const bool flash_colon = false;

int initial_time = 9 * 60;

// ISR for display refresh
void display_updater()
{
    display.display(on_time);
}

void drawAndUpdateColonAt(int x, int y)
{
    display.setCursor(x, y);
    if (draw_colon)
    {
        display.print(":");
    }
    if (flash_colon){
        draw_colon = !draw_colon;
    }
}

void secondsToMinutesAndSeconds(int total_seconds, int &minutes, int &seconds)
{
    minutes = total_seconds / 60;
    seconds = total_seconds - minutes * 60;
}

void writeMinutesSeconds(int time_m, int time_s, uint16_t color)
{
    display.setTextColor(color);
    display.setFont(&FreeSansBold12pt7b);

    timer.printDoubleDigitNumberAt(time_m, 2, 25);
    drawAndUpdateColonAt(29, 23);
    timer.printDoubleDigitNumberAt(time_s, 35, 25);
}

void drawTimeFromSeconds(int input_seconds){
    Serial.print("drawing time: ");
    Serial.print(input_seconds);
    Serial.println("s");
    display.clearDisplay();
    int minutes, seconds;
    int display_time = (input_seconds > 0) ? input_seconds : 0;
    secondsToMinutesAndSeconds(display_time, minutes, seconds);
    uint8_t interp_color[3];
    interp_colors(GREEN, RED, float(display_time) / float(initial_time), interp_color);
    if (draw_time) {
        writeMinutesSeconds(minutes, seconds, to_color565(interp_color));
    }
    // Flash the time on/off when time ran out
    if (input_seconds <= 0) {
        draw_time = !draw_time;
    }
}

void resetClock(){
    clock_start_millis = millis();
    last_display_seconds = presenter_time_limit_s;
    draw_time = true;
    drawTimeFromSeconds(last_display_seconds);
}

void handlePlayPauzePressed(){
    switch(clock_state){
        case RUNNING:
            clock_state = PAUZE;
            break;
        case PAUZE:
            // Change the start millis so that when the clock continues running, it has the same time as when it last updated (-750ms so it feels responsive)
            clock_start_millis = millis() - (presenter_time_limit_s - last_display_seconds) * 1000 - 750;
            clock_state = RUNNING;
            break;
        default:
            break;
    }
}

void handleInputs(){
    // Reverse press logic since pins are pull-up
    play_pauze_pressed = !digitalRead(P_PLAYPAUZE);
    reset_pressed = !digitalRead(P_RESET);
    if (play_pauze_pressed && !play_pauze_pressed_prev){
        handlePlayPauzePressed();
    }
    if (reset_pressed && !reset_pressed_prev){
        resetClock();
    }
    play_pauze_pressed_prev = play_pauze_pressed;
    reset_pressed_prev = reset_pressed;
}



void handle_running(){
    unsigned int s_timer_on = ((millis() - clock_start_millis) * speed_mult) / 1000;
    int time_to_display = presenter_time_limit_s - s_timer_on;
    if (time_to_display != last_display_seconds){
        last_display_seconds = time_to_display;
        drawTimeFromSeconds(last_display_seconds);
    }
}

void handle_pauze(){

}


void loop()
{
    handleInputs();   
    switch(clock_state){
        case PAUZE:
            handle_pauze();
            break;
        case RUNNING:
            handle_running();
            break;
    }
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
    timer.setDisplay(&display);
    resetClock();
}