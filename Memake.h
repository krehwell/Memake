#pragma once

#include <SDL2/SDL.h>
#include <iostream>

#include "Color.h"
#include "Vec2.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Line.h"
#include "Ellipse.h"

using namespace std;

class Memake
{
    public:
        Memake(int width, int height, string window_name);
        ~Memake();

        void Update();
        void Draw();
        void Clear();
        void Compose();

    // private:
        SDL_Window   *window = NULL;
        SDL_Surface  *surface = NULL;
        SDL_Renderer *renderer = NULL;

        int w;
        int h;
};
