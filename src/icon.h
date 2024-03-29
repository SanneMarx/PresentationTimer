#ifndef _ICONS_H_
#define _ICONS_H_

#include "icon_maps.h"

struct Icon {
    Icon(uint8_t *shape, unsigned int width, unsigned int height);

    uint8_t *shape;
    unsigned int width;
    unsigned int height;
};

extern const Icon small_heart;
extern const Icon large_heart;
extern const Icon small_circle;
extern const Icon large_circle;
extern const Icon large_um_u;
extern const Icon large_makerbot_m;

#endif