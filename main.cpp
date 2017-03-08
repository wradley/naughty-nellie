#include "src/Level.hpp"
#include "src/SDLWrap.hpp"
using namespace wj;

int G_SCREEN_WIDTH = 640;
int G_SCREEN_HEIGHT = 480;

int main(int argc, char const *argv[])
{
    // Init SDL
    SDLWrap sdl;

    // test draw rect
    sdl.render_clear();
    sdl.draw_rect({100,100,100,100}, {0xFF, 0xFF, 0xFF, 0xFF});
    sdl.render_present();

    // Startup main menu
    Level level(&sdl);
    level.load_define("game/defines/test.define");
    level.run("game/levels/Level_1");

    SDL_Delay(2000);

    return 0;
}
