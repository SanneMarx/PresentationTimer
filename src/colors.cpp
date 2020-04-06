#include "colors.h"

uint16_t toColor565(const uint8_t rgb[3]) {
  return ((rgb[0] & 0xF8) << 8) | ((rgb[1] & 0xFC) << 3) | (rgb[2] >> 3);
}

void interpColors(const uint8_t color_1[3], const uint8_t color_2[3], float ratio, uint8_t result[3]){
    for (uint rgb = 0; rgb < 3; rgb ++){
        result[rgb] = color_1[rgb] * ratio + color_2[rgb] * (1.0f - ratio);
    }
}

void interpColors(const uint16_t color_1, const uint16_t color_2, float ratio, uint16_t &result){
    result = (uint16_t)((color_1 & 0xF800) * ratio + (color_2 & 0xF800) * (1.0-ratio)) & 0xF800 | (uint16_t)((color_1 & 0x7E0) * ratio + (color_2 & 0x7E0) * (1.0-ratio)) & 0x7E0 | (uint16_t)((color_1 & 0x1F) * ratio + (color_2 & 0x1F) * (1.0-ratio)) & 0x1F;
}

void randomBaseColor(uint8_t result[3]){
    int roll = random(0, 7);
    for (unsigned int i = 0; i<3; i++){
        switch (roll)
        {
        case 0: result[i] = RED[i];
            break;
        case 1: result[i] = GREEN[i];
            break;
        case 2: result[i] = BLUE[i];
            break;
        case 3: result[i] = WHITE[i];
            break;
        case 4: result[i] = YELLOW[i];
            break;
        case 5: result[i] = MAGENTA[i];
            break;
        case 6: result[i] = CYAN[i];
            break;
        default: result[i] = 0;
            break;
        }
    }
}

void printColor(uint8_t color[3]){
    Serial.print("RGB color: ");
    Serial.print(color[0]);
    Serial.print(" ");
    Serial.print(color[1]);
    Serial.print(" ");
    Serial.println(color[2]);
}
