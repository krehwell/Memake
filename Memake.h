#pragma once

#include <SDL2/SDL.h>
#include <iostream>
#include <SDL2/SDL2_gfxPrimitives.h>

#include "Colmake.h"
#include "Vec2.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Line.h"
#include "Ellipse.h"
#include "Dot.h"
#include "Triangle.h"
#include "Trapezoid.h"

using namespace std;

class Memake
{
    public:
        Memake(int width, int height, string window_name);
        ~Memake();

        void Update(void (*draw)());
        void Draw();
        void Clear();
        void Compose();

        SDL_Renderer *GetRenderer();
        SDL_Window *GetWindow();
        SDL_Surface *GetSurface();

        /**
         * Draw Rectangle with a given (x,y) and (height,width) values.
         */
        void DrawRect(int x, int y, int width, int height, SDL_Color color);

        /**
         * Draw Circle with a given (x,y) and radius values.
         */
        void DrawCircle(int x, int y, int radius, SDL_Color color);

        /**
         * Draw Straight Line from given (x1,y1) to (x2, y2) values.
         */
        void DrawLine(int x1, int y1, int x2, int y2, SDL_Color color);

        /**
         * Draw Ellipse/Custom Cirle with a given (x,y) and (rx,ry) or custom radius values.
         */
        void DrawEllipse(int x, int y, int rx, int ry, SDL_Color color);

        /**
         * Draw Point/Dot to a specific x,y coordinate.
         */
        void DrawDot(int x, int y, SDL_Color color);

        /**
         * Draw Triangle with the given (x1,y1), (x2,y2), and (x3,y3) values.
         */
        void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, SDL_Color color);

        /**
         * Draw Trapezoid with the given (x1,y1), (x2,y2), (x3,y3), (x4,y4) values.
         */
        void DrawTrapezoid(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, SDL_Color color);

    private:
        SDL_Renderer *renderer = NULL;
        SDL_Window   *window = NULL;
        SDL_Surface  *surface = NULL;

        int w;
        int h;
};
