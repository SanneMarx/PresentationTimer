#include <Ticker.h>
#include <PxMatrix.h>
#include <Fonts/FreeSansBold12pt7b.h>

#include "colors.h"
#include "time_writer.h"

Ticker display_ticker;

// Pins for LED MATRIX
#define P_LAT 16
#define P_A 5
#define P_B 4
#define P_C 15
#define P_OE 2
#define P_D 12
#define P_E 0

PxMATRIX display(64, 32, P_LAT, P_OE, P_A, P_B, P_C, P_D);
TimeWriter time_writer = TimeWriter();

const int on_time = 20; // determines brightness, between 10-100
const int scan_lines = 16;

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

void setup()
{
    Serial.begin(9600);
    display.begin(scan_lines);
    display.clearDisplay();
    display_ticker.attach(0.002, display_updater);
    yield();
    delay(500);
    remaining_time_s = initial_time;
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

    time_writer.printDoubleDigitNumberAt(display, time_m, 2, 25);
    drawAndUpdateColonAt(29, 23);
    time_writer.printDoubleDigitNumberAt(display, time_s, 35, 25);
}

void loop()
{
    display.clearDisplay();
    int minutes, seconds;
    secondsToMinutesAndSeconds(remaining_time_s, minutes, seconds);
    uint8_t interp_color[3];
    interp_colors(GREEN, RED, float(remaining_time_s) / float(initial_time), interp_color);
    if (draw_time) {
        writeMinutesSeconds(minutes, seconds, to_color565(interp_color));
    }
    // Flash the time while in dwell time
    if (remaining_time_s <= 0) {
        draw_time = !draw_time;
    }
    if (remaining_time_s > 0) {
        remaining_time_s -= 1;
    }
    
    delay(1000);
}