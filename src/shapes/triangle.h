#pragma once
#include "shape.h"
#include "../util/ray.h"

class Triangle : public IShape {
public:
    Vector3 p1;
    Vector3 p2;
    Vector3 p3;

    Vector3 normal;

public:
    Triangle();

    void compute_normal();

    bool ray_intersects(const Ray& ray, float* t) const override;
};
