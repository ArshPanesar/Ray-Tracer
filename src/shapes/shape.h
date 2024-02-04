#pragma once
#include "../util/vector.h"
#include "../util/color.h"
#include "../util/ray.h"

class IShape {
public:
    enum class ShapeType {
        SPHERE = 0,
        TRIANGLE
    };

    ShapeType shape_type;

    Vector3 center_position;

    Color color = Color(25, 25, 112);

    // Lighting
    float diffuse_coef = 1.0f;
    float specular_coef = 1.0f;
    float ambient_coef = 1.0f;

public:

    // Every Shape must Implement this Function
    virtual bool ray_intersects(const Ray& ray, float* t) const = 0;
};
