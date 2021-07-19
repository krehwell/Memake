#pragma once

#include "Memake.h"
#include "Utils.h"

class Trapezoid
{
public:
    Trapezoid(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
    {
        this->x1 = x1;
        this->y1 = y1;
        this->x2 = x2;
        this->y2 = y2;
        this->x3 = x3;
        this->y3 = y3;
        this->x4 = x4;
        this->y4 = y4;
    }

    void Draw(SDL_Renderer *renderer, Color color)
    {
        int vx[4], vy[4];
        vx[0] = x1;
        vx[1] = x2;
        vx[2] = x3;
        vx[3] = x4;
        vy[0] = y1;
        vy[1] = y2;
        vy[2] = y3;
        vy[3] = y4;

        filledPolygonColor(renderer, vx, vy, 4, color);
    }

    int x1;
    int y1;
    int x2;
    int y2;
    int x3;
    int y3;
    int x4;
    int y4;
};
