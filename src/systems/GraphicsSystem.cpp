#include "GraphicsSystem.hpp"

extern int G_SCREEN_WIDTH;
extern int G_SCREEN_HEIGHT;

void wj::DAnimation::operator= (const DAnimation &other)
{
    frames = other.frames;
    num_frames = other.num_frames;
}

wj::GraphicsSystem::GraphicsSystem(SDLWrap *sdl) :
_sdl(sdl)
{
    printf("GraphicsSystem created with window size: %i, %i\n", G_SCREEN_WIDTH, G_SCREEN_HEIGHT);

    printf("** SDLW addr GSys CTOR: %p\n", _sdl);
}

wj::GraphicsSystem::~GraphicsSystem()
{
    printf("GraphicsSystem Deleted\n");
}


void wj::GraphicsSystem::define_frame(
    uint64_t frame_number,
    uint64_t animation_number,
    const std::string &filepath,
    double x, double y, double w, double h
){
    std::lock_guard<std::mutex> lock(_lock);

    if (!_sdl_textures.has(filepath))
    {
        _sdl_textures[filepath] = _sdl->make_texture(filepath);
    }

    Frame f;
    f.sdl_texture = filepath;
    f.x = x;
    f.y = y;
    f.w = w;
    f.h = x;

    _define_animations[animation_number].frames[frame_number] = f;
    _define_animations[animation_number].num_frames += 1;
}

void wj::GraphicsSystem::set_animation(
    uint64_t ent_instance_id, uint64_t animation_number
){
    std::lock_guard<std::mutex> lock(_lock);

    AnimationRequest *a = new AnimationRequest;
    a->ent_instance_id = ent_instance_id;
    a->animation_number = animation_number;
    _animation_requests.push(a);
}

void wj::GraphicsSystem::render(
    uint64_t ent_instance_id,
    uint32_t x, uint32_t y, uint32_t w, uint32_t h
){
    std::lock_guard<std::mutex> lock(_lock);

    RenderRequest *r = new RenderRequest;
    r->ent_instance_id = ent_instance_id;
    r->x = x;
    r->y = y;
    r->w = w;
    r->h = h;
    _render_requests.push(r);
}

void wj::GraphicsSystem::update()
{
    std::lock_guard<std::mutex> lock(_lock);

    while (!_animation_requests.is_empty())
    {
        AnimationRequest *r = _animation_requests.pop();
        delete r;
    }

    // test draw rect
    _sdl->render_clear();
    _sdl->draw_rect({100,100,100,100}, {0xFF, 0xFF, 0xFF, 0xFF});


    // incr all frames
    // for (auto animation : _instance_animations)
    // {
    //     ++animation.frame;
    //     if (animation.frame >= _define_animations[animation.define_animation].num_frames)
    //     {
    //         animation.frame = 0;
    //     }
    // }
}

void wj::GraphicsSystem::clear_instance_data()
{
    std::lock_guard<std::mutex> lock(_lock);

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
}
