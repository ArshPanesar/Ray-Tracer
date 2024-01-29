#include "ray_tracer.h"

RayTracer::RayTracer() {

    // Test Vector Stuff

    Vector3 a(1.0f, 2.0f, 3.0f);

    Vector3 b = a + a;

    b.d_print();
}

RayTracer::~RayTracer() {
    // Nothing to do for now
}
