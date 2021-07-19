#pragma once

#include "Memake.h"
#include "Utils.h"

class Polygon
{
public:
    Polygon(Vector2 pos[], int numOfEdges)
    {
        this->pos = pos;
        this->numOfEdges = numOfEdges;
    }

    void Draw(SDL_Renderer *renderer, Color color)
    {
        int vx[numOfEdges], vy[numOfEdges];

        for (int i = 0; i < numOfEdges; i++)
        {
            vx[i] = pos[i].x;
            vy[i] = pos[i].y;
        }

        filledPolygonColor(renderer, vx, vy, numOfEdges, color);
    }

    Vector2 *pos;
    int numOfEdges;
};
