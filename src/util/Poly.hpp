#ifndef __POLY_H__
#define __POLY_H__

#include "Vec2.hpp"
#include <cstdint>

namespace wj
{
    class Poly
    {
    public:

        Poly(uint32_t num_verts);
        Poly(const Poly &other);
        void operator= (const Poly &other);
        ~Poly();

        void add_vert(const Vec2 vert);

        // minimum translation vector to not be colliding with another polygon
        // - returns 0 if they're not colliding
        Vec2 min_translation(const Poly &other) const;

        inline uint32_t num_verts() { return _num_verts; }

    private:

        Vec2 *_verts;
        uint32_t _num_verts, _last_added_vert;

    };
};

#endif /* end of include guard: __POLY_H__ */
