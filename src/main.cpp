#include <Ticker.h>
#include <PxMatrix.h>
#include <Fonts/FreeSansBold12pt7b.h>

#include "colors.h"

Ticker display_ticker;

// Pins for LED MATRIX
#define P_LAT 16
#define P_A 5
#define P_B 4
#define P_C 15
#define P_OE 2
#define P_D 12
#define P_E 0

PxMATRIX display(64,32,P_LAT, P_OE,P_A,P_B,P_C,P_D);



const int on_time = 20; // determines brightness, between 10-100
const int scan_lines = 16;

int remaining_time_s = 0;
int initial_time_s = 7*60;

bool draw_colon = true;
// ISR for display refresh
void display_updater()
{
  display.display(on_time);
}

void setup() {
  Serial.begin(9600);
  display.begin(scan_lines);
  display.clearDisplay();
  display_ticker.attach(0.002, display_updater);
  yield();
  delay(500);
  remaining_time_s = initial_time_s;
}

void printDoubleDigitNumberAt(int num, int x, int y){
  display.setCursor(x, y);
  if (num < 10){
    display.print("0");
  }
  display.print(num);
}

void drawAndUpdateColonAt(int x, int y){
  display.setCursor(x, y);
  if (draw_colon) {
    display.print(":");
  }
  draw_colon = ! draw_colon;
}

void secondsToMinutesAndSeconds(int total_seconds, int& minutes, int& seconds){
  minutes = total_seconds / 60;
  seconds = total_seconds - minutes * 60;
}

void writeMinutesSeconds(int time_m, int time_s, uint16_t color) {
  display.setTextColor(color);
  display.setFont(&FreeSansBold12pt7b);

  printDoubleDigitNumberAt(time_m, 1, 23);
  drawAndUpdateColonAt(29, 21);
  printDoubleDigitNumberAt(time_s, 36, 23);
}


void loop() {
  display.clearDisplay();
  int minutes, seconds;
  secondsToMinutesAndSeconds(remaining_time_s, minutes, seconds);
  uint8_t interp_color[3];
  interp_colors(GREEN, RED, float(remaining_time_s) / float(initial_time_s), interp_color);
  writeMinutesSeconds(minutes, seconds, to_color565(interp_color));

  if (remaining_time_s > 0) {
    remaining_time_s -= 1;
  } else {
    remaining_time_s = initial_time_s;
  }
  delay(1000);
}