#pragma once

#include <SDL2/SDL.h>
#include <iostream>

#include "Colmake.h"
#include "Vector2d.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Line.h"
#include "Ellipse.h"
#include "Dot.h"
#include "Triangle.h"
#include "Trapezoid.h"
#include "EllipseBorder.h"
#include "Polygon.h"
#include "Polkadot.h"

using namespace std;

class Memake
{
    public:
        Memake(int width, int height, string window_name);
        ~Memake();

        void update(void (*draw)());
        void setDeltaTime();
        bool getKeyboardInput(char key);

        /**
         * Close Program
         */
        void close();

        /**
         * Delay each call on every frame
         */
        void delay(int delay);

        /**
         * Return Delta Time of the framerate. useful to multiply with any movement speed to get consistent movement through out all display.
         */
        float getDeltaTime();

        /**
         * Get X Position of Mouse Cursor.
         */
        int getMousePosX();

        /**
         * Get Y Position of Mouse Cursor.
         */
        int getMousePosY();

        /**
         * Generate Color by given (red, green, blue) values.
         */
        Color generateColor(Uint8 r, Uint8 g, Uint8 b);

        /**
         * Draw Rectangle with a given (x,y) and (width, height) values.
         */
        void drawRect(int x, int y, int width, int height, Color color);

        /**
         * Draw Circle with a given (x,y) and radius values.
         */
        void drawCircle(int x, int y, int radius, Color color);

        /**
         * Draw Straight Line from given (x1,y1) to (x2, y2) values.
         */
        void drawLine(int x1, int y1, int x2, int y2, Color color);

        /**
         * Draw Ellipse/Custom Cirle with a given (x,y) and (rx,ry) or custom radius values.
         */
        void drawEllipse(int x, int y, int rx, int ry, Color color);

        /**
         * Draw Ellipse with no fill (just border) with a given (x,y) and (rx,ry) or custom radius values.
         */
        void drawEllipseBorder(int x, int y, int rx, int ry, Color color);

        /**
         * Draw Point/Dot to a specific x,y coordinate.
         */
        void drawDot(int x, int y, Color color);

        /**
         * Draw Triangle with the given (x1,y1), (x2,y2), and (x3,y3) values.
         */
        void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, Color color);

        /**
         * Draw Trapezoid with the given (x1,y1), (x2,y2), (x3,y3), (x4,y4) values.
         */
        void drawTrapezoid(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, Color color);

        /**
         * Draw Polygon with as many edges as intened by the given Array of Vec2.
         * ---
         * example: Vec2 edgesPos[] = {{60, 20}, {50, 50}, {700, 400}, {100, 200}, {900, 200}, {400, 800}}
         * then call it with: `DrawPolygon(edgesPos, numOfEdges)`;
         */
        void drawPolygon(Vector2 * edgesPos, int numOfEdges, Color color);

        /**
         * Draw custom polkadot pattern with the given (x1,y1) and (x2,y2) values.
         */
        void drawPolkadot(int x1, int y1, int x2, int y2);

        /**
         * Draw flower with 4 petals by specifying petalSize and petalDistance.
         */
        void drawFlower(int x, int y, int petalSize, int petalDistance, Color petalColor, Color centerPetalColor);

        /**
         * Draw paddle by specifying position and height values with additional bar and corner color.
         */
        void drawPaddle(int x, int y, int width, int height, Color barColor, Color cornerColor);

        /**
         * Draw radar with given (x,y) and radius with number of circle expanded
         */
        void drawRadar(int x, int y, int radius, int count, Color color);

    private:
        void draw();
        void clear();
        void compose();
        void setMousePos();

    private:
        SDL_Renderer *GetRenderer();
        SDL_Window *GetWindow();
        SDL_Surface *GetSurface();
        SDL_Renderer *renderer = NULL;
        SDL_Window   *window = NULL;
        SDL_Surface  *surface = NULL;

        int w;
        int h;

        int prevTime = 0, currentTime=0;
        int mousePosX, mousePosY;
        float deltatime;
        bool keepWindowOpen = true;
};
