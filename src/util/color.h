#pragma once
#include "vector.h"

// Stores Color in RGB Format
// Range from 0-255    
class Color {
public:
    int r = 0;
    int g = 0;
    int b = 0;

public:
    Color(const int& _r, const int& _g, const int& _b) {

        set_color(_r, _g, _b);
    }

    void set_color(const int& _r, const int& _g, const int& _b) {

        r = _r;
        g = _g;
        b = _b;
    }
};
