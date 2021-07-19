#pragma once

#include "Memake.h"

class Polkadot
{
public:
    Polkadot(int x1, int y1, int x2, int y2)
    {
        this->x1 = x1;
        this->y1 = y1;
        this->x2 = x2;
        this->y2 = y2;
    }

    void Draw(SDL_Renderer *renderer)
    {
        for (int _y = y1; _y < y2; _y++)
        {
            for (int _x = x1; _x < x2; _x++)
            {
                SDL_SetRenderDrawColor(renderer, (_x - 25) * (_x - 25) + (_y - 25) * (_y - 25), (_x - 50) * (_x - 50) + (_y - 50) * (_y - 50), (_x - 75) * (_x - 75) + (_y - 75) * (_y - 75), 255);
                SDL_RenderDrawPoint(renderer, _x, _y);
            }
        }
    }

    int x1;
    int y1;
    int x2;
    int y2;
};
