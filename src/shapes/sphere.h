#pragma once
#include "../util/color.h"
#include "../util/ray.h"

class Sphere {
public:

    // Center of the Sphere in World Coordinates
    Vector3 center_position;

    // Radius
    float radius = 1.0f;

public:

    // Check if a Ray Intersects this Sphere
    // If Intersects, parameter t can be used to find the Intersection Point using the
    // Ray's Equation R(t) = p + dt 
    bool ray_intersects(const Ray& ray, float* t) const;
};

