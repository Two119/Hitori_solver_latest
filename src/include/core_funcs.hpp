#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <memory>
#include <string>
#include <cmath>
#include <vector>
#include <functional>
#include <SDL2_rotozoom.c>
#include <algorithm>
using namespace std;
int mouse_pos[2];
SDL_Point mousepos;
SDL_Window *win = SDL_CreateWindow("Hitori Solver", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 1000, SDL_RENDERER_ACCELERATED);
SDL_Rect window_rect;
bool playing = true;
SDL_Event event;
Uint32 black = (255<<24) + (int(0)<<16) + (int(0)<<8) + int(0);
Uint32 white = (255<<24) + (int(255)<<16) + (int(255)<<8) + int(255);
Uint32 red = (255<<24) + (int(255)<<16) + (int(0)<<8) + int(0);
Uint32 green = (255<<24) + (int(0)<<16) + (int(255)<<8) + int(0);
Uint32 blue = (255<<24) + (int(0)<<16) + (int(0)<<8) + int(255);
SDL_Surface *window_surface;
Uint32 button_state;
Uint8 *keyboard_state;
int FRAMES_PER_SECOND = 60;
int framestart;
int frametime;
int framedelay = ( 1000 / FRAMES_PER_SECOND );
SDL_Surface * scale_surface(SDL_Surface *surf, float factor=4.0){
    return zoomSurface(surf, factor, factor, SMOOTHING_OFF);
}
SDL_Surface * rotate_surface(SDL_Surface *surf, double angle){
    return rotozoomSurface(surf, angle, 1.00, SMOOTHING_OFF);
}
class Image{
    public:
    SDL_Rect srcrect;
    SDL_Rect dstrect;
    SDL_Surface* surface;
    void init(SDL_Surface* surf, Uint32 colorkey = black, bool set = true){
        surface = surf;           
        if (set){SDL_SetColorKey(surface, SDL_TRUE, colorkey);}
        srcrect.x = 0;
        srcrect.y = 0;
        srcrect.w = surface->w;
        srcrect.h = surface->h;
        dstrect.w = surface->w;
        dstrect.h = surface->h;
    }
    void blit(int pos[2], SDL_Surface *dest_surf = window_surface){
        dstrect.x = pos[0];
        dstrect.y = pos[1];
        SDL_BlitSurface(surface, &srcrect, dest_surf, &dstrect);
    }
    SDL_Rect get_src(){
        return srcrect;
    }
    SDL_Rect get_dst(){
        return dstrect;
    }
};
Image scale_image(Image img, float factor=4.0){
    Image new_img;
    new_img.init(zoomSurface(img.surface, factor, factor, SMOOTHING_OFF));
    return new_img;
}
Image rotate_image(Image img, double angle){
    Image new_img;
    new_img.init(rotozoomSurface(img.surface, angle, 1.00, SMOOTHING_OFF));
    return new_img;
}
Image cursor_img;
class Spritesheet{
    public:
    int size[2] = {0, 0};
    vector<vector<SDL_Surface *>> sheet;
    void init(SDL_Surface* sheet_, int size_[2], Uint32 colorkey = black, int spacing=0){
        size[0] = sheet_->w/size_[0];
        size[1] = sheet_->h/size_[1];
        SDL_Rect srcrect;
        srcrect.w = size[0];
        srcrect.h = size[1];
        SDL_Rect dstrect;
        dstrect.w = size[0];
        dstrect.h = size[1];
        dstrect.x = 0;
        dstrect.y = 0;
        vector<SDL_Surface *> vec = {};
        for (int i = 0; i < size_[1]; i++){
            sheet.push_back(vec);
            for (int j = 0; j < size_[0]; j++){
                SDL_Surface *surf = SDL_CreateRGBSurface(0,size[0]-spacing,size[1]-spacing,32,0,0,0,SDL_ALPHA_OPAQUE);
                srcrect.x = (size[0]*j)+spacing;
                srcrect.y = (size[1]*i)+spacing;
                SDL_BlitSurface(sheet_, &srcrect, surf, &dstrect);
                SDL_SetColorKey(surf, SDL_TRUE, colorkey);
                sheet[i].push_back(surf);
            }
        }
    }
    SDL_Surface * get(int loc[2]){
        return sheet[loc[1]][loc[0]];
    }
};
Spritesheet button_sprites;
class Sound {
    public:
    int audio_rate = 22050;
    Uint16 audio_format = AUDIO_S16SYS; 
    int audio_channels = 2; 
    int audio_buffers = 4096;
    Mix_Chunk *sound = NULL;
    int channel;
    void init(const char * filename){
        Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers);
        sound = Mix_LoadWAV(filename);
    }
    void play(){
        channel = Mix_PlayChannel(-1, sound, 0);
    }
};
Sound clicksound;
SDL_Color fColor;
SDL_Color wColor;
class Text{
    public:
    TTF_Font *font;
    SDL_Surface* fontSurface;
    
    SDL_Rect fontRect;
    void init(const char*filename, int fontsize){
        font = TTF_OpenFont(filename, fontsize);
        fColor.r = 0;
        fColor.g = 0;
        fColor.b = 0;
        wColor.r = 255;
        wColor.g = 255;
        wColor.b = 255;
    }
    void render(const char *c, int pos[2], SDL_Surface *surf=window_surface, SDL_Color color=fColor){
        fontSurface = TTF_RenderText_Solid(font, c, color);
        fontRect.x = pos[0];
        fontRect.y = pos[1];
        SDL_BlitSurface(fontSurface, NULL, surf, &fontRect);
    }

};
template < typename ret, typename T, typename... Rest > using fn = std::function< ret(T, Rest...) >;
template < typename ret, typename T, typename... Rest > ret wrapper(fn< ret, T, Rest... > f, T t, Rest... rest)
{
  return f(t, rest...);
}

template < typename ret, typename T, typename... Rest > ret wrapper(fn< ret, T &, Rest &... > f, T &t, Rest &...rest)
{
  return f(t, rest...);
}
int test(int in){
    cout << "Button works!" << endl;
    return 1;
}
auto test_func = fn<int, int>(test);
