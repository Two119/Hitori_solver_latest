#pragma once
#include <include/button.hpp>
Button button;
Slider slider;
void initiliaze(){
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    SDL_ShowCursor(SDL_DISABLE);
    IMG_Init(IMG_INIT_JPG || IMG_INIT_PNG);
    
    int size[2] = {2, 1};
    button_sprites.init(scale_surface(IMG_Load("assets/ui/buttons.png")), size, black, 4);
    int loc[2] = {0, 0};
    cursor_img.init(scale_surface(IMG_Load("assets/ui/cursor.png"), 2));
    clicksound.init("assets/sfx/click.wav");
    window_rect.x = 0;
    window_rect.y = 0;
    window_rect.w = 1280;
    window_rect.h = 720;
    int pos[2] = {100, 100};
    int pos2[2] = {100, 200};
    button.init(pos);
    slider.init(pos2);
}