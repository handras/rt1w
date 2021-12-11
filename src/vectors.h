#ifndef VECTORS_H
#define VECTORS_H

typedef float VEC3_IMPL_TYP;

typedef union vec3 {
    struct
    {
        VEC3_IMPL_TYP x, y, z;
    };
    struct
    {
        VEC3_IMPL_TYP r, g, b;
    };

    vec3 operator+(const vec3 &u) const {
        vec3 r = {this->x + u.x, this->y + u.y, this->z + u.z};
        return r;
    }

    vec3 operator-(const vec3 &u) const {
        vec3 r = {this->x - u.x, this->y - u.y, this->z - u.z};
        return r;
    }

    vec3 operator*(const vec3 &u) const {
        vec3 r = {this->x * u.x, this->y * u.y, this->z * u.z};
        return r;
    }

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wnarrowing"
    vec3 operator*(double u) const {
        vec3 r = {this->x * u, this->y * u, this->z * u};
        return r;
    }

    vec3 operator/(double u) const {
        vec3 r = {this->x / u, this->y / u, this->z / u};
        return r;
    }
#pragma GCC diagnostic pop

    double length() const;
    double length_squared() const;
    vec3 normalize() const;

} vec3;

double dot(const vec3 &u, const vec3 &v);
vec3 cross(const vec3 &u, const vec3 &v);

double vec3_length(vec3 *lh);
double vec3_length_squared(vec3 *lh);
vec3 vec3_unit(vec3 *lh);

#endif // VECTORS_H