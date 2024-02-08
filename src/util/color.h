#pragma once
#include "vector.h"

// Stores Color in RGB Format
// Range from 0-255    
class Color {
public:
    unsigned char r = 0;
    unsigned char g = 0;
    unsigned char b = 0;

public:
    Color() {

        r = 0;
        b = 0;
        g = 0;
    }

    Color(const unsigned char& _r, const unsigned char& _g, const unsigned char& _b) {

        set_color(_r, _g, _b);
    }

    void set_color(const unsigned char& _r, const unsigned char& _g, const unsigned char& _b) {

        r = _r;
        g = _g;
        b = _b;
    }

    void mix_light(const float& intensity) {
        
        float new_r = (float)r * intensity;
        r = (unsigned char)( (new_r > 255) ? 255 : ( (new_r < 0) ? 0 : new_r ) );

        float new_g = (float)g * intensity;
        g = (unsigned char)( (new_g > 255) ? 255 : ( (new_g < 0) ? 0 : new_g ) );

        float new_b = (float)b * intensity;
        b = (unsigned char)( (new_b > 255) ? 255 : ( (new_b < 0) ? 0 : new_b ) );           
    }

    void weighted_combine(const Color& color, const float& w1, const float& w2) {

        float new_r = ((float)r * w1 + (float)color.r * w2);
        r = (unsigned char)( (new_r > 255) ? 255 : ( (new_r < 0) ? 0 : new_r ) );

        float new_g = ((float)g * w1 + (float)color.g * w2);
        g = (unsigned char)( (new_g > 255) ? 255 : ( (new_g < 0) ? 0 : new_g ) );
        
        float new_b = ((float)b * w1 + (float)color.b * w2);
        b = (unsigned char)( (new_b > 255) ? 255 : ( (new_b < 0) ? 0 : new_b ) );
    }
};
