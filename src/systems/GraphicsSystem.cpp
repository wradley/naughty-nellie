#include "GraphicsSystem.hpp"

void wj::DAnimation::operator= (const DAnimation &other)
{
    frames = other.frames;
    num_frames = other.num_frames;
}

wj::GraphicsSystem::GraphicsSystem() :
_window(NULL), _renderer(NULL),
_screen_width(640), _screen_height(480)
{
    // Init window
    _window = SDL_CreateWindow(
        "WJ",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        _screen_width, _screen_height,
        SDL_WINDOW_SHOWN
    );
    if (_window == NULL)
    {
        printf("SDL Window Error: %s\n", SDL_GetError());
        assert(0);
    }

    // Init renderer
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
    if (_renderer == NULL)
    {
        printf("SDL Renderer Error: %s\n", SDL_GetError());
        assert(0);
    }

    // init renderer color to black
    SDL_SetRenderDrawColor( _renderer, 0, 0, 0, 0xFF );

    // init PNG loading
    int imgFlags = IMG_INIT_PNG;
    if(!(IMG_Init(imgFlags) & imgFlags))
    {
        printf("SDL_Image Error: %s\n", IMG_GetError());
        assert(0);
    }
}

wj::GraphicsSystem::~GraphicsSystem()
{
    // free sdl stuff
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
}


void wj::GraphicsSystem::define_frame(
    uint64_t frame_number,
    uint64_t animation_number,
    const std::string &filepath,
    double x, double y, double w, double h
){
    _lock.lock();

    if (!_sdl_textures.has(filepath))
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

        _sdl_textures[filepath] = t;
        SDL_FreeSurface(s);
    }

    Frame f;
    f.sdl_texture = filepath;
    f.x = x;
    f.y = y;
    f.w = w;
    f.h = x;

    _define_animations[animation_number].frames[frame_number] = f;
    _define_animations[animation_number].num_frames += 1;

    _lock.unlock();
}

void wj::GraphicsSystem::set_animation(
    uint64_t ent_instance_id, uint64_t animation_number
){
    _lock.lock();

    AnimationRequest *a = new AnimationRequest;
    a->ent_instance_id = ent_instance_id;
    a->animation_number = animation_number;
    _animation_requests.push(a);

    _lock.unlock();
}

void wj::GraphicsSystem::render(
    uint64_t ent_instance_id,
    uint32_t x, uint32_t y, uint32_t w, uint32_t h
){
    _lock.lock();

    RenderRequest *r = new RenderRequest;
    r->ent_instance_id = ent_instance_id;
    r->x = x;
    r->y = y;
    r->w = w;
    r->h = h;
    _render_requests.push(r);

    _lock.unlock();
}

void wj::GraphicsSystem::update()
{
    _lock.lock();
    _lock.lock();

    while (!_animation_requests.is_empty())
    {
        AnimationRequest *r = _animation_requests.pop();

        delete r;
    }
    _lock.unlock();

    // incr all frames
    for (auto animation : _instance_animations)
    {
        ++animation.frame;
        if (animation.frame >= _define_animations[animation.define_animation].num_frames)
        {
            animation.frame = 0;
        }
    }
    _lock.unlock();
}

void wj::GraphicsSystem::clear_instance_data()
{
    _lock.lock();

    // Clear out instance data
    _instance_animations.clear();

    // clear out animation requests
    while (!_animation_requests.is_empty())
    {
        AnimationRequest *ar = _animation_requests.pop();
        delete ar;
    }

    // clear out render requests
    while (!_animation_requests.is_empty())
    {
        RenderRequest *rr = _render_requests.pop();
        delete rr;
    }

    _lock.unlock();
}
