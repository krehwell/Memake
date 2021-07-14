#pragma once

#include "Memake.h"
#include "Utils.h"

class Flower
{
public:
    Flower(int x, int y, int petalSize, int petalDistance)
    {
        this->flowerX = x;
        this->flowerY = y;
        this->petalSize = petalSize;
        this->petalDistance = petalDistance;
    }

    void Draw(SDL_Renderer* renderer, Color petalColor, Color centerPetalColor)
    {
        Ellipse upperLeftPetal(flowerX - petalDistance, flowerY - petalDistance, petalSize, petalSize);
        upperLeftPetal.Draw(renderer, petalColor);

        Ellipse upperRightPetal(flowerX + petalDistance, flowerY - petalDistance, petalSize, petalSize);
        upperRightPetal.Draw(renderer, petalColor);

        Ellipse lowerLeft(flowerX - petalDistance, flowerY + petalDistance, petalSize, petalSize);
        lowerLeft.Draw(renderer, petalColor);

        Ellipse lowerRight(flowerX + petalDistance, flowerY + petalDistance, petalSize, petalSize);
        lowerRight.Draw(renderer, petalColor);

        Ellipse middlePetal(flowerX, flowerY, petalSize, petalSize);
        middlePetal.Draw(renderer, centerPetalColor);
    }

    int flowerX;
    int flowerY;
    int petalDistance;
    int petalSize;
};
