#include "eyes.h"

Eyes::Eyes(PxMATRIX* display_pointer): InteractableScreen(display_pointer){
    for (unsigned int i=0; i <3; i++){
        last_color[i] = RED[i];
        interped_color[i] = RED[i];
    }
    randomBaseColor(next_color);
    eyes_start_millis = millis();
}

void Eyes::handleBecameActive(){
    eyes_start_millis = millis();
    drawCircleEyes();
}

void Eyes::handlePlayPauze(){

}

void Eyes::handleReset(){
    display->clearDisplay();
    eye_type = (eye_type == CIRCLE) ? HEART : CIRCLE;
}

void Eyes::setNewTargetColor(){
    for (unsigned int i=0; i <3; i++){
            last_color[i] = next_color[i];
        }
    randomBaseColor(next_color);
    eyes_start_millis = millis();
}

void Eyes::update(){
    unsigned long millis_in_transition = millis() - eyes_start_millis;
    if (millis_in_transition > color_transition_millis){
        setNewTargetColor();
        millis_in_transition = 0;
    }
    float transition_ratio = float(millis_in_transition) / float(color_transition_millis);
    interpColors(next_color, last_color, transition_ratio, interped_color);
    if (eye_type == CIRCLE){
        drawCircleEyes();
    } else {
        drawHeartEyes();
    }
}

void Eyes::drawCircleEyes(){
    for (int yy=0; yy<19;yy++){
        for (int xx=0; xx<19;xx++){
            // draw on 2 places at once
            if (circle_19px[xx + yy*19]){
                display->drawPixel(xx+8,yy+8, toColor565(interped_color));
                display->drawPixel(xx+37,yy+8, toColor565(interped_color));
            }
        }
    }
}

void Eyes::drawHeartEyes()
{
    for (int yy=0; yy<23;yy++){
        for (int xx=0; xx<25;xx++){
            // draw on 2 places at once
            if (heart_icon25w23h[xx + yy*25]){
                display->drawPixel(xx+5,yy+6, toColor565(interped_color));
                display->drawPixel(xx+34,yy+6, toColor565(interped_color));
            }
        }
    }
}