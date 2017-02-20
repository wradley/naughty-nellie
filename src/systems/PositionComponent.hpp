#ifndef __POSITION_COMPONENT_H__
#define __POSITION_COMPONENT_H__

#include <cstdint>
#include "../util/Vec2.hpp"
#include "../util/Poly.hpp"

namespace wj
{
    struct PositionComponent
    {
        PositionComponent();
        PositionComponent(const PositionComponent &p);
        ~PositionComponent();

        // global position in the world
        Vec2 position;
        double rotation;

        // all the vectors that make up the shape of the ent
        Poly collider;

        // the layer the ent is on
        uint8_t layer;

        // if the object should worry about collisions
        bool no_clip;
    };
};

#endif /* end of include guard: __POSITION_COMPONENT_H__ */
