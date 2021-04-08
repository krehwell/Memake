#include "memake.h"

Memake::Memake(int width, int height)
{
    SDL_Init(SDL_INIT_VIDEO);

    m_width = width;
    m_height = height;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(width, height, 0, &m_window, &m_renderer);
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 0);
    SDL_RenderClear(m_renderer);
    SDL_RenderPresent(m_renderer);
}

Memake::~Memake()
{
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void Memake::Update()
{

    bool keep_window_open = true;

    while(keep_window_open)
    {
        while(SDL_PollEvent(&m_window_event) > 0)
        {
            switch(m_window_event.type)
            {
                case SDL_QUIT:
                    keep_window_open = false;
                    break;
            }
        }
    }
}

void Memake::Draw()
{
    SDL_RenderPresent(m_renderer);
}

void Memake::Circle(int cx, int cy, int r, SDL_Color color)
{
    SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);

    for(int x=cx-r; x<=cx+r; x++)
    {
        for(int y=cy-r; y<=cy+r; y++)
        {
            if((std::pow(cy-y,2)+std::pow(cx-x,2)) <= std::pow(r,2))
            {
                SDL_RenderDrawPoint(m_renderer, x, y);
            }
        }
    }
}
