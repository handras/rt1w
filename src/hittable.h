#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"

struct hit_record {
    hittable& hit_object;
    vec3 p;
    double t;
};

class hittable {
public:
    virtual bool hit(const ray &r, double t_min, double t_max, hit_record &rec) const = 0;
};

#endif // HITTABLE_H