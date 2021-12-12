#ifndef CAMERA_H
#define CAMERA_H

#include "ray.h"

class camera {
public:
    camera(float);
    ray get_ray(double u, double v) const;

private:
    vec3 origin;
    vec3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
};

#endif // CAMERA_H
