#pragma once
#include "camera.h"
#include "../util/image.h"
#include "../shapes/sphere.h"
#include "../shapes/triangle.h"
#include "../lighting/illumination.h"
#include "../shapes/tetrahedron.h"

#include <vector>
#include <memory>
#include <limits>

#include <CImg.h>

// Storing all Animation Data in this struct
struct AnimationData {
    
    int fps = 60;
    float duration_sec = 5.0f;

    // ***Animation Data***
    //
    Vector3 camera_start_position;
    Vector3 camera_end_position;

    Vector3 sphere1_start_position = Vector3(-1000, -425.0f, 1200.0f);
    Vector3 sphere1_end_position = Vector3(-300.0f, -425.0f, 1200.0f);

    Vector3 sphere2_start_position = Vector3(1000.0f, -400.0f, 1350.0f);
    Vector3 sphere2_end_position = Vector3(100.0f, -400.0f, 1350.0f);

    // Output
    std::string camera_output_filename = "C:\\Users\\Arsh Panesar\\Desktop\\UF Programming\\Graphics\\A1 - Ray Tracer\\Ray Tracer\\animations\\";
    // ***End of Animation Data***
};

class RayTracer {
private:

    Camera camera;

    // Complex Shapes
    Tetrahedron tetrahedron;

    // Using Smart Pointers to Avoid Memory Problems
    std::vector<std::unique_ptr<IShape>> objects_list;

    Image image;


    LightSource light_source;

    Illumination illumination;

    // Control Variables for Report
    bool lighting_enabled = true;
    bool shadows_enabled = true;
    bool glaze_enabled = true;

    Color background_color;

    AnimationData animation_data;

private:
    void draw_pixel(const Ray& ray, const int& x, const int& y);
    
    void compute_ray_intersection(IShape* object, const Ray& ray, const float& t);
    void compute_ray_intersection(Sphere* sphere, const Ray& ray, const float& t);
    void compute_ray_intersection(Triangle* triangle, const Ray& ray, const float& t);

    // Gets a Glaze on the Object
    Color get_glaze_on_object(IShape* object);

    // Count the Number of Shadows Falling at an Intersection Point of an Object
    int count_shadows(IShape* object, const Vector3& intersection_point);

    float lerp(const float& a, const float& b, const float& t) {
        return ( a + (b - a) * t );
    }

public:
    RayTracer();
    ~RayTracer();

    void update();

    // Switches between Orthographic and Perspective Camera
    void switch_camera_style();

    // Animation
    // Renders Images of an Animation
    void render_animation();

    const Image& get_output_image() const;
};
