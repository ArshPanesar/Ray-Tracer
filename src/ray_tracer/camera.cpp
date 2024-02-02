#include "camera.h"

Camera::Camera() {

    view_style = ViewStyle::ORTHOGRAPHIC;

    center_position = Vector3(0.0f, 0.0f, -1.0f);
    window_size = Vector3(1.0f, 1.0f, 0.0f);

    viewpoint_distance = 1000.0f;
}

Camera::~Camera() {

}

void Camera::set_center_position(const Vector3& _position) {
    center_position = _position;
}

void Camera::set_view(const float& image_width, const float& image_height, const float& window_width, const float& window_height) {

    image_size = Vector3(image_width, image_height, 0.0f);
    window_size = Vector3(window_width, window_height, 0.0f);
}

Ray Camera::project_ray(const float& pixel_x, const float& pixel_y) {

    // Pixel Positions are Local to the Image
    //
    // Converting Pixel Positions to Camera Space
    // Top-Left of Camera is the Starting Position of the Viewing Window
    Vector3 pixel_coord = Vector3(pixel_x, pixel_y, 0.0f);

    // THIS CODE IS ONLY NEEDED IF CAMERA USES NORMALIZED COORDINATES [0, 1]
    //
    // Correcting these Coordinates to be at the Center of each Pixel
    pixel_coord = pixel_coord + Vector3(0.5f, 0.5f, 0.0f);
    pixel_coord = Vector3((pixel_coord.x / image_size.x) * window_size.x, (pixel_coord.y / image_size.y) * window_size.y, 0.0f);
    pixel_coord = Vector3(pixel_x - (window_size.x / 2.0f), pixel_y - (window_size.y / 2.0f), 0.0f);

    // Converting Camera Coordinates to World Coordinates
    //
    // We can imagine pixel_coord bieng close to the World Origin
    // So we need to shift it towards the Camera's Origin in World Space
    Vector3 ray_origin = pixel_coord + center_position;

    // Generate a Ray
    Ray ray;
    ray.origin = ray_origin;

    // Set Direction according to View Style
    if (view_style == ViewStyle::ORTHOGRAPHIC) {
      
        ray.direction = Vector3(0.0f, 0.0f, -center_position.normalized().z); 
    } else if (view_style == ViewStyle::PERSPECTIVE) {
        
        Vector3 viewpoint = Vector3(center_position.x, center_position.y, center_position.z - viewpoint_distance);
        ray.direction = (ray_origin - viewpoint).normalized();
        ray.origin = viewpoint;
    }
    
    return ray;
}
