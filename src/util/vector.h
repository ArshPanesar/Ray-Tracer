#pragma once
#include <iostream>
#include <math.h>

class Vector3 {
public:
    // Components
    float x;
    float y;
    float z;

public:
    
    Vector3(); // Initializes all Components to Zero
    Vector3(const float& _x, const float& _y, const float& _z); // Initializes Vector to corresponding Components
    Vector3(const Vector3& other); // Copy Constructor

    ~Vector3();

    // Assignment
    Vector3 operator=(const Vector3& other);

    // Arithmetic
    Vector3 operator+(const Vector3& other) const;
    Vector3 operator-(const Vector3& other) const;
    Vector3 operator*(const float& scalar) const;
    Vector3 operator/(const float& scalar) const;

    // Vector Operations
    float magnitude() const;
    float dot(const Vector3& other) const;
    Vector3 cross(const Vector3& other) const;
    Vector3 normalized() const;
    
    // Debugging
    void d_print(const std::string& label = "") const;
};
