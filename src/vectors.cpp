#include "math.h"

#include "vectors.h"

double vec3::length() {
    return sqrt(this->length_squared());
}

double vec3::length_squared() {

    return this->x * this->x + this->y * this->y + this->z * this->z;
}

vec3 vec3::normalize() {
    double l = this->length();
    vec3 r = *this / l;
    return r;
}

double dot(const vec3 &u, const vec3 &v) {
    return u.x * v.x +
           u.z * v.z +
           u.y * v.y;
}

vec3 cross(const vec3 &u, const vec3 &v) {
    vec3 r = {
        u.y * v.z - u.z * v.y,
        u.z * v.x - u.x * v.z,
        u.x * v.y - u.y * v.x,
    };
    return r;
}