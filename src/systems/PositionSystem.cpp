#include "PositionSystem.hpp"
#include <cassert>

wj::PositionSystem::PositionSystem() {}
wj::PositionSystem::~PositionSystem() {}


void wj::PositionSystem::define_ent(
    uint64_t ent_def_id,
    Poly collider,
    bool no_clip
){
    _lock.lock();

    // Create new define component
    _define_components[ent_def_id].collider = collider;
    _define_components[ent_def_id].no_clip = no_clip;

    _lock.unlock();
}

void wj::PositionSystem::instantiate_ent(
    uint64_t ent_instance_id,
    uint64_t ent_def_id,
    Vec2 position,
    double rotation,
    uint8_t layer
){
    _lock.lock();

    // make sure the component has been defined
    if (!_define_components.exists(ent_def_id))
    {
        printf("Position Component %llu not defined.\n", ent_def_id);
        _lock.unlock();
        assert(0);
    }

    // Create new instance component
    _instance_components[ent_instance_id] = _define_components[ent_def_id];
    _instance_components[ent_instance_id].id = ent_instance_id;
    _instance_components[ent_instance_id].position = position;
    _instance_components[ent_instance_id].layer = layer;
    _instance_components[ent_instance_id].rotation = rotation;

    _lock.unlock();
}

void wj::PositionSystem::update()
{
    int num_fails = 0;
    while (!_lock.try_lock())
    {
        printf("***FAIL***\n");
    }

    while (!_requests.is_empty())
    {
        PositionRequest *pr = _requests.pop();
        uint64_t i = pr->ent_instance_id;

        switch (pr->type) {
            case SET_POS:
                _instance_components[i].position = pr->dist;
                break;
            case MOD_POS:
                _instance_components[i].position += pr->dist;
                break;
            case SET_LAYER:
                _instance_components[i].layer = pr->layer;
                break;
            case MOD_LAYER:
                _instance_components[i].layer += pr->layer;
                break;
            case SET_ROT:
                _instance_components[i].rotation = pr->rotation;
                break;
            case MOD_ROT:
                _instance_components[i].rotation += pr->rotation;
                break;
            default:
                printf("PositionSystem update");
                _lock.unlock();
                assert(0);
                break;
        }
        delete pr;
    }
    _lock.unlock();

    printf("Num fails: %i\n", num_fails);


    // _lock.lock();
    //
    // while (!_requests.is_empty())
    // {
    //     PositionRequest *pr = _requests.pop();
    //     uint64_t i = pr->ent_instance_id;
    //
    //     switch (pr->type) {
    //         case SET_POS:
    //             _instance_components[i].position = pr->dist;
    //             break;
    //         case MOD_POS:
    //             _instance_components[i].position += pr->dist;
    //             break;
    //         case SET_LAYER:
    //             _instance_components[i].layer = pr->layer;
    //             break;
    //         case MOD_LAYER:
    //             _instance_components[i].layer += pr->layer;
    //             break;
    //         case SET_ROT:
    //             _instance_components[i].rotation = pr->rotation;
    //             break;
    //         case MOD_ROT:
    //             _instance_components[i].rotation += pr->rotation;
    //             break;
    //         default:
    //             printf("PositionSystem update");
    //             _lock.unlock();
    //             assert(0);
    //             break;
    //     }
    //     delete pr;
    // }
    //
    // _lock.unlock();
}

void wj::PositionSystem::mod_ent_pos(uint64_t ent_instance_id, Vec2 distance)
{
    _lock.lock();
    PositionRequest *pr = new PositionRequest;
    pr->ent_instance_id = ent_instance_id;
    pr->dist = distance;
    pr->type = MOD_POS;
    _requests.push(pr);
    _lock.unlock();
}

void wj::PositionSystem::set_ent_pos(uint64_t ent_instance_id, Vec2 pos)
{
    _lock.lock();
    PositionRequest *pr = new PositionRequest;
    pr->ent_instance_id = ent_instance_id;
    pr->dist = pos;
    pr->type = SET_POS;
    _requests.push(pr);
    _lock.unlock();
}

