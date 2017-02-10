#include "PositionComponent.hpp"

wj::PositionComponent::PositionComponent(Vec2 _pos, Poly _collider, uint8_t _layer) :
position(_pos), collider(_collider), layer(_layer)
{}

wj::PositionComponent::PositionComponent(const PositionComponent &p) :
position(p.position), collider(p.collider), layer(p.layer)
{}

wj::PositionComponent::~PositionComponent()
{}
