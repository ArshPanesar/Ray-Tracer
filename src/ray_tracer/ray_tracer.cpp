#include "ray_tracer.h"

RayTracer::RayTracer() {
    
    // Set Image
    image.set_image(1024, 1024);
    background_color = Color(100, 100, 100);

    // Set Camera
    camera.set_center_position(Vector3(0, 0, 200));
    camera.set_view((float)image.get_width(), (float)image.get_height(), 1024.0f, 1024.0f);
    camera.view_style = Camera::ViewStyle::PERSPECTIVE;
    
    // Set Triangle as Plane
    objects_list.push_back( std::make_unique<Triangle>() );
    Triangle* triangle = (Triangle*)objects_list[objects_list.size() - 1].get();

    triangle->p1 = Vector3(-10000.0f, -500.0f, -10000.0f);
    triangle->p2 = Vector3(-10000.0f, -500.0f, 100000.0f);
    triangle->p3 = Vector3(10000.0f, -500.0f, -10000.0f);
    triangle->center_position = triangle->p1;
    triangle->compute_normal();

    triangle->color = Color(156, 181, 203);    
    triangle->diffuse_coef = 0.2f;
    triangle->ambient_coef = 1.0f;
    triangle->specular_coef = 0.2f;


    // Set Sphere 1
    objects_list.push_back( std::make_unique<Sphere>() );
    Sphere* sphere1 = (Sphere*)objects_list[objects_list.size() - 1].get();

    sphere1->center_position = Vector3(-300.0f, -425.0f, 1200.0f);
    sphere1->radius = 75.0f;
    sphere1->color = Color(124, 10, 2);
    sphere1->diffuse_coef = 1.0f;
    sphere1->specular_coef = 4.0f;

    // Set Sphere 2
    objects_list.push_back( std::make_unique<Sphere>() );
    Sphere* sphere2 = (Sphere*)objects_list[objects_list.size() - 1].get();

    sphere2->center_position = Vector3(100.0f, -400.0f, 1350.0f);
    sphere2->radius = 100.0f;
    sphere2->diffuse_coef = 1.0f;
    sphere2->specular_coef = 3.0f;

    // Set up Tetrahedron
    // Allocate Resources
    objects_list.push_back( std::make_unique<Triangle>() );
    tetrahedron.base_triangle = (Triangle*)objects_list[ objects_list.size() - 1 ].get();

    objects_list.push_back( std::make_unique<Triangle>() );
    tetrahedron.t1 = (Triangle*)objects_list[ objects_list.size() - 1 ].get();

    objects_list.push_back( std::make_unique<Triangle>() );
    tetrahedron.t2 = (Triangle*)objects_list[ objects_list.size() - 1 ].get();

    objects_list.push_back( std::make_unique<Triangle>() );
    tetrahedron.t3 = (Triangle*)objects_list[ objects_list.size() - 1 ].get();

    // Set Up Top Point
    tetrahedron.top_point = Vector3(-100, -200, 1216);

    // Set Up Base of Tetrahedron
    tetrahedron.base_triangle->p1 = Vector3(0, -600, 1250);
    tetrahedron.base_triangle->p2 = Vector3(-100, -600, 1150);
    tetrahedron.base_triangle->p3 = Vector3(-200, -600, 1250);
    
    // Set Up Sides of Tetrahedron
    tetrahedron.t1->p1 = tetrahedron.base_triangle->p1;
    tetrahedron.t1->p2 = tetrahedron.base_triangle->p2;
    tetrahedron.t1->p3 = tetrahedron.top_point;

    tetrahedron.t2->p1 = tetrahedron.base_triangle->p2;
    tetrahedron.t2->p2 = tetrahedron.base_triangle->p3;
    tetrahedron.t2->p3 = tetrahedron.top_point;

    tetrahedron.t3->p1 = tetrahedron.base_triangle->p1;
    tetrahedron.t3->p2 = tetrahedron.base_triangle->p3;
    tetrahedron.t3->p3 = tetrahedron.top_point;

    // Complete Setup of Tetrahedron
    tetrahedron.set_up_triangles();

    // Set Camera Basis to Look at a Sphere
    Vector3 camera_look_offset = Vector3(0.0f, 100.0f, 0.0f);
    Vector3 camera_basis_w = (camera.get_center_position() - tetrahedron.top_point + camera_look_offset).normalized();
    camera.set_camera_basis(camera_basis_w);

    camera_basis_w.d_print("W");

    // Light Source
    light_source.intensity = 1.5f;
    light_source.position = sphere2->center_position + Vector3(-500.0f, 500.0f, -500.0f);

    // Control Variables
    lighting_enabled = true;
    shadows_enabled = true;
    glaze_enabled = true;

    illumination.diffuse_enabled = true;
    illumination.ambient_enabled = true;
    illumination.specular_enabled = true;
}

