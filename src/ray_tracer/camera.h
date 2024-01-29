#pragma once
#include "../util/ray.h"

class Camera {
private:

    // Center of the Camera's Window in World Coordinates
    Vector3 center_position;

    // Distance of Viewpoint from Camera's Position: For Perspective Camera
    float viewpoint_distance;

    // Camera Window
    //
    // Width and Height of the Window: Should Be Kept Same as the Image
    Vector3 window_size;

public:

    Camera();
    ~Camera();

    // Set Center Position of Camera in World Coordinates (Camera Basis)
    void set_center_position(const Vector3& _position);

    // Set Viewing Window of the Camera (Top and Left should be in World Coordinates)
    // Keep Width and Height the same as the Output Image
    void set_view(const float& width, const float& height);

    // Project a Ray into the World
    // Ray's Origin will be determined by Camera View: Perspective or Orthographic
    // The Pixel Positions of the Image will be converted to the Camera's local coordinates with
    // Camera's center as the local origin. Then, a Ray will be cast in World Coordinates.
    Ray project_ray(const float& pixel_x, const float& pixel_y);
};
