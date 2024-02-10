#include "triangle.h"

Triangle::Triangle() {
    
    shape_type = IShape::ShapeType::TRIANGLE;
}

void Triangle::compute_normal() {

    Vector3 p1p2 = p2 - p1;
    Vector3 p1p3 = p3 - p1;

    normal = p1p2.cross(p1p3).normalized();
}

bool Triangle::ray_intersects(const Ray& ray, float* t) const {
    // compute the plane's normal
    Vector3 p1p2 = p2 - p1;
    Vector3 p1p3 = p3 - p1;
 
    // no need to normalize
    Vector3 normal = p1p2.cross(p1p3); // N
 
    // Step 1: finding P
    
    // check if the ray and plane are parallel.
    float NdotRayDirection = normal.dot(ray.direction);
    if (fabs(NdotRayDirection) < 0.0f) // almost 0
        return false; 

    // compute d parameter using equation 2
    float d = -normal.dot(p1);
    
    // compute t (equation 3)
    *t = -(normal.dot(ray.origin) + d) / NdotRayDirection;
    
    // check if the triangle is behind the ray
    if (*t < 0.0f) return false; // the triangle is behind
 
    // compute the intersection point using equation 1
    Vector3 P = ray.origin + ray.direction * (*t);
 
    // Step 2: inside-outside test
    Vector3 C; // vector perpendicular to triangle's plane
 
    // edge 1
    Vector3 edge1 = p2 - p1; 
    Vector3 vp1 = P - p1;
    C = edge1.cross(vp1);
    if (normal.dot(C) < 0) return false;
 
    // edge 2
    Vector3 edge2 = p3 - p2; 
    Vector3 vp2 = P - p2;
    C = edge2.cross(vp2);
    if (normal.dot(C) < 0)  return false;
 
    // edge 3
    Vector3 edge3 = p1 - p3; 
    Vector3 vp3 = P - p3;
    C = edge3.cross(vp3);
    if (normal.dot(C) < 0) return false;

    return true; // this ray hits the triangle
}
