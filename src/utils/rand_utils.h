#ifndef RAND_UTILS_H
#define RAND_UTILS_H

#include <random>
#include "vectors.h"

inline double random_double() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator(5 << 32 + 35 << 24 + 9 << 16 + 10 << 8 + 2);
    return distribution(generator);
}

inline double random_double(double min, double max) {
    return min + (max - min) * random_double();
}

vec3 random_on_unit_sphere();

#endif // RAND_UTILS_H
