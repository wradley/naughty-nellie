#include "Poly.hpp"
#include <cstdio>
#include <cassert>

wj::VertItr::VertItr(Poly &p, uint32_t index) :
_p(p), _index(index)
{}

wj::VertItr::VertItr(const VertItr &other) :
_p(other._p), _index(other._index)
{}


bool wj::VertItr::operator!= (const VertItr &other)
{
    return (_index != other._index);
}

wj::VertItr wj::VertItr::operator++ ()
{
    ++_index;
    return *this;
}

wj::Vec2& wj::VertItr::operator* ()
{
    return _p._verts[_index];
}

wj::Vec2& wj::VertItr::operator-> ()
{
    return _p._verts[_index];
}


wj::Poly::Poly() :
_verts(nullptr), _num_verts(0), _max_verts(0)
{
    static const int NUM_START_VERT_SIZE = 10;
    _verts = new Vec2[NUM_START_VERT_SIZE];
    _max_verts = NUM_START_VERT_SIZE;
}


wj::Poly::Poly(const Poly &other) :
_verts(nullptr), _num_verts(other._num_verts), _max_verts(other._max_verts)
{
    _verts = new Vec2[_max_verts];

    for (int i = 0; i < _num_verts; ++i)
    {
        _verts[i] = other._verts[i];
    }
}


void wj::Poly::operator= (const Poly &other)
{
    _max_verts = other._max_verts;
    _num_verts = other._num_verts;
    if (_verts != nullptr) delete [] _verts;
    _verts = new Vec2[_max_verts];

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
    // possible resize
    if (_num_verts >= _max_verts)
    {
        Vec2 *old = _verts;

        _max_verts *= 2;
        _verts = new Vec2[_max_verts];
        for (int i = 0; i < _num_verts; ++i) _verts[i] = old[i];
        delete [] old;
    }

    // add vert
    _verts[_num_verts++] = vert;
}


wj::Vec2 wj::Poly::min_translation(const Poly &other) const
{
    Vec2 v;
    assert(0);
    return v;
}

wj::Vec2 wj::Poly::get_vert(uint32_t i) const
{
    if (i < _num_verts) return _verts[i];
    else return {0,0};
}

wj::VertItr wj::Poly::begin()
{
    VertItr v(*this, 0);
    return v;
}

wj::VertItr wj::Poly::end()
{
    VertItr v(*this, _num_verts-1);
    return v;
}
