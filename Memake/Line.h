#pragma once

#include "Memake.h"

class Line
{
public:
    Line(int x1, int y1, int x2, int y2)
    {
        this->x1 = x1;
        this->y1 = y1;
        this->x2 = x2;
        this->y2 = y2;
    }

    void Draw(SDL_Renderer *renderer, Color color)
    {
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 1);
        SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
    }

    int x1;
    int y1;
    int x2;
    int y2;
};
