#ifndef __POLY_H__
#define __POLY_H__

#include "Vec2.hpp"
#include <cstdint>

namespace wj
{
    class Poly;
    
    class VertItr
    {
    public:
        VertItr(Poly &p, uint32_t index);
        VertItr(const VertItr &other);
        ~VertItr() {}
        bool operator!= (const VertItr &other);
        VertItr operator++ ();
        Vec2& operator* ();
        Vec2& operator-> ();
    private:
        Poly &_p;
        uint32_t _index;
    };

    class Poly
    {
    public:

        Poly();
        Poly(const Poly &other);
        void operator= (const Poly &other);
        ~Poly();

        void add_vert(const Vec2 vert);

        // minimum translation vector to not be colliding with another polygon
        // - returns 0 if they're not colliding
        Vec2 min_translation(const Poly &other) const;

        inline uint32_t num_verts() { return _num_verts; }
        Vec2 get_vert(uint32_t i) const;

        VertItr begin();
        VertItr end();

    private:

        friend class VertItr;
        Vec2 *_verts;
        uint32_t _num_verts; // how many verts are defined
        uint32_t _max_verts; // how big the array is

    };
};

#endif /* end of include guard: __POLY_H__ */
