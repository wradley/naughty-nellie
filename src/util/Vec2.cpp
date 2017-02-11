#include "Vec2.hpp"

#include <cmath>

wj::Vec2::Vec2(double x_, double y_) :
    x(x_), y(y_)
{}


wj::Vec2::Vec2(const Vec2 &other) :
    x(other.x), y(other.y)
{}


void wj::Vec2::operator= (const Vec2 &other)
{
    x = other.x;
    y = other.y;
}


wj::Vec2 wj::Vec2::normal() const
{
    Vec2 v((y), (-x));
    v.normalize();
    return v;
}


wj::Vec2 wj::Vec2::perp() const
{
    Vec2 v((y), (-x));
    return v;
}


double wj::Vec2::magnitude() const
{
    return sqrt( (x * x) + (y * y) );
}


wj::Vec2 wj::Vec2::direction() const
{
    double m = magnitude();
    Vec2 v((x / m), (y / m));
    return v;
}


void wj::Vec2::normalize()
{
    double m = magnitude();
    x /= m;
    y /= m;
}


wj::Vec2 wj::Vec2::operator+ (const Vec2 &other) const
{
    Vec2 v((x + other.x), (y + other.y));
    return v;
}

wj::Vec2 wj::Vec2::operator- (const Vec2 &other) const
{
    Vec2 v((x - other.x), (y - other.y));
    return v;
}

wj::Vec2 wj::Vec2::operator* (double val) const
{
    Vec2 v((x * val), (y * val));
    return v;
}

wj::Vec2 wj::Vec2::operator/ (double val) const
{
    Vec2 v((x / val), (y / val));
    return v;
}

void wj::Vec2::operator+= (const Vec2 &other)
{
    x += other.x;
    y += other.y;
}

void wj::Vec2::operator-= (const Vec2 &other)
{
    x -= other.x;
    y -= other.y;
}

void wj::Vec2::operator*= (double val)
{
    x *= val;
    y *= val;
}

void wj::Vec2::operator/= (double val)
{
    x /= val;
    y /= val;
}
