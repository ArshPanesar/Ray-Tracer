#include "camera.h"

Camera::Camera() {

    center_position = Vector3(0.0f, 0.0f, -1.0f);
    window_size = Vector3(1.0f, 1.0f, 0.0f);
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

    // Converting Camera Coordinates to World Coordinates
    //
    // We can image pixel_coord bieng close to the World Origin
    // So we need to shift it towards the Camera's Origin in World Space
    Vector3 ray_origin = pixel_coord + center_position;

    // Generate a Ray
    Ray ray;
    ray.origin = ray_origin;
    // Keeping Orthographic for now
    ray.direction = Vector3(0.0f, 0.0f, center_position.normalized().z); 

    return ray;
}
