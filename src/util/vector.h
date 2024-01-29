#include <iostream>

class Vector3 {
public:
    // Components
    float x;
    float y;
    float z;

    
    // Member Functions
    //
    Vector3(); // Initializes all Components to Zero
    Vector3(const float& _x, const float& _y, const float& _z); // Initializes Vector to corresponding Components

    ~Vector3();

    // Assignment
    Vector3 operator=(const Vector3& other);

    // Arithmetic
    Vector3 operator+(const Vector3& other) const;

    // Debugging
    void d_print() const;
};
