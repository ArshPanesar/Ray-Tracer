#include "sphere.h"

Sphere::Sphere() {

    shape_type = ShapeType::SPHERE;
}

bool Sphere::ray_intersects(const Ray& ray, float* t) const {

    // Using Formula from Book
    //
    Vector3 ray_to_center = ray.origin - center_position;
    float ray_dir_dot = ray.direction.dot(ray.direction);

    // Using Arbritary Labels to Compute Geometric Data 
    float a = ray.direction.dot(ray_to_center) * ray.direction.dot(ray_to_center);
    float b = ray_to_center.dot(ray_to_center) - radius * radius;
    float c = ray_dir_dot * b;

    float discriminant_sq = a - c;

    if (discriminant_sq < 0.0f)
        return false;
    
    float discriminant = sqrtf(discriminant_sq);

    float x = (ray.direction * -1.0f).dot(ray_to_center);

    float numerator_plus = x + discriminant;
    float numerator_minus = x - discriminant;

    float t0 = numerator_plus / ray_dir_dot;
    float t1 = numerator_minus / ray_dir_dot;

    float t_min = std::min(t0, t1);
    float t_max = std::max(t0, t1);
    
    if (t_min > 0.0f)
        *t = t_min;
    else if (t_max > 0.0f)
        *t = t_max;
    else
        return false; // Nothing is Hit, Sphere is not in View of Camera
    
    return true;
}