void wj::PositionSystem::mod_ent_rotation(uint64_t ent_instance_id, double deg)
{
    _lock.lock();
    PositionRequest *pr = new PositionRequest;
    pr->ent_instance_id = ent_instance_id;
    pr->rotation = deg;
    pr->type = MOD_ROT;
    _requests.push(pr);
    _lock.unlock();
}

void wj::PositionSystem::set_ent_rotation(uint64_t ent_instance_id, double deg)
{
    _lock.lock();
    PositionRequest *pr = new PositionRequest;
    pr->ent_instance_id = ent_instance_id;
    pr->rotation = deg;
    pr->type = SET_ROT;
    _requests.push(pr);
    _lock.unlock();
}

void wj::PositionSystem::mod_ent_layer(uint64_t ent_instance_id, int layer_diff)
{
    _lock.lock();
    PositionRequest *pr = new PositionRequest;
    pr->ent_instance_id = ent_instance_id;
    pr->layer = layer_diff;
    pr->type = MOD_LAYER;
    _requests.push(pr);
    _lock.unlock();
}

void wj::PositionSystem::set_ent_layer(uint64_t ent_instance_id, uint8_t layer)
{
    _lock.lock();
    PositionRequest *pr = new PositionRequest;
    pr->ent_instance_id = ent_instance_id;
    pr->layer = layer;
    pr->type = SET_LAYER;
    _requests.push(pr);
    _lock.unlock();
}

wj::Vec2 wj::PositionSystem::get_position(uint64_t ent_instance_id)
{
    Vec2 pos;

    _lock.lock();

    // make sure the instance exists
    if (!_instance_components.exists(ent_instance_id))
    {
        printf("Position Instance %llu does not exist.\n", ent_instance_id);
        _lock.unlock();
        assert(0);
    }

    // get position
    pos = _instance_components[ent_instance_id].position;

    _lock.unlock();
    return pos;
}

uint8_t wj::PositionSystem::get_layer(uint64_t ent_instance_id)
{
    uint8_t layer;

    _lock.lock();

    // make sure the instance exists
    if (!_instance_components.exists(ent_instance_id))
    {
        printf("Position Instance %llu does not exist.\n", ent_instance_id);
        _lock.unlock();
        assert(0);
    }

    // get position
    layer = _instance_components[ent_instance_id].layer;

    _lock.unlock();
    return layer;
}

double wj::PositionSystem::get_rotation(uint64_t ent_instance_id)
{
    double rotation;
    _lock.lock();

    // make sure the instance exists
    if (!_instance_components.exists(ent_instance_id))
    {
        printf("Position Instance %llu does not exist.\n", ent_instance_id);
        _lock.unlock();
        assert(0);
    }

    // get rotation
    rotation = _instance_components[ent_instance_id].rotation;

    _lock.unlock();
    return rotation;
}

std::string wj::PositionSystem::debug_define_to_string()
{
    std::string ret_str;

    _lock.lock();
    ret_str = _define_components.debug_to_string();
    _lock.unlock();

    return ret_str;
}

std::string wj::PositionSystem::debug_instance_to_string()
{
    std::string ret_str;

    _lock.lock();
    ret_str = _instance_components.debug_to_string() + "\n";
    for (auto p_comp : _instance_components)
    {
        ret_str += "Instance: " + std::to_string(p_comp.id) + "\n";
        ret_str += "  [" + std::to_string(p_comp.position.x) + ", ";
        ret_str += std::to_string(p_comp.position.y) + "]\n";
        ret_str += "  Verts:\n";
        for (auto vert : p_comp.collider)
        {
            ret_str += "    [" + std::to_string(vert.x) + ", ";
            ret_str += std::to_string(vert.y) + "]\n";
        }
    }
    _lock.unlock();

    return ret_str;
}

std::string wj::PositionSystem::debug_request_to_string()
{
    _lock.lock();
    _lock.unlock();
    assert(0);
}


void wj::PositionSystem::clear_instance_data()
{
    _lock.lock();

    // Clear out instances
    _instance_components.clear();

    // clear out requests
    while (!_requests.is_empty())
    {
        PositionRequest *pr = _requests.pop();
        delete pr;
    }

    _lock.unlock();
}
