#pragma once

#include "Memake.h"
#include "Utils.h"

class Dot
{
public:
    Dot(int x, int y)
    {
        this->x = x;
        this->y = y;
    }

    void Draw(SDL_Renderer *renderer, Color color)
    {
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
        SDL_RenderDrawPoint(renderer, x, y);
    }

    int x;
    int y;
};
