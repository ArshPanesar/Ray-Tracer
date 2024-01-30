#pragma once
#include "camera.h"
#include "../util/image.h"
#include "../shapes/sphere.h"

class RayTracer {
private:

    Camera camera;

    Sphere sphere;

    Image image;

public:
    RayTracer();
    ~RayTracer();

    void update();

    const Image& get_output_image() const;
};
