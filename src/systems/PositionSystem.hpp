#ifndef __POSITION_SYSTEM_H___
#define __POSITION_SYSTEM_H___

#include "PositionComponent.hpp"
#include <cstdint>
#include "../util/Vec2.hpp"

namespace wj
{
    class PositionSystem
    {
    public:

        PositionSystem();
        PositionSystem(const PositionSystem &) = delete;
        ~PositionSystem();

        // to be called by game
        void add_ent(uint64_t ent_instance_id, uint64_t ent_def_id, Vec2 position);
        void start_update_loop(bool &running, bool &paused);

        // to be called by other systems
        void translate_ent(uint64_t ent_instance_id, Vec2 distance);

    private:

        // Every entity must have a position so this will just be a simple array
        //   that uses the instance id as the index
        PositionComponent *_components;
        uint64_t _num_components;

    };
};

#endif /* end of include guard: __POSITION_SYSTEM_H___ */
