#ifndef _X86_DISPLAY_H_
#define _X86_DISPLAY_H_

#include <stdint.h>
#include "gfxfont.h"

class X86Display{
public:
    X86Display();

    void drawPixelRGB565(int16_t x, int16_t y, uint16_t color);
    void drawPixel(int16_t x, int16_t y, uint16_t color);
    void clearDisplay(void);
    void setCursor(int16_t x, int16_t y);
    void print(const char str[]);
    void print(int n);
    void setTextColor(uint16_t c);
    void setFont(const GFXfont *f);

private:
};
#endif