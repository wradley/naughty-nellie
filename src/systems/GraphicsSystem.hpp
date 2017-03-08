#ifndef __GRAPHICS_SYSTEM_H__
#define __GRAPHICS_SYSTEM_H__

#include <string>
#include <mutex>
#include "../SDLWrap.hpp"
#include "../util/ds/List.hpp"
#include "../util/ds/Map.hpp"
#include "../util/ds/Queue.hpp"

namespace wj
{
    struct Frame;
    struct DAnimation;
    struct IAnimation;
    struct AnimationRequest;
    struct RenderRequest;


    class GraphicsSystem
    {
    public:

        GraphicsSystem(SDLWrap *sdl);
        ~GraphicsSystem();


        // adds a frame to an animation
        void define_frame(
            uint64_t frame_number, // order in animation
            uint64_t animation_number,
            const std::string &filepath,
            double x, double y, double w, double h
        );


        // sets an entity with an animation
        void set_animation(
            uint64_t ent_instance_id, uint64_t animation_number
        );


        void render(
            uint64_t ent_instance_id,
            uint32_t x, uint32_t y, uint32_t w, uint32_t h
        );


        // sets each animation to its next frame
        void update();


        // - clears out level data so a new one can be loaded in
        void clear_instance_data();

    private:

        // SDL
        SDLWrap *_sdl;

        // Graphics Data
        Map<std::string, SDL_Texture*>   _sdl_textures;
        List<DAnimation>                 _define_animations;
        List<IAnimation>                 _instance_animations;
        Queue<AnimationRequest*>         _animation_requests;
        Queue<RenderRequest*>            _render_requests;

        // Lock
        std::mutex _lock;

        // Deleted functions
        GraphicsSystem(const GraphicsSystem &) = delete;
        void operator= (const GraphicsSystem &) = delete;
    };

    struct Frame
    {
        std::string sdl_texture;
        uint32_t x, y, w, h;
    };

    // define animation
    struct DAnimation
    {
        void operator= (const DAnimation &other);

        List<Frame> frames;
        int num_frames;
    };

    // instance animation
    struct IAnimation
    {
        uint64_t define_animation;
        int frame;
    };

    struct AnimationRequest
    {
        uint64_t ent_instance_id;
        uint64_t animation_number;
    };

    struct RenderRequest
    {
        uint64_t ent_instance_id;   // ent to be rendered
        uint32_t x, y, w, h;        // where to render on screen
    };
};

#endif /* end of include guard: __GRAPHICS_SYSTEM_H__ */
