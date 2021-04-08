#pragma once

#include <SDL2/SDL.h>
#include <iostream>
#include "color.h"

class Application
{
    public:
        Application(int width, int height);
        ~Application();

        void Update();
        void Draw();
        void Circle(int cx, int cy, int r, SDL_Color color);

    private:
        SDL_Window   *m_window = NULL;
        SDL_Surface  *m_window_surface;
        SDL_Renderer *m_renderer = NULL;
        SDL_Event     m_window_event;

        int m_width;
        int m_height;
};
