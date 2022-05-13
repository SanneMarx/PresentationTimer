#include "nyan_screen.h"

NyanScreen::NyanScreen(Display* display_pointer): InteractableScreen(display_pointer){
}


void NyanScreen::handleBecameActive(){
    display->clearDisplay();
    drawNyanAnimation();
}

void NyanScreen::handlePlayPauze(){
    play_active = !play_active;
}

void NyanScreen::handleReset(){
}

void NyanScreen::drawNyanAnimation(){
    int pixel_nr = 0;
    int y_offset = 6;
    for (unsigned int h = 0; h < 25; h++){
        for (unsigned int w = 0; w < 64; w++){
            display->drawPixelRGB565(w, h + y_offset, nyan_frames[active_frame_nr][pixel_nr]);
            pixel_nr++;
        }
    }
}

void NyanScreen::determineActiveFrame(){
    ticks_since_frame_change++;
    if (ticks_since_frame_change >= ticks_between_frame_change){
        active_frame_nr++;
        if (active_frame_nr >= NUM_FRAMES) {
            active_frame_nr = 0;
        }
        ticks_since_frame_change = 0;
    }
}

void NyanScreen::update(){
    if (play_active){
        determineActiveFrame();
        drawNyanAnimation();
    }
}