RayTracer::~RayTracer() {

    objects_list.clear();
}

void RayTracer::update() {

    for (int y = 0; y < image.get_height(); ++y) {
        for (int x = 0; x < image.get_width(); ++x) {

            Ray camera_ray = camera.project_ray(x, y);
            draw_pixel(camera_ray, x, y);
        }
    }
}

void RayTracer::switch_camera_style() {

    if (camera.view_style == Camera::ViewStyle::ORTHOGRAPHIC)
        camera.view_style = Camera::ViewStyle::PERSPECTIVE;
    else
        camera.view_style = Camera::ViewStyle::ORTHOGRAPHIC;
}

void RayTracer::draw_pixel(const Ray& ray, const int& x, const int& y) {

    float t = 0.0f;

    // Object to Draw at this Pixel
    IShape* closest_object = nullptr;
    float min_t = std::numeric_limits<float>::max(); // Maximum Float Value

    // Go through Objects List to Draw them
    for (int i = 0; i < objects_list.size(); ++i) {

        IShape* object = objects_list[i].get();
        if (object->ray_intersects(ray, &t)) {

            // Compute Parameters of the Object
            // Everything is stored in the last_hit_record field of the Object
            compute_ray_intersection(object, ray, t);

            // Check if it is the Closest Object
            if (t < min_t) {

                min_t = t;
                closest_object = object;
            }
        }
    }

    if (closest_object == nullptr) {
    
        image.set_pixel(x, y, background_color);
        return;
    }

    if (!lighting_enabled) {
        closest_object->last_hit_record.illuminated_color = closest_object->color;
        image.set_pixel(x, y, closest_object->color);
        return;
    }

    // Draw the Object
    // Mix Intensity with Color
    Color color = closest_object->color;
    color = illumination.compute_lighting(light_source, closest_object);

    // Fill Shadows
    int num_shadows = count_shadows(closest_object, closest_object->last_hit_record.intersection_point);
    if (num_shadows > 0) {
        
        // Set it to Unilluminated Base Color
        color = closest_object->color;
    }    
    closest_object->last_hit_record.illuminated_color = color;
    
    // Glazed
    color = get_glaze_on_object(closest_object);

    closest_object->last_hit_record.illuminated_color = color;
    
    image.set_pixel(x, y, color);   
}

void RayTracer::compute_ray_intersection(IShape* object, const Ray& ray, const float& t) {
    
    switch(object->shape_type) {

    case IShape::ShapeType::SPHERE:

        compute_ray_intersection((Sphere*)object, ray, t);
        break;
    
    case IShape::ShapeType::TRIANGLE:
    
        compute_ray_intersection((Triangle*)object, ray, t);
        break;
}
}

void RayTracer::compute_ray_intersection(Sphere* sphere, const Ray& ray, const float& t) {
            
    Vector3 intersection_point = ray.origin + ray.direction * t;
    Vector3 surface_normal = (intersection_point - sphere->center_position).normalized();

    // Store this Information for subsequent rays (recursive ray tracing)
    sphere->last_hit_record.intersection_point = intersection_point;
    sphere->last_hit_record.ray = ray;
    sphere->last_hit_record.surface_normal = surface_normal;
}

