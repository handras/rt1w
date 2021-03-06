#include "camera.h"

camera::camera(float aspect_ratio) {
    float viewport_height = 2.0;
    float viewport_width = aspect_ratio * viewport_height;
    float focal_length = 1.0;

    origin = vec3({0, 0, 0});
    horizontal = vec3({viewport_width, 0, 0});
    vertical = vec3({0, viewport_height, 0});
    lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3({0, 0, focal_length});
}

ray camera::get_ray(double u, double v) const {
    ray r = {origin, lower_left_corner + horizontal * u + vertical * v - origin};
    return r;
}
