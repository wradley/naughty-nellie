#ifndef __POSITION_SYSTEM_H___
#define __POSITION_SYSTEM_H___

#include "PositionComponent.hpp"
#include <cstdint>
#include <mutex>
#include <string>
#include "../util/Vec2.hpp"
#include "../util/FList.hpp"

namespace wj
{
    struct PositionRequest
    {
        uint64_t ent_instance_id;
        Vec2 dist;
        int layer;
        int rotation;

        bool set_pos; // true = set position rather than translate position
        bool set_layer; // true = set layer rather than modify layer (+/- some ammount)
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


        // updates all the entities that have been requested to translate by other systems
        //   and any collisions
        void update();


        // queues a request to change an entity
        //   (which will be changed upon the next update)
        void mod_ent_pos(uint64_t ent_instance_id, Vec2 distance);
        void set_ent_pos(uint64_t ent_instance_id, Vec2 pos);
        void mod_ent_rotation(uint64_t ent_instance_id, double deg);
        void set_ent_rotation(uint64_t ent_instance_id, double deg);
        void mod_ent_layer(uint64_t ent_instance_id, int layer_diff);
        void set_ent_layer(uint64_t ent_instance_id, uint8_t layer);


        // getters
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
        FList<PositionComponent> _define_components;

        // Every entity must have a position so this will just be a simple array
        //   that uses the instance id as the index
        FList<PositionComponent> _instance_components;

        PositionRequest *_requests;
        uint64_t _request_head, _request_tail, _max_num_requests;


        std::mutex _instance_mutex, _def_mutex, _request_mutex;

    };
};

#endif /* end of include guard: __POSITION_SYSTEM_H___ */
