#include "eyes.h"

Eyes::Eyes(PxMATRIX* display_pointer): InteractableScreen(display_pointer){
    eye_icon = get_new_eye_icon();
    for (unsigned int i=0; i <3; i++){
        last_color[i] = RED[i];
        interped_color[i] = RED[i];
    }
    randomBaseColor(next_color);
    randomBaseColor(next_next_color);
    eyes_start_millis = millis();
}

const Icon* Eyes::get_new_eye_icon(){
    active_eye++;
    if (active_eye >= NUM_EYES){
        active_eye = 0;
    } 
    return eye_icons[active_eye];
}

void Eyes::handleBecameActive(){
    eyes_start_millis = millis();
    drawIconEyes();
}

void Eyes::handlePlayPauze(){
    color_type = (color_type == BREATHING) ? RAINBOW : BREATHING;
    color_transition_millis = (color_type == BREATHING) ? 5000 : 1000;
}

void Eyes::handleReset(){
    display->clearDisplay();
    eye_icon = get_new_eye_icon();
}

void Eyes::setNewTargetColor(){
    for (unsigned int i=0; i <3; i++){
            last_color[i] = next_color[i];
            next_color[i] = next_next_color[i];
        }
    randomBaseColor(next_next_color);
    eyes_start_millis = millis();
}

void Eyes::update(){
    unsigned long millis_in_transition = millis() - eyes_start_millis;
    if (millis_in_transition > color_transition_millis){
        setNewTargetColor();
        millis_in_transition = 0;
    }
    transition_ratio = float(millis_in_transition) / float(color_transition_millis);
    interpColors(next_color, last_color, transition_ratio, interped_color);
    drawIconEyes();
}

void Eyes::drawIconEyes()
{
    uint16_t draw_color = toColor565(interped_color);
    int x_offset = ((max_eye_size - xy_margin) - eye_icon->width) / 2 + xy_margin; // icon must have odd width/ height for this to be correct
    int x_offset_2 = x_offset + max_eye_size - xy_margin;
    int y_offset = ((max_eye_size - xy_margin) - eye_icon->height) / 2 + xy_margin;
    for (int yy=0; yy<eye_icon->height;yy++){
        if (color_type == RAINBOW){
            float color_ratio = (yy/(eye_icon->height - 1.0) + transition_ratio);
            if (color_ratio > 1.0f){
                interpColors(next_next_color, next_color, color_ratio - 1.0f, interped_color);
            } else {
                interpColors(next_color, last_color, color_ratio, interped_color);
            }
            draw_color = toColor565(interped_color);
        }
        for (int xx=0; xx<eye_icon->width;xx++){
            // draw on 2 places at once
            if (eye_icon->shape[xx + yy*eye_icon->width]){
                display->drawPixel(xx+x_offset,yy+y_offset, draw_color);
                display->drawPixel(xx+x_offset_2,yy+y_offset, draw_color);
            }
        }
    }
}
