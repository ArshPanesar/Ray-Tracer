#include "ray_tracer.h"

RayTracer::RayTracer() {
    
    // Set Image
    image.set_image(512, 512);
    
    // Set Camera
    camera.set_center_position(Vector3(-100.0f, -250.0f, -10.0f));
    camera.set_view((float)image.get_width(), (float)image.get_height(), 512.0f, 512.0f);
    camera.view_style = Camera::ViewStyle::PERSPECTIVE;
    

    // Set Triangle as Plane
    objects_list.push_back( std::make_unique<Triangle>() );
    Triangle* triangle = (Triangle*)objects_list[0].get();

    triangle->center_position = Vector3(0.0f, 0.0f, 0.0f);
    triangle->p1 = Vector3(-10000.0f, -500.0f, -100.0f);
    triangle->p2 = Vector3(-10000.0f, -500.0f, 100000.0f);
    triangle->p3 = Vector3(10000.0f, -500.0f, -100.0f);
    triangle->color = Color(127, 127, 127);    
    triangle->compute_normal();


    // Set Sphere 1
    objects_list.push_back( std::make_unique<Sphere>() );
    Sphere* sphere = (Sphere*)objects_list[1].get();

    sphere->center_position = Vector3(-100.0f, -400.0f, 500.0f);
    sphere->radius = 100.0f;

    // sphere1.center_position = Vector3(160.0f, -400.0f, 500.0f);
    // sphere1.radius = 100.0f;
    // sphere1.color = Color(1, 50, 32);

    // Light Source
    light_source.intensity = 60.0f;
    light_source.position = sphere->center_position + Vector3(-200.0f, 250.0f, 0.0f);
}

RayTracer::~RayTracer() {

    objects_list.clear();
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
            
            // Go through Objects List to Draw them
            for (int i = 0; i < objects_list.size(); ++i) {

                IShape* object = objects_list[i].get();
                if (object->ray_intersects(ray, &t)) {

                    switch(object->shape_type) {

                        case IShape::ShapeType::SPHERE:

                            draw_sphere((Sphere*)object, ray, t, x, y);
                            break;
                        
                        case IShape::ShapeType::TRIANGLE:
                        
                            draw_triangle((Triangle*)object, ray, t, x, y);
                            break;
                    }
                }
            }
        }
    }
}

void RayTracer::draw_sphere(Sphere* sphere, const Ray& ray, const float& t, const int& x, const int& y) {
            
    Vector3 intersection_point = ray.origin + ray.direction * t;
    Vector3 surface_normal = (intersection_point - sphere->center_position).normalized();

    // Calculate Lighting
    //float intensity = illumination.compute_diffuse_intensity(light_source, sphere, intersection_point, surface_normal, 2);
    float intensity = illumination.compute_ambient_intensity(light_source, 0.2f);

    // Mix Intensity with Color
    Color color = sphere->color;
    
    color.light_mix(intensity);
    
    image.set_pixel(x, y, color);
}

void RayTracer::draw_triangle(Triangle* triangle, const Ray& ray, const float& t, const int& x, const int& y) {

    Vector3 intersection_point = ray.origin + ray.direction * t;
    Vector3 surface_normal = triangle->normal;

    // Calculate Lighting
    //float intensity = illumination.compute_diffuse_intensity(light_source, triangle, intersection_point, surface_normal, 2);
    float intensity = illumination.compute_ambient_intensity(light_source, 0.2f);

    Ray shadow_ray;
    shadow_ray.origin = intersection_point;
    shadow_ray.direction = (light_source.position - intersection_point).normalized();
    
    // Mix Intensity with Color
    Color color = triangle->color;

    // if (sphere.ray_intersects(shadow_ray, &t)) {
    //     //color = Color(0, 0, 0);
    //     intensity = -10;
    // }
    // if (sphere1.ray_intersects(shadow_ray, &t)) {
    //     //color = Color(0, 0, 0);
    //     intensity -= 10;
    // }

    color.light_mix(intensity);

    image.set_pixel(x, y, color);    
}

const Image& RayTracer::get_output_image() const {
    return image;
}

