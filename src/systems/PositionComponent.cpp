#include "PositionComponent.hpp"

wj::PositionComponent::PositionComponent()
{}

wj::PositionComponent::PositionComponent(const PositionComponent &p) :
position(p.position), collider(p.collider),
layer(p.layer), no_clip(p.no_clip)
{}

wj::PositionComponent::~PositionComponent()
{}
