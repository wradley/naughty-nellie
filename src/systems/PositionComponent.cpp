#include "PositionComponent.hpp"

wj::PositionComponent::PositionComponent()
{}

wj::PositionComponent::PositionComponent(const PositionComponent &p) :
id(p.id),
position(p.position),
rotation(p.rotation),
collider(p.collider),
layer(p.layer),
no_clip(p.no_clip)
{}

wj::PositionComponent::~PositionComponent()
{}
