#include "Memake.h"

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

SDL_Renderer* Memake::GetRenderer(){
    return renderer;
}

SDL_Window* Memake::GetWindow(){
    return window;
}

SDL_Surface* Memake::GetSurface(){
    return surface;
}

Memake::~Memake()
{
    SDL_DestroyWindow(window);
    SDL_FreeSurface(surface);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

void Memake::Update(void (*draw)())
{
    bool keep_window_open = true;

    SDL_Event event;

    while (keep_window_open)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                keep_window_open = false;
            }
            else if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    keep_window_open = false;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0xF, 0x0, 0xF, 1);
        for (int w = 0; w < 20 * 2; w++)
        {
            for (int h = 0; h < 20 * 2; h++)
            {
                int dx = 20 - w;
                int dy = 20 - h;
                if ((dx*dx + dy*dy) <= (20 * 20))
                {
                    SDL_RenderDrawPoint(renderer, 10 + dx, 10 + dy);
                }
            }
        }
        Clear();

        // Compose(); // set this to active to use unwrapper wrap
        draw();

        SDL_RenderPresent(renderer);
    }
}

void Memake::Clear()
{
    SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xFF);
    SDL_RenderClear(renderer);
}


// Debugger | Testing
void Memake::Compose()
{
    Rectangle rect(100, 100, 20, 70);
    rect.Draw(renderer, Colmake.red);

    Circle circ(500, 300, 90);
    circ.Draw(renderer, Colmake.blue);

    Line line(550, 590, 590, 600);
    line.Draw(renderer, Colmake.pink);

    Ellipse ellipse(100, 500, 90, 20);
    ellipse.Draw(renderer, Colmake.purple);

    Dot dot(600, 60);
    dot.Draw(renderer, Colmake.yellowgreen);

    Triangle triangle(50, 80, 60, 50, 90, 100);
    triangle.Draw(renderer, Colmake.yellow);

    Trapezoid trapezoid(700, 695, 720, 650, 780, 644, 740, 740);
    trapezoid.Draw(renderer, Colmake.plum);

    Vec2 a[] = {{60, 20}, {50, 50}, {700, 400}, {100, 200}, {900, 200}, {400, 800}};
    Polygon pol(a, 6);
    pol.Draw(renderer, Colmake.darkgoldenrod);
}

// ============================================================================
/**
  * DRAW FUNCTION WRAPPER OF WRAPPER, user will only call this function
  */
// ============================================================================

void Memake::DrawRect(int x, int y, int width, int height, SDL_Color color) {
    Rectangle rect(x, y, width, height);
    rect.Draw(renderer, color);
}

void Memake::DrawCircle(int x, int y, int radius, SDL_Color color) {
    Circle circ(x, y, radius);
    circ.Draw(renderer, color);
}

void Memake::DrawLine(int x1, int y1, int x2, int y2, SDL_Color color) {
    Line line(x1, y1, x2, y2);
    line.Draw(renderer, color);
}

void Memake::DrawEllipse(int x, int y, int rx, int ry, SDL_Color color) {
    Ellipse ellipse(x, y, rx, ry);
    ellipse.Draw(renderer, color);
}

void Memake::DrawDot(int x, int y, SDL_Color color) {
    Dot dot(x, y);
    dot.Draw(renderer, color);
}

void Memake::DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, SDL_Color color) {
    Triangle triangle(x1, y1, x2, y2, x3, y3);
    triangle.Draw(renderer, color);
}

void Memake::DrawTrapezoid(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, SDL_Color color) {
    Trapezoid trapezoid(x1, y1, x2, y2, x3, y3, x4, y4);
    trapezoid.Draw(renderer, color);
}

void Memake::DrawPolygon(Vec2 * edgesPos, int numOfEdges, SDL_Color color) {
    Polygon polygon(edgesPos, numOfEdges);
    polygon.Draw(renderer, color);
}
