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

Memake::~Memake()
{
    SDL_DestroyWindow(window);
    SDL_FreeSurface(surface);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

void Memake::Update()
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

        Compose();

        SDL_RenderPresent(renderer);
    }
}

void Memake::Clear()
{
    SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xFF);
    SDL_RenderClear(renderer);
}


// Debugger
void Memake::Compose()
{
    Rectangle rect(100, 100, 20, 70);
    rect.Draw(renderer, red);

    Circle circ(500, 300, 90);
    circ.Draw(renderer, blue);

    Line line(550, 590, 590, 600);
    line.Draw(renderer, fuchsia);

    Ellipse ellipse(100, 500, 90, 20);
    ellipse.Draw(renderer, purple);
}
