#include "camera.h"

Camera::Camera() {

    center_position = Vector3(0.0f, 0.0f, -1.0f);
    window_size = Vector3(1.0f, 1.0f, 0.0f);

    viewpoint_distance = 10.0f;
}

Camera::~Camera() {

}

void Camera::set_center_position(const Vector3& _position) {
    center_position = _position;
}

void Camera::set_view(const float& width, const float& height) {
    window_size = Vector3(width, height, 0.0f);
}

Ray Camera::project_ray(const float& pixel_x, const float& pixel_y) {

    // Pixel Positions are Local to the Image
    //
    // Converting Pixel Positions to Camera Space
    // Top-Left of Camera is the Starting Position of the Viewing Window
    Vector3 pixel_coord = Vector3( 
            pixel_x - (window_size.x / 2.0f), pixel_y - (window_size.y / 2.0f), 0.0f);

    // THIS CODE IS ONLY NEEDED IF CAMERA USES NORMALIZED COORDINATES [0, 1]
    //
    // Correcting these Coordinates to be at the Center of each Pixel
    //pixel_coord = pixel_coord + Vector3(0.5f, 0.5f, 0.0f);
    //pixel_coord = Vector3(pixel_coord.x / window_size.x, pixel_coord.y / window_size.y, 0.0f);

    // Converting Camera Coordinates to World Coordinates
    //
    // We can imagine pixel_coord bieng close to the World Origin
    // So we need to shift it towards the Camera's Origin in World Space
    Vector3 ray_origin = pixel_coord + center_position;

    // Generate a Ray
    Ray ray;
    ray.origin = ray_origin;
    // Keeping Orthographic for now
    ray.direction = Vector3(0.0f, 0.0f, center_position.normalized().z); 

    // Perspective Camera
    //Vector3 viewpoint = center_position * (viewpoint_distance * -1.0f);
    //ray.direction = ray_origin - viewpoint;

    return ray;
}
