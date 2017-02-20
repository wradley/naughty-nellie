#include "PositionSystem.hpp"
#include <cassert>

static const int REQUEST_SIZE           = 128;

wj::PositionSystem::PositionSystem() : _requests(nullptr)
{
    // alloc space
    _requests = new PositionRequest[REQUEST_SIZE];

    // set values
    _max_num_requests = REQUEST_SIZE;
    _request_head = _request_tail = 0;
}


wj::PositionSystem::~PositionSystem()
{
    // dealloc space
    if (_requests   != nullptr) delete [] _requests;
}


void wj::PositionSystem::define_ent(
    uint64_t ent_def_id,
    Poly collider,
    bool no_clip
){
    _def_mutex.lock();

    // Create new define component
    _define_components[ent_def_id].collider = collider;
    _define_components[ent_def_id].no_clip = no_clip;

    _def_mutex.unlock();
}

void wj::PositionSystem::instantiate_ent(
    uint64_t ent_instance_id,
    uint64_t ent_def_id,
    Vec2 position,
    double rotation,
    uint8_t layer
){
    _instance_mutex.lock();

    // make sure the component has been defined
    if (!_define_components.exists(ent_def_id))
    {
        printf("Position Component %llu not defined.\n", ent_def_id);
        assert(0);
    }

    // Create new instance component
    _instance_components[ent_instance_id] = _define_components[ent_def_id];
    _instance_components[ent_instance_id].position = position;
    _instance_components[ent_instance_id].layer = layer;
    _instance_components[ent_instance_id].rotation = rotation;

    _instance_mutex.unlock();
}

void wj::PositionSystem::update()
{
    _instance_mutex.lock();
    assert(0);
    _instance_mutex.unlock();
}

void wj::PositionSystem::mod_ent_pos(uint64_t ent_instance_id, Vec2 distance)
{
    _request_mutex.lock();
    assert(0);
    _request_mutex.unlock();
}

void wj::PositionSystem::set_ent_pos(uint64_t ent_instance_id, Vec2 pos)
{
    _request_mutex.lock();
    assert(0);
    _request_mutex.unlock();
}

void wj::PositionSystem::mod_ent_rotation(uint64_t ent_instance_id, double deg)
{
    _request_mutex.lock();
    assert(0);
    _request_mutex.unlock();
}

void wj::PositionSystem::set_ent_rotation(uint64_t ent_instance_id, double deg)
{
    _request_mutex.lock();
    assert(0);
    _request_mutex.unlock();
}

void wj::PositionSystem::mod_ent_layer(uint64_t ent_instance_id, int layer_diff)
{
    _request_mutex.lock();
    assert(0);
    _request_mutex.unlock();
}

void wj::PositionSystem::set_ent_layer(uint64_t ent_instance_id, uint8_t layer)
{
    _request_mutex.lock();
    assert(0);
    _request_mutex.unlock();
}

wj::Vec2 wj::PositionSystem::get_position(uint64_t ent_instance_id)
{
    Vec2 pos;

    _instance_mutex.lock();

    // make sure the instance exists
    if (!_instance_components.exists(ent_instance_id))
    {
        printf("Position Instance %llu does not exist.\n", ent_instance_id);
        assert(0);
    }

    // get position
    pos = _instance_components[ent_instance_id].position;

    _instance_mutex.unlock();
    return pos;
}

uint8_t wj::PositionSystem::get_layer(uint64_t ent_instance_id)
{
    uint8_t layer;

    _instance_mutex.lock();

    // make sure the instance exists
    if (!_instance_components.exists(ent_instance_id))
    {
        printf("Position Instance %llu does not exist.\n", ent_instance_id);
        assert(0);
    }

    // get position
    layer = _instance_components[ent_instance_id].layer;

    _instance_mutex.unlock();
    return layer;
}

double wj::PositionSystem::get_rotation(uint64_t ent_instance_id)
{
    double rotation;
    _instance_mutex.lock();

    // make sure the instance exists
    if (!_instance_components.exists(ent_instance_id))
    {
        printf("Position Instance %llu does not exist.\n", ent_instance_id);
        assert(0);
    }

    // get rotation
    rotation = _instance_components[ent_instance_id].rotation;

    _instance_mutex.unlock();
    return rotation;
}

std::string wj::PositionSystem::debug_define_to_string()
{
    std::string ret_str;

    _def_mutex.lock();
    ret_str = _define_components.debug_to_string();
    _def_mutex.unlock();

    return ret_str;
}

std::string wj::PositionSystem::debug_instance_to_string()
{
    std::string ret_str;

    _instance_mutex.lock();
    ret_str = _instance_components.debug_to_string();
    _instance_mutex.unlock();

    return ret_str;
}

std::string wj::PositionSystem::debug_request_to_string()
{
    _request_mutex.lock();
    _request_mutex.unlock();
    assert(0);
}
