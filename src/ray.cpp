#include "ray.h"

vec3 ray::ray_at(double t) {
    vec3 res = this->orig + this->dir * t;
    return res;
}