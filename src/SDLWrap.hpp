#ifndef __SDLWRAP_H__
#define __SDLWRAP_H__

#include <SDL2/SDL.h>
#include <mutex>
#include <cstdint>

namespace wj
{
    struct Color
    {
        uint8_t r, g, b, a;
    };

    class SDLWrap
    {
    public:

        SDLWrap();
        ~SDLWrap();

        // Visual
        void render_present();
        void render_clear();
        void render_copy(
            SDL_Texture* t, SDL_Rect src, SDL_Rect dst
        );
        void draw_rect(SDL_Rect r, Color c);
        SDL_Texture* make_texture(const std::string &filepath);

        // Audio

    private:

        void exit();

        SDL_Window *_window;
        SDL_Renderer *_renderer;

        std::mutex _graphics_lock;

    };
};

#endif /* end of include guard: __SDLWRAP_H__ */
