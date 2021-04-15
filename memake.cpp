#include "memake.h"

Memake::Memake(int width, int height, string window_name)
{
    w = width;
    h = height;

    SDL_Init(SDL_INIT_VIDEO);
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
        Clear();

        SDL_RenderPresent(renderer);
    }
}

void Memake::Clear()
{
    SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xFF);
    SDL_RenderClear(renderer);
}
