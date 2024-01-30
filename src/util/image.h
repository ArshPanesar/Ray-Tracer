#pragma once
#include "color.h"

class Image {
private:

    int width;
    int height;

    unsigned char* pixel_array;

public:

    Image();
    ~Image();

    // Calling this Function is Necessary to Allocate Data for the Image
    void set_image(const int& _width, const int& _height);

    // Set a Pixel's Intensity
    // RGB from 0-255
    void set_pixel(const int& x, const int& y, const Color& color);

    // Getters
    const int get_width() const;
    const int get_height() const;
    // This is unsafe as anything can change the data
    // But its needed for OpenGL
    unsigned char* get_raw_data() const;
};
