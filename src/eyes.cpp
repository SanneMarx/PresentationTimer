#include "eyes.h"
#include "colors.h"

Eyes::Eyes(PxMATRIX* display_pointer):display(display_pointer){
    for (unsigned int i=0; i <3; i++){
        last_color[i] = RED[i];
        interped_color[i] = RED[i];
    }
    randomBaseColor(next_color);
    eyes_start_millis = millis();
}

void Eyes::startEyesAnimation(){
    eyes_start_millis = millis();
}

void Eyes::update(){
    unsigned long millis_in_transition = millis() - eyes_start_millis;
    if (millis_in_transition > color_transition_millis){
        for (unsigned int i=0; i <3; i++){
            last_color[i] = next_color[i];
        }
        randomBaseColor(next_color);
        Serial.print("Rolled new ");
        printColor(next_color);
        eyes_start_millis = millis();
        millis_in_transition = 0;
    }
    float transition_ratio = float(millis_in_transition) / float(color_transition_millis);
    if (transition_ratio < 0.1){
        transition_ratio = 0.0;
    }
    interpColors(next_color, last_color, transition_ratio, interped_color);
    drawHeartEyes();
}

void Eyes::drawHeartEyes()
{
    for (int yy=0; yy<23;yy++){
        for (int xx=0; xx<25;xx++){
            // draw on 2 places at once
            if (heart_icon25w23h[xx + yy*25]){
                display->drawPixel(xx+5,yy+5, toColor565(interped_color));
                display->drawPixel(xx+34,yy+5, toColor565(interped_color));
            }
        }
    }
}