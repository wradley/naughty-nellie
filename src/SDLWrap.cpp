#include "SDLWrap.hpp"
#include <SDL2/SDL_image.h>
#include <cassert>
#include <string>

extern int G_SCREEN_WIDTH;
extern int G_SCREEN_HEIGHT;

wj::SDLWrap::SDLWrap()
{
    if (SDL_Init(SDL_INIT_TIMER|SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0)
    {
        printf("Unable to initialize SDL: %s\n", SDL_GetError());
        assert(0);
    }

    // Video
    _window = NULL;
    _window = SDL_CreateWindow( "WJ",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        G_SCREEN_WIDTH, G_SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE
    );
    if (_window == NULL) {
        printf("SDL Window Error: %s\n", SDL_GetError());
        assert(0);
    }

    // Init renderer
    _renderer = NULL;
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
    if (_renderer == NULL) {
        printf("SDL Renderer Error: %s\n", SDL_GetError());
        assert(0);
    }

    // init renderer color to black
    if (SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255) != 0)
    {
        printf("SDL did not set draw color: %s\n", SDL_GetError());
        assert(0);
    }

    // init PNG loading
    int imgFlags = IMG_INIT_PNG;
    if(!(IMG_Init(imgFlags) & imgFlags))
    {
        printf("SDL_Image Error: %s\n", IMG_GetError());
        assert(0);
    }
}

wj::SDLWrap::~SDLWrap()
{
    exit();
}

void wj::SDLWrap::exit()
{
    // video
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);


    SDL_Quit();
}


void wj::SDLWrap::render_present()
{
    std::lock_guard<std::mutex> lock(_graphics_lock);
    SDL_RenderPresent(_renderer);
}


void wj::SDLWrap::render_clear()
{
    std::lock_guard<std::mutex> lock(_graphics_lock);

    if (SDL_RenderClear(_renderer) != 0)
    {
        printf("SDL did not render_clear: %s\n", SDL_GetError());
        assert(0);
    }
}

void wj::SDLWrap::render_copy(
    SDL_Texture* t, SDL_Rect src, SDL_Rect dst
){
    std::lock_guard<std::mutex> lock(_graphics_lock);
    if (SDL_RenderCopy(_renderer, t, &src, &dst) != 0)
    {
        printf("SDL did not render copy: %s\n", SDL_GetError());
        assert(0);
    }
}

void wj::SDLWrap::draw_rect(SDL_Rect rec, Color c)
{
    uint8_t r, g, b, a;

    std::lock_guard<std::mutex> lock(_graphics_lock);
    SDL_GetRenderDrawColor(_renderer, &r, &g, &b, &a);
    SDL_SetRenderDrawColor(_renderer, c.r, c.g, c.b, c.a);
    SDL_RenderFillRect(_renderer, &rec);
    SDL_SetRenderDrawColor(_renderer, r, g, b, a);
}


SDL_Texture* wj::SDLWrap::make_texture(const std::string &filepath)
{
    SDL_Surface *s = NULL;
    s = IMG_Load(filepath.c_str());
    if (s == NULL)
    {
        printf("IMG Error: %s\n", IMG_GetError());
        assert(0);
    }

    SDL_Texture *t = NULL;
    t = SDL_CreateTextureFromSurface(_renderer, s);
    if (t == NULL)
    {
        printf("SDL Error: %s\n", SDL_GetError());
        assert(0);
    }

    SDL_FreeSurface(s);
    return t;
}
