#pragma once

#include "memake.h"

class Circle
{
public:
    Circle(int x, int y, int radius)
    {
        c_x = x;
        c_y = y;
        r = radius;
    }

    void Draw(SDL_Renderer* renderer,  SDL_Color color)
    {
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 1);

        for (int w = 0; w < r * 2; w++)
        {
            for (int h = 0; h < r * 2; h++)
            {
                int dx = r - w;
                int dy = r - h;
                if ((dx*dx + dy*dy) <= (r * r))
                {
                    SDL_RenderDrawPoint(renderer, c_x + dx, c_y + dy);
                }
            }
        }
    }

    int c_x;
    int c_y;
    int r;
};
