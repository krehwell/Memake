#pragma once

#include "Memake.h"
#include "Utils.h"

class Triangle
{
public:
    Triangle(int x1, int y1, int x2, int y2, int x3, int y3)
    {
        this->x1 = x1;
        this->y1 = y1;
        this->x2 = x2;
        this->y2 = y2;
        this->x3 = x3;
        this->y3 = y3;
    }

    void Draw(SDL_Renderer* renderer, SDL_Color color)
    {
        filledTrigonColor(renderer, x1, y1, x2, y2, x3, y3, color);
    }

    int x1;
    int y1;
    int x2;
    int y2;
    int x3;
    int y3;
};
