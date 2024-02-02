#pragma once
#include "../shapes/shape.h"
#include "light_source.h"

class Illumination {
public:

    float compute_diffuse_intensity(const LightSource& source, const IShape* shape, const Vector3 intersection_point, 
                                    const Vector3 surface_normal, const float& diffuse_coef = 1.0f) {
        
        Vector3 v = source.position - shape->center_position;

        float n_dot_v = surface_normal.dot(v.normalized());
        n_dot_v = std::max(0.0f, n_dot_v);

        float intensity = diffuse_coef * source.intensity * n_dot_v;
        return intensity;
    }
};
