#pragma once

#include <SDL2/SDL.h>
#include <iostream>
#include <functional>

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
#include "FractalTree.h"

#define lambda [&]()

class Memake
{
    public:
        Memake(int width, int height, std::string window_name);
        Memake(int width, int height, std::string window_name, Color backgroundColor);
        ~Memake();

        /**
         * Memake's Game Loop
         */
        void update(std::function<void()>draw);

        /**
         * Read what key is pressed
         * @returns {char} pressedKey
         */
        char readKeyInput();

        /**
         * Get max screen width
         */
        int getScreenW();

        /**
         * Get max screen height
         */
        int getScreenH();

        /**
         * Close Program
         */
        void close();

        /**
         * Delay call on every frame
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
         * Set screen background color
         */
        void setScreenBackgroundColor(Color color);

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
         * Draw Custom Polkadot Pattern with the given (x1,y1) and (x2,y2) values.
         */
        void drawPolkadot(int x1, int y1, int x2, int y2);

        /**
         * Draw Flower with 4 petals by specifying petalSize and petalDistance.
         */
        void drawFlower(int x, int y, int petalSize, int petalDistance, Color petalColor, Color centerPetalColor);

        /**
         * Draw Paddle by specifying position and height values with additional bar and corner color.
         */
        void drawPaddle(int x, int y, int width, int height, Color barColor, Color cornerColor);

        /**
         * Draw Radar with given (x,y) and radius with number of circle expanded
         */
        void drawRadar(int x, int y, int radius, int count, Color color);

        /**
         * Draw a Tree with given (x,y) additional with
         * @param {int} lineLength - initial bark size
         * @param {int} lineLengthSeed - randomizer for next bark to be growth (5-10 for best value)
         * @param {int} angle - angle rotation of tree (90 for straight)
         * @param {int} angleSeed - angle randomizer (15-25 for best value)
         * Best look ex: .drawFractalTree(400, 700, 70, 8, 90, 15, Colmake.cadetblue);
         */
        void drawFractalTree(int x, int y, int lineLength, int lineLengthSeed, int angle, int angleSeed, Color color);

    private:
        void clear();
        void compose();
        void setMousePos();
        void setDeltaTime();

    private:
        SDL_Renderer *GetRenderer();
        SDL_Window *GetWindow();
        SDL_Surface *GetSurface();
        SDL_Renderer *renderer = NULL;
        SDL_Window   *window = NULL;
        SDL_Surface  *surface = NULL;
        SDL_Event event;

        int w;
        int h;

        int prevTime = 0, currentTime=0;
        int mousePosX, mousePosY;
        float deltatime;
        bool keepWindowOpen = true;
        Color bgColor;
};
