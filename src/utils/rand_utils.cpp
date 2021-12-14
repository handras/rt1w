#include "rand_utils.h"

#define M_PI 3.141592653589793

vec3 random_on_unit_sphere(){
    auto theta = 2 * M_PI * random_double();
    auto phi = acos(1 - 2 * random_double());
    auto x = sin(phi) * cos(theta);
    auto y = sin(phi) * sin(theta);
    auto z = cos(phi);
    return vec3({x, y, z});
}