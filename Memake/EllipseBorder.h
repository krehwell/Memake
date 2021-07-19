#pragma once

#include "Memake.h"
#include "Utils.h"

class EllipseBorder
{
public:
    EllipseBorder(int x, int y, int rx, int ry)
    {
        c_x = x;
        c_y = y;
        r_x = rx;
        r_y = ry;
    }

    void Draw(SDL_Renderer *renderer, Color color)
    {
        borderEllipse(renderer, c_x, c_y, r_x, r_y, color);
    }

    int c_x;
    int c_y;
    int r_x;
    int r_y;
};
