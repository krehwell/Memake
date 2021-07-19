#pragma once

#include "Memake.h"

class Rectangle
{
public:
    Rectangle(int x, int y, int width, int height)
    {
        rect.x = x;
        rect.y = y;
        rect.w = width;
        rect.h = height;
    }

    void Draw(SDL_Renderer *renderer, Color color)
    {
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 1);
        SDL_RenderFillRect(renderer, &rect);
    }

    SDL_Rect rect{};
};
