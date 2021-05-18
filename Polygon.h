#pragma once

#include "Memake.h"
#include "Utils.h"

class Polygon
{
public:
    Polygon(Vec2 pos[], int numOfEdges)
    {
        this->pos = pos;
        this->numOfEdges = numOfEdges;

    }

    void Draw(SDL_Renderer* renderer, SDL_Color color)
    {
        int vx[numOfEdges], vy[numOfEdges];

        for (int i = 0; i < numOfEdges; i++) {
            vx[i] = pos[i].x;
            vy[i] = pos[i].y;
        }

        filledPolygonColor(renderer,vx,vy,numOfEdges,color);
    }

    Vec2 *pos;
    int numOfEdges;
};
