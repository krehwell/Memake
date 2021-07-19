#pragma once

#include "Memake.h"
#include "Utils.h"

class Circle
{
public:
    Circle(int x, int y, int radius)
    {
        c_x = x;
        c_y = y;
        r = radius;
    }

    void Draw(SDL_Renderer *renderer, Color color)
    {
        filledEllipseColor(renderer, c_x, c_y, r, r, color);
    }

    int c_x;
    int c_y;
    int r;
};
