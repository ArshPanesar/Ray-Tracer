#include "ray_tracer.h"

RayTracer::RayTracer() {
    
    // Set Image
    image.set_image(512, 512);
    
    // Set Camera
    camera.set_center_position(Vector3(0.0f, 0.0f, -1.0f));
    camera.set_view((float)image.get_width(), (float)image.get_height(), 512.0f, 512.0f);
    camera.view_style = Camera::ViewStyle::PERSPECTIVE;

    // Set Sphere
    sphere.center_position = Vector3(-100.0f, 0.0f, 100.0f);
    sphere.radius = 100.0f;

    sphere1.center_position = Vector3(100.0f, 0.0f, 500.0f);
    sphere1.radius = 100.0f;
    sphere1.color = Color(1, 50, 32);

    // Light Source
    light_source.intensity = 60.0f;
    light_source.position = sphere.center_position + Vector3(-20.0f, 160.0f, -100.0f);
}

RayTracer::~RayTracer() {

}

void RayTracer::update() {

    //camera.view_style = Camera::ViewStyle::PERSPECTIVE;
    // Compute Intersection
    for (int y = 0; y < image.get_height(); ++y) {
        for (int x = 0; x < image.get_width(); ++x) {

            // Compute Ray from Camera
            Ray ray = camera.project_ray(x, y);

            // Check Intersection with Object
            float t = 0.0f;
            if (sphere.ray_intersects(ray, &t)) {
                
                Vector3 intersection_point = ray.origin + ray.direction * t;
                Vector3 surface_normal = (intersection_point - sphere.center_position).normalized();

                // Calculate Lighting
                float intensity = illumination.compute_diffuse_intensity(light_source, &sphere, intersection_point, surface_normal, 2);

                // Mix Intensity with Color
                Color color = sphere.color;
                color.light_mix(intensity);
                //std::cout << (int)intensity << std::endl;

                image.set_pixel(x, y, color);
            }

            if (sphere1.ray_intersects(ray, &t)) {
                
                Vector3 intersection_point = ray.origin + ray.direction * t;
                Vector3 surface_normal = (intersection_point - sphere1.center_position).normalized();

                // Calculate Lighting
                float intensity = illumination.compute_diffuse_intensity(light_source, &sphere1, intersection_point, surface_normal, 2);

                // Mix Intensity with Color
                Color color = sphere1.color;
                color.light_mix(intensity);
                //std::cout << (int)intensity << std::endl;

                image.set_pixel(x, y, color);
            }
        }
    }
}

const Image& RayTracer::get_output_image() const {
    return image;
}
