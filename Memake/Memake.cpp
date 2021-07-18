#include "Memake.h"
#include <stdio.h>
#include <math.h>

Memake::Memake(int width, int height, string window_name)
{
    w = width;
    h = height;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cout << "Error Initializing Memake";
    }

    window = SDL_CreateWindow(window_name.c_str(), 0, 0, w, h, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, 0);
}

Memake::~Memake()
{
    SDL_DestroyWindow(window);
    SDL_FreeSurface(surface);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

SDL_Renderer* Memake::GetRenderer()
{
    return renderer;
}

SDL_Window* Memake::GetWindow()
{
    return window;
}

SDL_Surface* Memake::GetSurface()
{
    return surface;
}

int Memake::getMousePosX()
{
    return mousePosX;
}

int Memake::getMousePosY()
{
    return mousePosY;
}

void Memake::setMousePos()
{
    SDL_GetMouseState(&mousePosX, &mousePosY);
}

float Memake::getDeltaTime()
{
    return deltatime;
}

void Memake::setDeltaTime()
{
    prevTime = currentTime;
    currentTime = SDL_GetTicks();
    deltatime = (currentTime - prevTime) / 1000.0f;
}

void Memake::delay(int delay) {
    SDL_Delay(delay);
}

Color Memake::generateColor(Uint8 r, Uint8 g, Uint8 b)
{
    Color newColor = {r, g, b, 255};
    return newColor;
}

void Memake::close()
{
    keepWindowOpen = false;
}

char Memake::readKeyInput()
{
    SDL_Event userEvent;
    while (SDL_PollEvent(&userEvent))
    {
        switch(userEvent.type) {
            case SDL_TEXTINPUT:
                for(int i=0; i < SDL_TEXTINPUTEVENT_TEXT_SIZE; ++i) {
                    char c = userEvent.text.text[i];
                    // cancel if a non-ascii char is encountered
                    if(c < ' ' || c > '~') {
                        break;
                    } else  {
                        std::cout << c << std::endl;
                        return c;
                    }
                }
                break;
        }
    }
    return ' ';
}

void Memake::update(void (*draw)())
{
    SDL_Event event;

    while (keepWindowOpen)
    {
        setMousePos();
        setDeltaTime();

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                keepWindowOpen = false;
            }
            else if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    keepWindowOpen = false;
                }
            }
        }

        clear();

        // compose(); // set this to active to use unwrap wraper
        draw();

        SDL_RenderPresent(renderer);
    }
}

void Memake::clear()
{
    SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xFF);
    SDL_RenderClear(renderer);
}

// Debugger | Testing
void Memake::compose()
{
    Rectangle rect(100, 100, 20, 70);
    rect.Draw(renderer, Colmake.red);

    Circle circ(500, 300, 90);
    circ.Draw(renderer, Colmake.blue);

    Line line(550, 590, 590, 600);
    line.Draw(renderer, Colmake.pink);

    // unprovided by sdl
    Ellipse ellipse(100, 500, 90, 20);
    ellipse.Draw(renderer, Colmake.purple);

    Dot dot(600, 60);
    dot.Draw(renderer, Colmake.yellowgreen);

    Triangle triangle(50, 80, 60, 50, 90, 100);
    triangle.Draw(renderer, Colmake.yellow);

    Trapezoid trapezoid(700, 695, 720, 650, 780, 644, 740, 740);
    trapezoid.Draw(renderer, Colmake.plum);

    Vector2 a[] = {{140, 140}, {150, 130}, {120, 120}, {180, 120}, {200, 180}, {130, 240}};
    Polygon pol(a, 6);
    pol.Draw(renderer, Colmake.darkgoldenrod);

    Polkadot polkadot(400, 600, 500, 900);
    polkadot.Draw(renderer);

    EllipseBorder ellipseBorder(120, 700, 50, 90);
    ellipseBorder.Draw(renderer, Colmake.aqua);
}

// ============================================================================
/**
  * DRAW FUNCTION WRAPPER OF WRAPPER, user will only call this function
  */
// ============================================================================

void Memake::drawRect(int x, int y, int width, int height, Color color) {
    Rectangle rect(x, y, width, height);
    rect.Draw(renderer, color);
}

void Memake::drawCircle(int x, int y, int radius, Color color) {
    Circle circ(x, y, radius);
    circ.Draw(renderer, color);
}

void Memake::drawLine(int x1, int y1, int x2, int y2, Color color) {
    Line line(x1, y1, x2, y2);
    line.Draw(renderer, color);
}

void Memake::drawEllipse(int x, int y, int rx, int ry, Color color) {
    Ellipse ellipse(x, y, rx, ry);
    ellipse.Draw(renderer, color);
}

void Memake::drawDot(int x, int y, Color color) {
    Dot dot(x, y);
    dot.Draw(renderer, color);
}

void Memake::drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, Color color) {
    Triangle triangle(x1, y1, x2, y2, x3, y3);
    triangle.Draw(renderer, color);
}

void Memake::drawTrapezoid(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, Color color) {
    Trapezoid trapezoid(x1, y1, x2, y2, x3, y3, x4, y4);
    trapezoid.Draw(renderer, color);
}

void Memake::drawPolygon(Vector2 * edgesPos, int numOfEdges, Color color) {
    Polygon polygon(edgesPos, numOfEdges);
    polygon.Draw(renderer, color);
}

void Memake::drawPolkadot(int x1, int y1, int x2, int y2) {
    Polkadot polkadot(x1, y1, x2, y2);
    polkadot.Draw(renderer);
}

void Memake::drawFlower(int x, int y, int petalSize, int petalDistance, Color petalColor, Color centerPetalColor) {
    Ellipse upperLeftPetal(x - petalDistance, y - petalDistance, petalSize, petalSize);
    upperLeftPetal.Draw(renderer, petalColor);

    Ellipse upperRightPetal(x + petalDistance, y - petalDistance, petalSize, petalSize);
    upperRightPetal.Draw(renderer, petalColor);

    Ellipse lowerLeft(x - petalDistance, y + petalDistance, petalSize, petalSize);
    lowerLeft.Draw(renderer, petalColor);

    Ellipse lowerRight(x + petalDistance, y + petalDistance, petalSize, petalSize);
    lowerRight.Draw(renderer, petalColor);

    Ellipse middlePetal(x, y, petalSize, petalSize);
    middlePetal.Draw(renderer, centerPetalColor);
}

void Memake::drawEllipseBorder(int x, int y, int rx, int ry, Color color) {
    EllipseBorder ellipseBorder(x, y, rx, ry);
    ellipseBorder.Draw(renderer, color);
}

void Memake::drawPaddle(int x, int y, int width, int height, Color barColor, Color cornerColor) {
    Rectangle rect(x, y, width, height);
    Ellipse rPaddle(x, y + (height/2), height/2, height/2);
    Ellipse lPaddle(x + width, y + (height/2), height/2, height/2);

    lPaddle.Draw(renderer, cornerColor);
    rPaddle.Draw(renderer, cornerColor);
    rect.Draw(renderer, barColor);
}

void Memake::drawRadar(int x, int y, int radius, int count, Color color) {
    for(int i=1; i<=count; i++)
    {
        drawEllipseBorder(x, y, i*radius, i*radius, color);
    }
}

void Memake::drawFractalTree(int x, int y, int lineLength, int lineLengthSeed, int angle, int angleSeed, Color color) {
    FractalTree ft(x, y, lineLength, lineLengthSeed, angle, angleSeed);
    ft.Draw(renderer, color);
}
