#include "icon.h"

Icon::Icon(uint8_t *shape, unsigned int width, unsigned int height): shape(shape), height(height), width(width){
    
}

const Icon small_heart = Icon(heart_icon13w15h, 13, 15);

const Icon large_heart = Icon(heart_icon25w23h, 25, 23);

const Icon small_circle = Icon(circle_19px, 19, 19);

const Icon large_circle = Icon(circle_25px, 25, 25);

const Icon large_um_u = Icon(ultimaker_U_icon25w23h, 25, 23);

const Icon large_makerbot_m = Icon(makerbot_M_icon25w23h, 25, 23);
