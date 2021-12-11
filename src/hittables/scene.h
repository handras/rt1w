#ifndef SCENE_H
#define SCENE_H

#include "hittable.h"

#include <vector>

class scene : public hittable {
public:
    scene() {}
    ~scene() {}
    bool hit(const ray &r, double t_min, double t_max, hit_record &rec) const override;
    void add(hittable &object);

public:
    std::vector<hittable *> objects;
};

#endif // SCENE_H
