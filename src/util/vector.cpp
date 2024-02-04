#include "vector.h"

const Vector3 Vector3::X_AXIS = Vector3(1.0f, 0.0f, 0.0f);
const Vector3 Vector3::Y_AXIS = Vector3(0.0f, 1.0f, 0.0f);
const Vector3 Vector3::Z_AXIS = Vector3(0.0f, 0.0f, 1.0f);


Vector3::Vector3() {
    
    *this = X_AXIS;
}

Vector3::Vector3(const float& _x, const float& _y, const float& _z) {

    x = _x;
    y = _y;
    z = _z;
}

Vector3::Vector3(const Vector3& other) {
    
    x = other.x;
    y = other.y;
    z = other.z;
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

Vector3 Vector3::operator-(const Vector3& other) const {
    return Vector3(x - other.x, y - other.y, z - other.z);
}

Vector3 Vector3::operator*(const float& scalar) const {
    return Vector3(x * scalar, y * scalar, z * scalar);
}

Vector3 Vector3::operator/(const float& scalar) const {
    return Vector3(x / scalar, y / scalar, z / scalar);
}

float Vector3::magnitude() const {
    return sqrtf( x * x + y * y + z * z );
}

float Vector3::dot(const Vector3& other) const {
    return (x * other.x + y * other.y + z * other.z);
}

Vector3 Vector3::cross(const Vector3& other) const {
    return Vector3(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
}

Vector3 Vector3::normalized() const {
    return Vector3( *this / magnitude() );
}




// Debugging

void Vector3::d_print(const std::string& label) const {

    std::string msg = "";
    if (!label.empty())
        msg = label + " = ";
    
    std::cout << label << "( " << x << ", " << y << ", " << z << " )" << std::endl; 
}