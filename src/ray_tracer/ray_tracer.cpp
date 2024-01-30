#include "ray_tracer.h"

RayTracer::RayTracer() {
    
    // Set Image
    image.set_image(512, 512);
    
    // Set Camera
    camera.set_center_position(Vector3(0.0f, 0.0f, 1000.0f));
    camera.set_view(image.get_width(), image.get_height());

    // Set Sphere
    sphere.center_position = Vector3(0.0f, 0.0f, 91.0f);
    sphere.radius = 100.0f;
}

RayTracer::~RayTracer() {

}

void RayTracer::update() {

    // Compute Intersection
    for (int y = 0; y < image.get_height(); ++y) {
        for (int x = 0; x < image.get_width(); ++x) {

            // Compute Ray from Camera
            Ray ray = camera.project_ray(x, y);

            //ray.direction.d_print("Ray's Direction");
            //ray.origin.d_print("Ray's Origin");

            // Check Intersection with Object
            float t = 0.0f;
            if (sphere.ray_intersects(ray, &t)) {

                image.set_pixel(x, y, Color(173, 216, 230));
            }
        }
    }
}

const Image& RayTracer::get_output_image() const {
    return image;
}