void RayTracer::compute_ray_intersection(Triangle* triangle, const Ray& ray, const float& t) {

    Vector3 intersection_point = ray.origin + ray.direction * t;
    Vector3 surface_normal = triangle->normal;

    // Store this Information for subsequent rays (recursive ray tracing)
    triangle->last_hit_record.intersection_point = intersection_point;
    triangle->last_hit_record.ray = ray;
    triangle->last_hit_record.surface_normal = surface_normal;
}

Color RayTracer::get_glaze_on_object(IShape* object) {
    
    if (!glaze_enabled)
        return object->last_hit_record.illuminated_color;

    LastRayHitRecord& last_hit_record = object->last_hit_record;

    // Build a Reflection Ray
    // From the book under topic "4.5.4 Mirror Reflection"
    Ray reflected_ray;
    reflected_ray.origin = last_hit_record.intersection_point;
    reflected_ray.direction = last_hit_record.ray.direction - last_hit_record.surface_normal * 2.0f * 
                                last_hit_record.ray.direction.dot(last_hit_record.surface_normal);
    reflected_ray.direction = reflected_ray.direction.normalized();

    IShape* other_object = nullptr;
    float min_rt = std::numeric_limits<float>::max();

    // Go through the Objects List
    for (int i = 0; i < objects_list.size(); ++i) {

        IShape* _other_object = objects_list[i].get();

        // Ignore Self
        if (object == _other_object)
            continue;
        
        float rt = 0.0f;
        
        // Get the First Object that the Ray Hits
        if (_other_object->ray_intersects(reflected_ray, &rt)) {
                    
            if (rt < min_rt) {

                min_rt = rt;
                other_object = _other_object;
            }            
        }
    }

    if (other_object == nullptr)
        return last_hit_record.illuminated_color;

    Color new_color = other_object->color;

    // Illuminated Color for Other Object needs to be re-calculated
    // This can be optimized!!!
    compute_ray_intersection(other_object, reflected_ray, min_rt);
    new_color = illumination.compute_lighting(light_source, other_object);
    // Fill Shadows
    int num_shadows = count_shadows(other_object, other_object->last_hit_record.intersection_point);
    if (num_shadows > 0) {
        
        // Set it to Unilluminated Base Color
        new_color = other_object->color;
    }    

    // Vector3 reflected_dir = reflected_ray.direction.normalized();
    // float dot = reflected_dir.dot(other_object->last_hit_record.surface_normal.normalized() * -1.0f);

    // dot = (dot < 0.0f) ? 0.0f : ( (dot > 1.0f) ? 1.0f : dot );

    new_color.weighted_combine(last_hit_record.illuminated_color, 0.25f, 0.75f);
        
    return new_color;
}

int RayTracer::count_shadows(IShape* object, const Vector3& intersection_point) {

    if (!shadows_enabled)
        return 0;

    int num_shadows = 0;

    // Project a Ray from a Point on the Surface to the Light Source
    Ray shadow_ray;
    shadow_ray.origin = intersection_point;
    shadow_ray.direction = (light_source.position - shadow_ray.origin).normalized();


    // Draw Shadows
    // Go through the Objects List Again
    for (int j = 0; j < objects_list.size(); ++j) {
        
        IShape* other_object = objects_list[j].get();

        // Ignore Self
        if (object == other_object)
            continue;
        
        float st = 0.0f;
        
        // If any Object collides with the Shadow Ray, then that Point in the Object is Shadowed  
        if (other_object->ray_intersects(shadow_ray, &st)) {

            // Point is in Shadow
            ++num_shadows;
        }
    }

    return num_shadows;
}

