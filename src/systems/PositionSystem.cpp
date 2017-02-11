#include "PositionSystem.hpp"
#include <cassert>

wj::PositionSystem::PositionSystem() :
_components(nullptr), _num_components(0)
{
    assert(0);
}

wj::PositionSystem::~PositionSystem()
{
    assert(0);
}


void wj::PositionSystem::add_ent(uint64_t ent_instance_id, uint64_t ent_def_id, Vec2 position)
{
    assert(0);
}

void wj::PositionSystem::update()
{
    assert(0);
}

void wj::PositionSystem::translate_ent(uint64_t ent_instance_id, Vec2 distance)
{
    assert(0);
}
