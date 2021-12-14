#ifndef MATERIALS_H
#define MATERIALS_H

#include "ray.h"
#include "rand_utils.h"

struct hit_record;

class material {
public:
    virtual bool scatter(
        const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const = 0;
};

class lambertian : public material {
public:
    lambertian(const vec3 &a) : albedo(a) {}

    virtual bool scatter(
        const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const override {
        auto scatter_direction = rec.normal + random_on_unit_sphere();
        scattered.orig = rec.p;
        scattered.dir = scatter_direction;
        attenuation = albedo;
        return true;
    }

public:
    vec3 albedo;
};

#endif // MATERIALS_H
