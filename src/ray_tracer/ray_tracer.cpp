#include "ray_tracer.h"

RayTracer::RayTracer() {
    
    // Set Image
    image.set_image(8, 8);
}

RayTracer::~RayTracer() {

}

const Image& RayTracer::get_output_image() const {
    return image;
}
