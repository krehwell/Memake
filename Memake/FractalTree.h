#pragma once

#include "Memake.h"
#include "Utils.h"

class FractalTree
{
public:
    FractalTree(int x, int y, int lineLength, int lineLengthSeed, int angle, int angleSeed)
    {
        this->x = x;
        this->y = y;
        this->lineLength = lineLength;
        this->lineLengthSeed = lineLengthSeed;
        this->angle = angle;
        this->angleSeed = angleSeed;
    }

    void Draw(SDL_Renderer *renderer, Color color)
    {
        RenderTree(renderer, x, y, lineLength, lineLengthSeed, angle, angleSeed, color);
    }

    int x;
    int y;
    int lineLength;
    int lineLengthSeed;
    int angle;
    int angleSeed;
};
