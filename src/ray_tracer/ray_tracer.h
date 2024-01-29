#pragma once
#include "camera.h"
#include "../util/image.h"

class RayTracer {
private:

    Camera camera;

    Image image;

public:
    RayTracer();
    ~RayTracer();

    const Image& get_output_image() const;
};
