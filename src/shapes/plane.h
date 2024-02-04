#pragma once
#include "shape.h"
#include "../util/ray.h"

class Plane : public IShape {
public:

    // Normal of the Plane
    Vector3 normal;

public:
    // Check if a Ray Intersects this Plane
    // If Intersects, parameter t can be used to find the Intersection Point using the
    // Ray's Equation R(t) = p + dt 
    bool ray_intersects(const Ray& ray, float* t) const override;
};

