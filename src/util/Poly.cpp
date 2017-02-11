#include "Poly.hpp"
#include <cstdio>
#include <cassert>

wj::Poly::Poly(uint32_t num_verts) :
_verts(nullptr), _num_verts(num_verts), _last_added_vert(0)
{
    _verts = new Vec2[_num_verts];
}


wj::Poly::Poly(const Poly &other) :
_verts(nullptr), _num_verts(other._num_verts), _last_added_vert(0)
{
    _verts = new Vec2[_num_verts];

    for (int i = 0; i < _num_verts; ++i)
    {
        _verts[i] = other._verts[i];
    }
}


void wj::Poly::operator= (const Poly &other)
{
    _last_added_vert = 0;
    _num_verts = other._num_verts;
    if (_verts != nullptr) delete [] _verts;
    _verts = new Vec2[_num_verts];

    for (int i = 0; i < _num_verts; ++i)
    {
        _verts[i] = other._verts[i];
    }
}


wj::Poly::~Poly()
{
    delete [] _verts;
}


void wj::Poly::add_vert(const Vec2 vert)
{
    if (_last_added_vert >= _num_verts - 1)
    {
        printf("Added too many verts to polygon.\n");
        assert(0);
    }

    _verts[++_last_added_vert] = vert;
}


wj::Vec2 wj::Poly::min_translation(const Poly &other) const
{
    Vec2 v;
    assert(0);
    return v;
}
