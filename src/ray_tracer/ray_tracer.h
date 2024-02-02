#pragma once
#include "camera.h"
#include "../util/image.h"
#include "../shapes/sphere.h"
#include "../lighting/illumination.h"

class RayTracer {
private:

    Camera camera;

    Sphere sphere;
    Sphere sphere1;

    Image image;

    LightSource light_source;

    Illumination illumination;

public:
    RayTracer();
    ~RayTracer();

    void update();

    const Image& get_output_image() const;
};
