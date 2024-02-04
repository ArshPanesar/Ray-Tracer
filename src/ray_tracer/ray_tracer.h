#pragma once
#include "camera.h"
#include "../util/image.h"
#include "../shapes/sphere.h"
#include "../shapes/triangle.h"
#include "../lighting/illumination.h"

#include <vector>
#include <memory>

class RayTracer {
private:

    Camera camera;

    // Sphere sphere;
    // Sphere sphere1;

    // Triangle triangle;

    // Using Smart Pointers to Avoid Memory Problems
    std::vector<std::unique_ptr<IShape>> objects_list;

    Image image;

    LightSource light_source;

    Illumination illumination;

    void draw_sphere(Sphere* sphere, const Ray& ray, const float& t, const int& x, const int& y);
    void draw_triangle(Triangle* triangle, const Ray& ray, const float& t, const int& x, const int& y);

public:
    RayTracer();
    ~RayTracer();

    void update();

    const Image& get_output_image() const;
};
