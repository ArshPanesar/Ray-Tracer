#include "vector.h"

Vector3::Vector3() {
    
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
}

Vector3::Vector3(const float& _x, const float& _y, const float& _z) {

    x = _x;
    y = _y;
    z = _z;
}

Vector3::~Vector3() {

    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
}

Vector3 Vector3::operator=(const Vector3& other) {

    x = other.x;
    y = other.y;
    z = other.z;

    return *this;
}

Vector3 Vector3::operator+(const Vector3& other) const {

    return Vector3(x + other.x, y + other.y, z + other.z);
}


// Debugging

void Vector3::d_print() const {

    std::cout << "( " << x << ", " << y << ", " << z << " )" << std::endl; 
}