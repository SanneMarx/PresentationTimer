#include <Ticker.h>
#include <PxMatrix.h>
#include "time_displayer.h"

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
TimeDisplayer time_displayer(display);

const int on_time = 20; // determines brightness, between 10-100
const int scan_lines = 16;

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
  time_displayer.setInitialDuration(11 * 60);
  time_displayer.setVisible(true);
  time_displayer.start();
}

void loop()
{
  //display.setCursor(29, 21);
  //display.print(":");
}