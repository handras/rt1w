#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"

class hittable;
class material;

struct hit_record {
    vec3 p;
    vec3 normal;
    material *mat;
    double t;
};

class hittable {
public:
    virtual bool hit(const ray &r, double t_min, double t_max, hit_record &rec) const = 0;
};

#endif // HITTABLE_H
