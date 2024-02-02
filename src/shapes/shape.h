#pragma once
#include "../util/vector.h"
#include "../util/color.h"

class IShape {
public:
    Vector3 center_position;

    Color color = Color(25, 25, 112);
};
