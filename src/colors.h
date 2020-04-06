#ifndef _COLORS_H_
#define _COLORS_H_

#include <Arduino.h>

uint16_t toColor565(const uint8_t rgb[3]);

void interpColors(const uint8_t color_1[3], const uint8_t color_2[3], float ratio, uint8_t result[3]);
void interpColors(const uint16_t color_1, const uint16_t color_2, float ratio, uint16_t &result);

void randomBaseColor(uint8_t result[3]);

void printColor(uint8_t color[3]);

// Set minimum RGB value to 1 instead so they are always on. Turning on/off a subpixel looks very jarring
const uint8_t RED[3] = {255, 1, 1};
const uint8_t GREEN[3] = {1, 255, 1};
const uint8_t BLUE[3] = {1, 1, 255};
const uint8_t WHITE[3] = {255, 255, 255};
const uint8_t YELLOW[3] = {255, 255, 1};
const uint8_t CYAN[3] = {1, 255, 255};
const uint8_t MAGENTA[3] = {255, 1, 255};

#endif