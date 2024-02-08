#include "camera.h"

Camera::Camera() {

    view_style = ViewStyle::ORTHOGRAPHIC;

    center_position = Vector3(0.0f, 0.0f, -1.0f);
    
    camera_basis_u = Vector3(1.0f, 0.0f, 0.0f);
    camera_basis_v = Vector3(0.0f, 1.0f, 0.0f);
    camera_basis_w = Vector3(0.0f, 0.0f, -1.0f);
    
    window_size = Vector3(1.0f, 1.0f, 0.0f);

    viewpoint_distance = 1000.0f;
}

Camera::~Camera() {

}

void Camera::set_center_position(const Vector3& _position) {
    center_position = _position;
}

void Camera::set_camera_basis(const Vector3& basis_w) {
    
    // Set the w basis
    camera_basis_w = basis_w;

    // Build u and v Vectors from w
    Vector3 t = camera_basis_w;
    Vector3 abs_t = Vector3(abs(t.x), abs(t.y), abs(t.z));

    // Change the smallest absolute component of t to 1
    if (abs_t.x <= abs_t.y && abs_t.x <= abs_t.z)
        t.x = 1.0f;
    else if (abs_t.y <= abs_t.x && abs_t.y <= abs_t.z)
        t.y = 1.0f;
    else if (abs_t.z <= abs_t.x && abs_t.z <= abs_t.y)
        t.z = 1.0f;

    //t = Vector3(0.0f, 1.0f, 0.0f);

    // Compute u and v
    camera_basis_v = t.cross(camera_basis_w).normalized();
    camera_basis_u = camera_basis_w.cross(camera_basis_v).normalized();

    // Print
    // camera_basis_u.d_print("U");
    // camera_basis_v.d_print("V");
    // camera_basis_w.d_print("W");
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

    // Correcting these Coordinates to be at the Center of each Pixel
    pixel_coord = pixel_coord + Vector3(0.5f, 0.5f, 0.0f);
    pixel_coord = Vector3((pixel_coord.x / image_size.x) * window_size.x, (pixel_coord.y / image_size.y) * window_size.y, 0.0f);
    pixel_coord = Vector3(pixel_x - (window_size.x / 2.0f), pixel_y - (window_size.y / 2.0f), 0.0f);


    // Generate a Ray
    Ray ray;
    // Set Direction according to View Style
    if (view_style == ViewStyle::ORTHOGRAPHIC) {
        
        ray.origin = camera_basis_u * pixel_coord.x + camera_basis_v * pixel_coord.y + center_position;
        ray.direction = camera_basis_w * -1.0f; 
    } else if (view_style == ViewStyle::PERSPECTIVE) {
        
        ray.origin = center_position;
        ray.direction = (camera_basis_w * -viewpoint_distance + camera_basis_u * pixel_coord.x + camera_basis_v * pixel_coord.y).normalized();
    }
    
    return ray;
}


const Vector3& Camera::get_center_position() const {
    return center_position;
}
