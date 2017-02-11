#ifndef __VEC2_H__
#define __VEC2_H__

namespace wj
{
    struct Vec2
    {
        double x, y;

        Vec2(double x_ = 0, double y_ = 0);
        Vec2(const Vec2 &other);
        void operator= (const Vec2 &other);

        ~Vec2() {}

        // returns vector perpendicular to this vector with a magnitude of 1
        Vec2 normal() const;

        // returns vector perpendicular to this vector
        Vec2 perp() const;

        // magnitude of vector
        double magnitude() const;

        // returns a vector with only a direction and a magnitude of 1
        Vec2 direction() const;

        // converts this vector to only a direction with a magnitude of 1
        void normalize();

        // operators
        Vec2 operator+ (const Vec2 &other) const;
        Vec2 operator- (const Vec2 &other) const;
        Vec2 operator* (double val) const;
        Vec2 operator/ (double val) const;
        void operator+= (const Vec2 &other);
        void operator-= (const Vec2 &other);
        void operator*= (double val);
        void operator/= (double val);
    };
};


#endif /* end of include guard: __VEC2_H__ */
