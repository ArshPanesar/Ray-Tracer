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
};
