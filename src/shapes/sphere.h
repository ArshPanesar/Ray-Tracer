#pragma once
#include "shape.h"
#include "../util/ray.h"

class Sphere : public IShape {
public:

    // Radius
    float radius = 1.0f;

public:

    // Check if a Ray Intersects this Sphere
    // If Intersects, parameter t can be used to find the Intersection Point using the
    // Ray's Equation R(t) = p + dt 
    bool ray_intersects(const Ray& ray, float* t) const;
};

