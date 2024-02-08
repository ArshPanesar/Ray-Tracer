#pragma once
#include "../util/vector.h"
#include "../util/color.h"
#include "../util/ray.h"

// Information from the Last Ray Intersection with this Shape
struct LastRayHitRecord {

    Ray ray;
    Vector3 intersection_point;
    Vector3 surface_normal;
    Color illuminated_color;

    LastRayHitRecord() {}
};


class IShape {
public:
    enum class ShapeType {
        SPHERE = 0,
        TRIANGLE
    };

    ShapeType shape_type;

    LastRayHitRecord last_hit_record;

    Vector3 center_position;

    Color color = Color(25, 25, 112);

    // Lighting
    float diffuse_coef = 1.0f;
    float specular_coef = 1.0f;
    float ambient_coef = 1.0f;
    
public:
    IShape() {}

    // Every Shape must Implement this Function
    virtual bool ray_intersects(const Ray& ray, float* t) const = 0;
};
