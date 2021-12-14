#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "materials.h"

class sphere : public hittable {
public:
    sphere() {}
    sphere(vec3 cen, double r, material* mat) : center(cen), radius(r), material(mat){};

    virtual bool hit(
        const ray &r, double t_min, double t_max, hit_record &rec) const override;

public:
    vec3 center;
    double radius;
    material* material;
};

#endif // SPHERE_H
