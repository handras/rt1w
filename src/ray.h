#ifndef RAY_H
#define RAY_H

#include "vectors.h"

class ray {
public:
    vec3 orig;
    vec3 dir;

public:
    vec3 ray_at(double t);
};


#endif // RAY_H