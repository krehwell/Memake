#pragma once

#include <SDL2/SDL.h>
#include <iostream>
#include "color.h"

using namespace std;

class Memake
{
    public:
        Memake(int width, int height, string window_name);
        ~Memake();

        void Update();
        void Draw();
        void Clear();

    // private:
        SDL_Window   *window = NULL;
        SDL_Surface  *surface;
        SDL_Renderer *renderer = NULL;
        SDL_Event     event;

        int w;
        int h;
};
