#pragma once
#include "../util/ray.h"

class Camera {
private:

    // Center of the Camera's Window in World Coordinates (Camera Basis)
    Vector3 center_position;

    // Distance of Viewpoint from Camera's Position: For Perspective Camera
    float viewpoint_distance;

    // Camera Window
    Vector3 window_size;

    // Width and Height of the Image
    Vector3 image_size;

public:
    enum class ViewStyle {
        ORTHOGRAPHIC = 0,
        PERSPECTIVE
    };

    ViewStyle view_style;

public:

    Camera();
    ~Camera();

    // Set Center Position of Camera in World Coordinates (Camera Basis)
    void set_center_position(const Vector3& _position);

    // Set Viewing Window of the Camera (Top and Left should be in World Coordinates)
    // Keep Width and Height the same as the Output Image
    void set_view(const float& image_width, const float& image_height, const float& window_width, const float& window_height);

    // Project a Ray into the World
    // Ray's Origin will be determined by Camera View: Perspective or Orthographic
    // The Pixel Positions of the Image will be converted to the Camera's local coordinates with
    // Camera's center as the local origin. Then, a Ray will be cast in World Coordinates.
    Ray project_ray(const float& pixel_x, const float& pixel_y);
};
