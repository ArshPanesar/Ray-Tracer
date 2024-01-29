#include "image.h"

Image::Image() {

    width = 0;
    height = 0;
    pixel_array = nullptr;
}

Image::~Image() {

    if (pixel_array != nullptr)
        delete pixel_array;

    pixel_array = nullptr;
    width = 0;
    height = 0;    
}

void Image::set_image(const int& _width, const int& _height) {

    width = _width;
    height = _height;

    if (pixel_array != nullptr)
        delete pixel_array;

    pixel_array = new unsigned char[width * height * 3]; // 3 Components: RGB
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            
            int id = (i * width + j) * 3;
            // Setting Default Color to Gray
            pixel_array[id + 0] = 100;
            pixel_array[id + 1] = 100;
            pixel_array[id + 2] = 100;
        }
    }
}

void Image::set_pixel(const int& x, const int& y, const Color& color) {

    if (x < 0 || x >= width || y < 0 || y >= height)
        return;

    int id = (y * width + x);
    pixel_array[id + 0] = color.r;
    pixel_array[id + 1] = color.b;
    pixel_array[id + 2] = color.g; 
}

const int Image::get_width() const {
    return width;
}

const int Image::get_height() const {
    return height;
}

unsigned char* Image::get_raw_data() const {
    return pixel_array;
}