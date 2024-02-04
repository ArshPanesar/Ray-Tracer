#include "plane.h"

bool Plane::ray_intersects(const Ray& ray, float* t) const {

    float ray_dir_dot_norm = ray.direction.dot(normal);

    if (ray_dir_dot_norm > 1e-6) {

        Vector3 position_to_origin = center_position - ray.origin;

        float t0 = position_to_origin.dot(normal) / ray_dir_dot_norm;
        *t = t0;
        
        if (t0 < 0.0f)
            return false;

        return true;
    }

    return false;
}