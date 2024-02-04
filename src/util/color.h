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
    Color(const unsigned char& _r, const unsigned char& _g, const unsigned char& _b) {

        set_color(_r, _g, _b);
    }

    void set_color(const unsigned char& _r, const unsigned char& _g, const unsigned char& _b) {

        r = _r;
        g = _g;
        b = _b;
    }

    void light_mix(const int& intensity) {
        
        if ((int)r + intensity > 255)
            r = 255;
        else if ((int)r + intensity < 0)
            r = 0;
        else
            r += (unsigned char)intensity;
        
        if ((int)g + intensity > 255)
            g = 255;
        else if ((int)g + intensity < 0)
            g = 0;
        else
            g += (unsigned char)intensity;
        
        if ((int)b + intensity > 255)
            b = 255;
        else if ((int)b + intensity < 0)
            b = 0;
        else
            b += (unsigned char)intensity;
        
    }
};
