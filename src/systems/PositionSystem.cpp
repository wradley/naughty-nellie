#include "PositionSystem.hpp"
#include <cassert>

static const int DEF_START_SIZE         = 32;
static const int INSTANCE_START_SIZE    = 64;
static const int REQUEST_SIZE           = 128;

wj::PositionSystem::PositionSystem() :
_define_components(nullptr), _instance_components(nullptr), _requests(nullptr)
{
    // alloc space
    _define_components = new PositionComponent[DEF_START_SIZE];
    _instance_components = new PositionComponent[INSTANCE_START_SIZE];
    _requests = new PositionRequest[REQUEST_SIZE];

    // set values
    _num_define_components = DEF_START_SIZE;
    _num_instance_components = INSTANCE_START_SIZE;
    _max_num_requests = REQUEST_SIZE;
    _request_head = _request_tail = 0;
}


wj::PositionSystem::~PositionSystem()
{
    // dealloc space
    if (_define_components != nullptr) delete [] _define_components;
    if (_instance_components != nullptr) delete [] _instance_components;
    if (_requests   != nullptr) delete [] _requests;
}


void wj::PositionSystem::define_ent(uint64_t ent_def_id, Poly collider)
{
    _def_mutex.lock();

    // resize if more space is needed
    while (ent_def_id > _num_define_components)
    {
        _num_define_components *= 2;
        wj::PositionComponent *old = _define_components;
        _define_components = new wj::PositionComponent [_num_define_components];
        for (int i = 0; i < _num_define_components/2; ++i) _define_components[i] = old[i];
        delete [] old;
    }

    // Create new define component
    _define_components[ent_def_id].collider = collider;
    _define_components[ent_def_id].valid = true;

    _def_mutex.unlock();
}

void wj::PositionSystem::instantiate_ent(uint64_t ent_instance_id, uint64_t ent_def_id, Vec2 position, uint8_t layer, bool no_clip)
{
    _instance_mutex.lock();

    // make sure the component has been defined
    if ((ent_def_id >= _num_define_components) || !(_define_components[ent_def_id].valid))
    {
        printf("Position Component %llu not defined.\n", ent_def_id);
        assert(0);
    }

    // resize if more space is needed
    while (ent_instance_id > _num_instance_components)
    {
        _num_instance_components *= 2;
        wj::PositionComponent *old = _instance_components;
        _instance_components = new wj::PositionComponent [_num_instance_components];
        for (int i = 0; i < _num_instance_components/2; ++i) _instance_components[i] = old[i];
        delete [] old;
    }

    // Create new instance component
    _instance_components[ent_instance_id] = _define_components[ent_def_id];
    _instance_components[ent_instance_id].position = position;
    _instance_components[ent_instance_id].layer = layer;
    _instance_components[ent_instance_id].no_clip = no_clip;

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

void wj::PositionSystem::mod_ent_rotation(uint64_t ent_instance_id, int degrees)
{
    _request_mutex.lock();
    assert(0);
    _request_mutex.unlock();
}

void wj::PositionSystem::set_ent_rotation(uint64_t ent_instance_id, int degrees)
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
    if ((ent_instance_id >= _num_instance_components) || !(_instance_components[ent_instance_id].valid))
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
    if ((ent_instance_id >= _num_instance_components) || !(_instance_components[ent_instance_id].valid))
    {
        printf("Position Instance %llu does not exist.\n", ent_instance_id);
        assert(0);
    }

    // get position
    layer = _instance_components[ent_instance_id].layer;

    _instance_mutex.unlock();

    return layer;
}

int wj::PositionSystem::get_rotation()
{
    _instance_mutex.lock();
    assert(0);
    _instance_mutex.unlock();
    return 0;
}

std::string wj::PositionSystem::debug_define_to_string()
{
    std::string ret_str;

    _def_mutex.lock();
    for (int i = 0; i < _num_define_components; ++i)
    {
        if (!_define_components[i].valid) continue;
        ret_str += "Position System Define ID: [" + std::to_string(i) + "]\n";
        int num_verts = _define_components[i].collider.num_verts();
        for (int j = 0; j < num_verts; ++j)
        {
            Vec2 v = _define_components[i].collider.get_vert(j);
            ret_str +=
                "  " + std::to_string(v.x) + ", " +
                std::to_string(v.y) + "\n";
        }
    }
    _def_mutex.unlock();

    return ret_str;
}

std::string wj::PositionSystem::debug_instance_to_string()
{
    std::string ret_str;

    _instance_mutex.lock();
    for (int i = 0; i < _num_instance_components; ++i)
    {
        if (!_instance_components[i].valid) continue;
        ret_str += "Position System Instance ID: [" + std::to_string(i) + "]\n";
        int num_verts = _instance_components[i].collider.num_verts();
        for (int j = 0; j < num_verts; ++j)
        {
            Vec2 v = _instance_components[i].collider.get_vert(j);
            ret_str +=
                "  " + std::to_string(v.x) + ", " +
                std::to_string(v.y) + "\n";
        }
        ret_str += "  Pos:   " + std::to_string(_instance_components[i].position.x) + ", ";
        ret_str += std::to_string(_instance_components[i].position.y) + "\n";
        ret_str += "  Layer: " + std::to_string(_instance_components[i].layer);
    }
    _instance_mutex.unlock();

    return ret_str;
}

std::string wj::PositionSystem::debug_request_to_string()
{
    _request_mutex.lock();
    _request_mutex.unlock();
    assert(0);
}
