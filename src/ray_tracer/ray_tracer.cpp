#include "ray_tracer.h"

RayTracer::RayTracer() {
    
    // Set Image
    image.set_image(512, 512);
    
    // Set Camera
    camera.set_center_position(Vector3(0.0f, 100.0f, -1000.0f));
    camera.set_view((float)image.get_width(), (float)image.get_height(), 512.0f, 512.0f);
    camera.view_style = Camera::ViewStyle::PERSPECTIVE;
    
    // Set Triangle as Plane
    objects_list.push_back( std::make_unique<Triangle>() );
    Triangle* triangle = (Triangle*)objects_list[0].get();

    triangle->center_position = Vector3(0.0f, 0.0f, 0.0f);
    triangle->p1 = Vector3(-10000.0f, -500.0f, -100.0f);
    triangle->p2 = Vector3(-10000.0f, -500.0f, 100000.0f);
    triangle->p3 = Vector3(10000.0f, -500.0f, -100.0f);
    triangle->color = Color(156, 181, 203);    
    triangle->compute_normal();
    triangle->diffuse_coef = 1.0f;
    triangle->ambient_coef = 1.0f;
    triangle->specular_coef = 0.0f;

    // Set Sphere 1
    objects_list.push_back( std::make_unique<Sphere>() );
    Sphere* sphere = (Sphere*)objects_list[1].get();

    sphere->center_position = Vector3(-80.0f, -400.0f, 400.0f);
    sphere->radius = 100.0f;
    sphere->diffuse_coef = 1.0f;
    sphere->specular_coef = 1.0f;

    // Set Sphere 2
    objects_list.push_back( std::make_unique<Sphere>() );
    Sphere* sphere1 = (Sphere*)objects_list[2].get();

    sphere1->center_position = Vector3(140.0f, -400.0f, 550.0f);
    sphere1->radius = 100.0f;
    sphere1->color = Color(124, 10, 2);
    sphere1->diffuse_coef = 1.0f;
    sphere1->specular_coef = 4.f;

    // Set Camera Basis to Look at the Sphere 1
    Vector3 camera_basis_w = (sphere->center_position - camera.get_center_position()).normalized() * -1.0f;
    camera.set_camera_basis(camera_basis_w);

    camera_basis_w.d_print("W");

    // Light Source
    light_source.intensity = 1.5f;
    light_source.position = sphere->center_position + Vector3(-500.0f, 500.0f, -1000.0f);
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

                    // Draw the Object
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

    // Mix Intensity with Color
    Color color = sphere->color;
    
    // Lighting
    color = illumination.compute_lighting(light_source, sphere, intersection_point, surface_normal, ray);
    

    // Fill Shadows
    int num_shadows = count_shadows(sphere, intersection_point);
    if (count_shadows(sphere, intersection_point) > 0) {

        color = sphere->color;
    }

    image.set_pixel(x, y, color);
}

void RayTracer::draw_triangle(Triangle* triangle, const Ray& ray, const float& t, const int& x, const int& y) {

    Vector3 intersection_point = ray.origin + ray.direction * t;
    Vector3 surface_normal = triangle->normal;

    // Calculate Lighting
    Ray shadow_ray;
    shadow_ray.origin = intersection_point;
    shadow_ray.direction = (light_source.position - intersection_point).normalized();
    
    // Mix Intensity with Color
    Color color = triangle->color;
    
    color = illumination.compute_lighting(light_source, triangle, intersection_point, surface_normal, ray);

    // Fill Shadows
    int num_shadows = count_shadows(triangle, intersection_point);
    if (count_shadows(triangle, intersection_point) > 0) {

        color = triangle->color;
    }    

    image.set_pixel(x, y, color);    
}

int RayTracer::count_shadows(IShape* object, const Vector3& intersection_point) {

    int num_shadows = 0;

    // Draw Shadows
    // Go through the Objects List Again
    for (int j = 0; j < objects_list.size(); ++j) {
        
        IShape* other_object = objects_list[j].get();

        // Ignore Self
        if (object == other_object)
            continue;
        
        // Project a Ray from a Point on the Surface to the Light Source
        Ray shadow_ray;
        shadow_ray.origin = intersection_point;
        shadow_ray.direction = (light_source.position - shadow_ray.origin).normalized();

        float st = 0.0f;
        
        // If any Object collides with the Shadow Ray, then that Point in the Object is Shadowed  
        if (objects_list[j]->ray_intersects(shadow_ray, &st)) {

            // Point is in Shadow
            ++num_shadows;
        }
    }

    return num_shadows;
}

const Image& RayTracer::get_output_image() const {
    return image;
}

