#pragma once
#include "../util/color.h"

class LightSource {
public:
    
    // Position in World Coordinates
    Vector3 position;
    
    // Intensity of Light
    float intensity = 2.0f;    
};
