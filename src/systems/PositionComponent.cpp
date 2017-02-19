#include "PositionComponent.hpp"

wj::PositionComponent::PositionComponent() :
valid(false)
{}

wj::PositionComponent::PositionComponent(const PositionComponent &p) :
position(p.position), collider(p.collider),
layer(p.layer), no_clip(p.no_clip), valid(p.valid)
{}

wj::PositionComponent::~PositionComponent()
{}
