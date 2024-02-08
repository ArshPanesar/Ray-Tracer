#pragma once
#include "triangle.h"
#include <memory>

class Tetrahedron {
public:
    // Triangles of the Tetrahedron
    Triangle* t1;
    Triangle* t2;
    Triangle* t3;
    Triangle* base_triangle;

    // Top Point: Where the 3 Side Triangles will meet
    Vector3 top_point;

public:
    void set_up_triangles() {

        if (t1 == nullptr || t2 == nullptr || t3 == nullptr || base_triangle == nullptr)
            return;
        
        t1->specular_coef = 2.0f;
        t1->color = Color(128, 0, 128);
        t1->compute_normal();

        t2->specular_coef = 2.0f;
        t2->color = Color(128, 0, 128);
        t2->compute_normal();
        
        t3->specular_coef = 2.0f;
        t3->color = Color(128, 0, 128);
        t3->compute_normal();
        
        base_triangle->specular_coef = 2.0f;
        base_triangle->color = Color(128, 0, 128);
        base_triangle->compute_normal();
    }
};
