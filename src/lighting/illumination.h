#pragma once
#include "../shapes/shape.h"
#include "light_source.h"

class Illumination {
public:
    float ambient_intensity = 1.05f;

    // Specular Shading using Phong Model
    // This variable refers to 'n' power on the max function
    float specular_power = 8;

public:

    Color compute_lighting(const LightSource& source, const IShape* shape, const Vector3& intersection_point, const Vector3& surface_normal, const Ray& ray) {

        Color final_color = shape->color;

        // Diffuse Shading
        Vector3 v = (source.position - shape->center_position).normalized();

        float n_dot_v = surface_normal.dot(v);
        float max_n_dot_v = std::max(0.0f, n_dot_v);

        float diffuse_intensity = shape->diffuse_coef * max_n_dot_v;

        // Ambient Shading
        float ambient_shading = shape->ambient_coef * ambient_intensity;


        // Specular (Phong) Shading
        Vector3 vr = (surface_normal * 2.0f * (n_dot_v) - v).normalized();
        Vector3 ve = (ray.origin - intersection_point).normalized();

        float max_vr_dot_ve = std::max(0.0f, vr.dot(ve));
        float power_max_vr_dot_ve = std::pow(max_vr_dot_ve, specular_power);
        float specular_intensity = shape->specular_coef * power_max_vr_dot_ve;

        // Calculate Total Intensity of Light
        float final_intensity = ambient_shading + source.intensity * ( diffuse_intensity + specular_intensity );

        final_color.mix_light(final_intensity);
        return final_color;
    }
};
