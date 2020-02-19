#include <Arduino.h>

inline uint16_t to_color565(uint8_t rgb[3]) {
  return ((rgb[0] & 0xF8) << 8) | ((rgb[1] & 0xFC) << 3) | (rgb[2] >> 3);
}

void interp_colors(const uint8_t color_1[3], const uint8_t color_2[3], float ratio, uint8_t result[3]){
    for (uint rgb = 0; rgb < 3; rgb ++){
        result[rgb] = color_1[rgb] * ratio + color_2[rgb] * (1.0f - ratio);
    }
}

const uint8_t RED[3] = {255, 0, 0};
const uint8_t GREEN[3] = {0, 255, 0};

/**
uint16_t RED = to_color565(255, 0, 0);
uint16_t GREEN = to_color565(0, 255, 0);
uint16_t BLUE = to_color565(0, 0, 255);
uint16_t WHITE = to_color565(255, 255, 255);
uint16_t YELLOW = to_color565(255, 255, 0);
uint16_t CYAN = to_color565(0, 255, 255);
uint16_t MAGENTA = to_color565(255, 0, 255);
uint16_t BLACK = to_color565(0, 0, 0);
**/
