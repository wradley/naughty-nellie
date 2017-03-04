#ifndef __POSITION_SYSTEM_H___
#define __POSITION_SYSTEM_H___

#include "PositionComponent.hpp"
#include <cstdint>
#include <mutex>
#include <string>
#include "../util/Vec2.hpp"
#include "../util/ds/List.hpp"
#include "../util/ds/Queue.hpp"

namespace wj
{
    enum RequestType
    {
        SET_POS,
        MOD_POS,
        SET_LAYER,
        MOD_LAYER,
        SET_ROT,
        MOD_ROT
    };

    struct PositionRequest
    {
        uint64_t ent_instance_id;
        Vec2 dist;
        int layer;
        double rotation;

        RequestType type;
    };

    class PositionSystem
    {
    public:

        PositionSystem();
        PositionSystem(const PositionSystem &) = delete;
        ~PositionSystem();


        void define_ent(uint64_t ent_def_id, Poly collider, bool no_clip);
        void instantiate_ent(
            uint64_t ent_instance_id,
            uint64_t ent_def_id,
            Vec2 position,
            double rotation,
            uint8_t layer
        );


        // - updates all the entities that have been requested to
        //   translate by other systems and any collisions
        void update();

        // - clears out level data so a new one can be loaded in
        void clear_instance_data();


        // Setters
        void mod_ent_pos(uint64_t ent_instance_id, Vec2 distance);
        void set_ent_pos(uint64_t ent_instance_id, Vec2 pos);
        void mod_ent_rotation(uint64_t ent_instance_id, double deg);
        void set_ent_rotation(uint64_t ent_instance_id, double deg);
        void mod_ent_layer(uint64_t ent_instance_id, int layer_diff);
        void set_ent_layer(uint64_t ent_instance_id, uint8_t layer);


        // Getters
        Vec2    get_position(uint64_t ent_instance_id);
        uint8_t get_layer(uint64_t ent_instance_id);
        double  get_rotation(uint64_t ent_instance_id);

        // Debug
        std::string debug_define_to_string();
        std::string debug_instance_to_string();
        std::string debug_request_to_string();

    private:

        void handle_collisions(uint64_t ent_instance_id);

        // where all the defined components are stored to be copied into the instance components
        List<PositionComponent> _define_components;

        // Every entity must have a position so this will just be a simple array
        //   that uses the instance id as the index
        List<PositionComponent> _instance_components;

        // Holds a list of requests all to be updated at once everytime update() is called
        Queue<PositionRequest*> _requests;

        // Locks for the data structures
        std::mutex _lock;

    };
};

#endif /* end of include guard: __POSITION_SYSTEM_H___ */