void RayTracer::render_animation() {

    std::cout << "Animation Started...\n"; 

    // Create Image to be Saved
    cimg_library::CImg<unsigned char> cimg_image(image.get_width(), image.get_height(), 1, 3);


    // Animating Camera Movement
    animation_data.camera_start_position = camera.get_center_position();
    animation_data.camera_end_position = camera.get_center_position() + Vector3(0, 200, -100);

    // Animating Spheres
    float speed = 1500.0f;
    Vector3 sphere1_move = Vector3(0, 0, 0);
    Vector3 sphere2_move = Vector3(0, 0, 0);
    
    int frame_count = animation_data.fps * animation_data.duration_sec;

    // Print Output
    std::cout << "Building Camera Animation. Screen may freeze." << "\n";
    for (int i = 0; i < (frame_count + 1); ++i) {
        
        // Compute New Position of Camera
        float t = (float)i / (float)frame_count;

        float next_x = lerp(animation_data.camera_start_position.x, animation_data.camera_end_position.x, t);
        float next_y = lerp(animation_data.camera_start_position.y, animation_data.camera_end_position.y, t);
        float next_z = lerp(animation_data.camera_start_position.z, animation_data.camera_end_position.z, t);

        Vector3 next_position(next_x, next_y, next_z);
        camera.set_center_position(next_position);
        
        // Compute Lerp Weight for Spheres 
        float dt = 1.0f / (float)animation_data.fps;

        // Compute Movement of Spheres
        sphere1_move = objects_list[1]->center_position - Vector3(tetrahedron.top_point.x, objects_list[1]->center_position.y, tetrahedron.top_point.z);
        sphere1_move = sphere1_move.cross(tetrahedron.top_point - Vector3(tetrahedron.top_point.x, 0.0f, tetrahedron.top_point.z));
        sphere1_move = sphere1_move.normalized() * speed;

        sphere2_move = objects_list[2]->center_position - Vector3(tetrahedron.top_point.x, objects_list[2]->center_position.y, tetrahedron.top_point.z);
        sphere2_move = sphere1_move.cross(tetrahedron.top_point - Vector3(tetrahedron.top_point.x, 0.0f, tetrahedron.top_point.z));
        sphere2_move = sphere1_move.normalized() * -speed;

        // Compute New Position of Sphere 1
        animation_data.sphere1_start_position = objects_list[1]->center_position;
        animation_data.sphere1_end_position = animation_data.sphere1_start_position + sphere1_move;
        next_x = lerp(animation_data.sphere1_start_position.x, animation_data.sphere1_end_position.x, dt);
        next_y = lerp(animation_data.sphere1_start_position.y, animation_data.sphere1_end_position.y, dt);
        next_z = lerp(animation_data.sphere1_start_position.z, animation_data.sphere1_end_position.z, dt);

        objects_list[1]->center_position = Vector3(next_x, next_y, next_z);

        // Compute New Position of Sphere 1
        animation_data.sphere2_start_position = objects_list[2]->center_position;
        animation_data.sphere2_end_position = animation_data.sphere2_start_position + sphere2_move;
        next_x = lerp(animation_data.sphere2_start_position.x, animation_data.sphere2_end_position.x, dt);
        next_y = lerp(animation_data.sphere2_start_position.y, animation_data.sphere2_end_position.y, dt);
        next_z = lerp(animation_data.sphere2_start_position.z, animation_data.sphere2_end_position.z, dt);

        objects_list[2]->center_position = Vector3(next_x, next_y, next_z);
        

        // Generate Output
        update();

        // Copy RayTracer's Output to Final Image
        unsigned char* data = image.get_raw_data();
        int id = 0;
        int cx = 0, cy = image.get_height() - 1;
        for (int y = 0; y < image.get_height(); ++y) {
            for (int x = 0; x < image.get_width(); ++x) {
                
                id = (y * image.get_width() + x) * 3;
                cx = x;
                
                unsigned char color[3];
                color[0] = data[id + 0];
                color[1] = data[id + 1];
                color[2] = data[id + 2];
                
                cimg_image.draw_point(cx, cy, color);
            }
            --cy;
        }
        
        // Generate Name
        std::string filename = animation_data.camera_output_filename;
        filename = filename + std::to_string(i);
        filename = filename + ".png";

        // Save the File
        try {
            cimg_image.save(filename.c_str());
        } catch (std::exception e) {
            // Do Nothing
        }
    }
    std::cout << "\nTotal Images Generated: " << frame_count << "\n";
}

const Image& RayTracer::get_output_image() const {
    return image;
}

