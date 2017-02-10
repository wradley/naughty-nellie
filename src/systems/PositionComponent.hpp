#ifndef __POSITION_COMPONENT_H__
#define __POSITION_COMPONENT_H__

namespace wj
{
    struct PositionComponent
    {
        PositionComponent(Vec2 _pos, Poly _collider, uint8_t _layer);
        PositionComponent(const PositionComponent &p);
        ~PositionComponent();

        // global position in the world
        Vec2 position;

        // all the vectors that make up the shape of the ent
        Poly collider;

        // the layer the ent is on
        uint8_t layer;
    };
};

#endif /* end of include guard: __POSITION_COMPONENT_H__ */
