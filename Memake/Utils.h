#pragma once
#include <cmath>
#include <cstdlib>
#include <utility>
#include <SDL2/SDL.h>

/*
 *
 * COMMON UTILS
 *
 */
inline int random(int min, int max)
{
    int ret = rand() % (max + 1);
    if (ret < min)
    {
        ret += min;
    }
    return ret;
}

double inline round(double x) { return floor(x + 0.5); }
double inline fPart(double x) { return x - floor(x); }
double inline rfPart(double x) { return 1 - fPart(x); }

/*
 *
 * FRACTAL TREE UTILS
 *
 */
inline void plot(SDL_Renderer *renderer, int x, int y, double brightness, SDL_Color color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, brightness * 0xFF);
    SDL_RenderDrawPoint(renderer, x, y);
}

inline void wuLine(SDL_Renderer *renderer, double x0, double y0, double x1, double y1, SDL_Color color)
{
    bool steep = fabs(y1 - y0) > fabs(x1 - x0);

    if (steep)
    {
        std::swap(x0, y0);
        std::swap(x1, y1);
    }

    if (x0 > x1)
    {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }

    double dx = x1 - x0;
    double dy = y1 - y0;

    double gradient = dx == 0.0 ? 1.0 : dy / dx;

    double xEnd = round(x0);
    double yEnd = y0 + gradient * (xEnd - x0);
    double xGap = rfPart(x0 + 0.5);
    double xPixel1 = xEnd;
    double yPixel1 = floor(yEnd);

    if (steep)
    {
        plot(renderer, yPixel1, xPixel1, rfPart(yEnd) * xGap, color);
        plot(renderer, yPixel1 + 1, xPixel1, fPart(yEnd) * xGap, color);
    }

    else
    {
        plot(renderer, xPixel1, yPixel1, rfPart(yEnd) * xGap, color);
        plot(renderer, xPixel1, yPixel1 + 1, fPart(yEnd) * xGap, color);
    }

    double yIntersection = yEnd + gradient;

    xEnd = round(x1);
    yEnd = y1 + gradient * (xEnd - x1);
    xGap = fPart(x1 + 0.5);
    double xPixel2 = xEnd;
    double yPixel2 = floor(yEnd);

    if (steep)
    {
        plot(renderer, yPixel2, xPixel2, rfPart(yEnd) * xGap, color);
        plot(renderer, yPixel2 + 1, xPixel2, fPart(yEnd) * xGap, color);

        for (int x = xPixel1 + 1; x <= (xPixel2 - 1); x++)
        {
            plot(renderer, yIntersection, x, rfPart(yIntersection), color);
            plot(renderer, yIntersection + 1, x, fPart(yIntersection), color);
            yIntersection += gradient;
        }
    }

    else
    {
        plot(renderer, xPixel2, yPixel2, rfPart(yEnd) * xGap, color);
        plot(renderer, xPixel2, yPixel2 + 1, fPart(yEnd) * xGap, color);

        for (int x = xPixel1 + 1; x <= (xPixel2 - 1); x++)
        {
            plot(renderer, x, yIntersection, rfPart(yIntersection), color);
            plot(renderer, x, yIntersection + 1, fPart(yIntersection), color);
            yIntersection += gradient;
        }
    }
}

inline void RenderTree(SDL_Renderer *renderer, int startX, int startY, int lineLength, int lineLengthSeed, int angle, int angleSeed, SDL_Color color = {255, 255, 255, 255})
{
    // Uncomment for slow animation
    //SDL_RenderPresent(renderer);

    double angleInRad = ((double)angle * M_PI) / 180.0;

    int endX = (int)(startX - (double)lineLength * cos(angleInRad));
    int endY = (int)(startY - (double)lineLength * sin(angleInRad));

    // COLOR RANDOMIZER
    // Uint8 re = random(0, 255);
    // Uint8 ge = random(0, 255);
    // Uint8 be = random(0, 255);
    // SDL_Color color = {re, ge, be, 255};

    wuLine(renderer, startX, startY, endX, endY, color);

    if (lineLength > 20)
    {
        RenderTree(renderer, endX, endY, lineLength - lineLengthSeed, lineLengthSeed, angle + angleSeed, angleSeed, color);
        RenderTree(renderer, endX, endY, lineLength - lineLengthSeed, lineLengthSeed, angle - angleSeed, angleSeed, color);

        // Uncomment for a little faster animation
        // SDL_RenderPresent(renderer);
    }
}

/*
   SDL2_gfxPrimitives.c: graphics primitives for SDL2 renderers
   Copyright (C) 2012-2014  Andreas Schiffler
   Modifications and additions for BBC BASIC (C) 2016-2020 Richard Russell
   This software is provided 'as-is', without any express or implied
   warranty. In no event will the authors be held liable for any damages
   arising from the use of this software.
   Permission is granted to anyone to use this software for any purpose,
   including commercial applications, and to alter it and redistribute it
   freely, subject to the following restrictions:
   1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.
   2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
   3. This notice may not be removed or altered from any source
   distribution.
   Andreas Schiffler -- aschiffler at ferzkopp dot net
   Richard Russell -- richard at rtrussell dot co dot uk
   */

/*
 *
 * VAR UTILS
 *
 */
/* CACHE FOR TELLING THINGS IN DRAWING FOR POLYGON */
static int *primitivesPolyIntsGlobal = NULL;
static int primitivesPolyAllocatedGlobal = 0;

/*
 *
 * GENERICS UTILS
 *
 */
inline int vlineRGBA(SDL_Renderer *renderer, int x, int y1, int y2, SDL_Color color)
{
    int result = 0;
    // if (color.a != 255) result |= SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    result |= SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    result |= SDL_RenderDrawLine(renderer, x, y1, x, y2);
    return result;
}

inline int hlineRGBA(SDL_Renderer *renderer, int x1, int x2, int y, SDL_Color color)
{
    int result = 0;
    // if (color.a != 255) result |= SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    result |= SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    result |= SDL_RenderDrawLine(renderer, x1, y, x2, y);
    return result;
}

inline int hline(SDL_Renderer *renderer, int x1, int x2, int y)
{
    return SDL_RenderDrawLine(renderer, x1, y, x2, y);
}

inline int _gfxPrimitivesCompareInt(const void *a, const void *b)
{
    return (*(const int *)a) - (*(const int *)b);
}

/*
 *
 * ELLIPSE FUNCTIONS UTILS
 *
 */
inline int filledEllipseRGBA(SDL_Renderer *renderer, int x, int y, int rx, int ry, SDL_Color color)
{
    int result;
    int ix, iy;
    int h, i, j, k;
    int oh, oi, oj, ok;
    int xmh, xph;
    int xmi, xpi;
    int xmj, xpj;
    int xmk, xpk;

    /* Sanity check radius */
    if ((rx < 0) || (ry < 0))
    {
        return (-1);
    }

    /* Special case for rx=0 - draw a vline */
    if (rx == 0)
    {
        return (vlineRGBA(renderer, x, y - ry, y + ry, color));
    }

    /* Special case for ry=0 - draw a hline */
    if (ry == 0)
    {
        return (hlineRGBA(renderer, x - rx, x + rx, y, color));
    }

    /* Set color */
    result = 0;
    // if (color.a != 255) result |= SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    result |= SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    /* Init vars */
    oh = oi = oj = ok = 0xFFFF;

    /* Draw */
    if (rx > ry)
    {
        ix = 0;
        iy = rx * 64;

        do
        {
            h = (ix + 32) >> 6;
            i = (iy + 32) >> 6;
            j = (h * ry) / rx;
            k = (i * ry) / rx;

            if ((ok != k) && (oj != k))
            {
                xph = x + h;
                xmh = x - h;
                if (k > 0)
                {
                    result |= hline(renderer, xmh, xph, y + k);
                    result |= hline(renderer, xmh, xph, y - k);
                }
                else
                {
                    result |= hline(renderer, xmh, xph, y);
                }
                ok = k;
            }
            if ((oj != j) && (ok != j) && (k != j))
            {
                xmi = x - i;
                xpi = x + i;
                if (j > 0)
                {
                    result |= hline(renderer, xmi, xpi, y + j);
                    result |= hline(renderer, xmi, xpi, y - j);
                }
                else
                {
                    result |= hline(renderer, xmi, xpi, y);
                }
                oj = j;
            }

            ix = ix + iy / rx;
            iy = iy - ix / rx;
        } while (i > h);
    }
    else
    {
        ix = 0;
        iy = ry * 64;

        do
        {
            h = (ix + 32) >> 6;
            i = (iy + 32) >> 6;
            j = (h * rx) / ry;
            k = (i * rx) / ry;

            if ((oi != i) && (oh != i))
            {
                xmj = x - j;
                xpj = x + j;
                if (i > 0)
                {
                    result |= hline(renderer, xmj, xpj, y + i);
                    result |= hline(renderer, xmj, xpj, y - i);
                }
                else
                {
                    result |= hline(renderer, xmj, xpj, y);
                }
                oi = i;
            }
            if ((oh != h) && (oi != h) && (i != h))
            {
                xmk = x - k;
                xpk = x + k;
                if (h > 0)
                {
                    result |= hline(renderer, xmk, xpk, y + h);
                    result |= hline(renderer, xmk, xpk, y - h);
                }
                else
                {
                    result |= hline(renderer, xmk, xpk, y);
                }
                oh = h;
            }

            ix = ix + iy / ry;
            iy = iy - ix / ry;
        } while (i > h);
    }

    return (result);
}

inline int filledEllipseColor(SDL_Renderer *renderer, int x, int y, int rx, int ry, SDL_Color color)
{
    return filledEllipseRGBA(renderer, x, y, rx, ry, color);
}

/*
 *
 * POLYGON FUNCTIONS UTILS
 *
 */
inline int filledPolygonRGBAMT(SDL_Renderer *renderer, const int *vx, const int *vy, int n, Uint8 r, Uint8 g, Uint8 b, Uint8 a, int **polyInts, int *polyAllocated)
{
    int result;
    int i;
    int y, xa, xb;
    int miny, maxy;
    int x1, y1;
    int x2, y2;
    int ind1, ind2;
    int ints;
    int *gfxPrimitivesPolyInts = NULL;
    int *gfxPrimitivesPolyIntsNew = NULL;
    int gfxPrimitivesPolyAllocated = 0;

    /* Vertex array NULL check */
    if (vx == NULL)
    {
        return (-1);
    }
    if (vy == NULL)
    {
        return (-1);
    }

    /* Sanity check number of edges */
    if (n < 3)
    {
        return -1;
    }

    /* Map polygon cache */
    if ((polyInts == NULL) || (polyAllocated == NULL))
    {
        /* Use global cache */
        gfxPrimitivesPolyInts = primitivesPolyIntsGlobal;
        gfxPrimitivesPolyAllocated = primitivesPolyAllocatedGlobal;
    }
    else
    {
        /* Use local cache */
        gfxPrimitivesPolyInts = *polyInts;
        gfxPrimitivesPolyAllocated = *polyAllocated;
    }

    /* Allocate temp array, only grow array */
    if (!gfxPrimitivesPolyAllocated)
    {
        gfxPrimitivesPolyInts = (int *)malloc(sizeof(int) * n);
        gfxPrimitivesPolyAllocated = n;
    }
    else
    {
        if (gfxPrimitivesPolyAllocated < n)
        {
            gfxPrimitivesPolyIntsNew = (int *)realloc(gfxPrimitivesPolyInts, sizeof(int) * n);
            if (!gfxPrimitivesPolyIntsNew)
            {
                if (!gfxPrimitivesPolyInts)
                {
                    free(gfxPrimitivesPolyInts);
                    gfxPrimitivesPolyInts = NULL;
                }
                gfxPrimitivesPolyAllocated = 0;
            }
            else
            {
                gfxPrimitivesPolyInts = gfxPrimitivesPolyIntsNew;
                gfxPrimitivesPolyAllocated = n;
            }
        }
    }

    /* Check temp array */
    if (gfxPrimitivesPolyInts == NULL)
    {
        gfxPrimitivesPolyAllocated = 0;
    }

    /* Update cache variables */
    if ((polyInts == NULL) || (polyAllocated == NULL))
    {
        primitivesPolyIntsGlobal = gfxPrimitivesPolyInts;
        primitivesPolyAllocatedGlobal = gfxPrimitivesPolyAllocated;
    }
    else
    {
        *polyInts = gfxPrimitivesPolyInts;
        *polyAllocated = gfxPrimitivesPolyAllocated;
    }

    /* Check temp array again */
    if (gfxPrimitivesPolyInts == NULL)
    {
        return (-1);
    }

    /* Determine Y maxima */
    miny = vy[0];
    maxy = vy[0];
    for (i = 1; (i < n); i++)
    {
        if (vy[i] < miny)
        {
            miny = vy[i];
        }
        else if (vy[i] > maxy)
        {
            maxy = vy[i];
        }
    }

    /* Draw, scanning y */
    result = 0;
    for (y = miny; (y <= maxy); y++)
    {
        ints = 0;
        for (i = 0; (i < n); i++)
        {
            if (!i)
            {
                ind1 = n - 1;
                ind2 = 0;
            }
            else
            {
                ind1 = i - 1;
                ind2 = i;
            }
            y1 = vy[ind1];
            y2 = vy[ind2];
            if (y1 < y2)
            {
                x1 = vx[ind1];
                x2 = vx[ind2];
            }
            else if (y1 > y2)
            {
                y2 = vy[ind1];
                y1 = vy[ind2];
                x2 = vx[ind1];
                x1 = vx[ind2];
            }
            else
            {
                continue;
            }
            if (((y >= y1) && (y < y2)) || ((y == maxy) && (y > y1) && (y <= y2)))
            {
                gfxPrimitivesPolyInts[ints++] = ((65536 * (y - y1)) / (y2 - y1)) * (x2 - x1) + (65536 * x1);
            }
        }

        qsort(gfxPrimitivesPolyInts, ints, sizeof(int), _gfxPrimitivesCompareInt);

        /* Set color */
        result = 0;
        if (a != 255)
            result |= SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        result |= SDL_SetRenderDrawColor(renderer, r, g, b, a);

        for (i = 0; (i < ints); i += 2)
        {
            xa = gfxPrimitivesPolyInts[i] + 1;
            xa = (xa >> 16) + ((xa & 32768) >> 15);
            xb = gfxPrimitivesPolyInts[i + 1] - 1;
            xb = (xb >> 16) + ((xb & 32768) >> 15);
            result |= hline(renderer, xa, xb, y);
        }
    }

    return (result);
}

inline int filledPolygonColor(SDL_Renderer *renderer, const int *vx, const int *vy, int n, SDL_Color color)
{
    return filledPolygonRGBAMT(renderer, vx, vy, n, color.r, color.g, color.b, color.a, NULL, NULL);
}

/*
 *
 * ELLIPSE BORDER UTILS: Draw one quadrant arc, and mirror the other 4 quadrants
 *
 */
inline void borderEllipse(SDL_Renderer *r, int x0, int y0, int radiusX, int radiusY, SDL_Color color)
{
    float pi = 3.14159265358979323846264338327950288419716939937510;
    float pih = pi / 2.0; //half of pi

    //drew  28 lines with   4x4  circle with precision of 150 0ms
    //drew 132 lines with  25x14 circle with precision of 150 0ms
    //drew 152 lines with 100x50 circle with precision of 150 3ms
    const int prec = 27; // precision value; value of 1 will draw a diamond, 27 makes pretty smooth circles.
    float theta = 0;     // angle that will be increased each loop

    //starting point
    int x = (float)radiusX * cos(theta); //start point
    int y = (float)radiusY * sin(theta); //start point
    int x1 = x;
    int y1 = y;

    SDL_SetRenderDrawColor(r, color.r, color.g, color.b, 255);
    //repeat until theta >= 90;
    float step = pih / (float)prec;                 // amount to add to theta each time (degrees)
    for (theta = step; theta <= pih; theta += step) //step through only a 90 arc (1 quadrant)
    {
        //get new point location
        x1 = (float)radiusX * cosf(theta) + 0.5; //new point (+.5 is a quick rounding method)
        y1 = (float)radiusY * sinf(theta) + 0.5; //new point (+.5 is a quick rounding method)

        //draw line from previous point to new point, ONLY if point incremented
        if ((x != x1) || (y != y1)) //only draw if coordinate changed
        {
            SDL_RenderDrawLine(r, x0 + x, y0 - y, x0 + x1, y0 - y1); //quadrant TR
            SDL_RenderDrawLine(r, x0 - x, y0 - y, x0 - x1, y0 - y1); //quadrant TL
            SDL_RenderDrawLine(r, x0 - x, y0 + y, x0 - x1, y0 + y1); //quadrant BL
            SDL_RenderDrawLine(r, x0 + x, y0 + y, x0 + x1, y0 + y1); //quadrant BR
        }
        //save previous points
        x = x1; //save new previous point
        y = y1; //save new previous point
    }
    //arc did not finish because of rounding, so finish the arc
    if (x != 0)
    {
        x = 0;
        SDL_RenderDrawLine(r, x0 + x, y0 - y, x0 + x1, y0 - y1); //quadrant TR
        SDL_RenderDrawLine(r, x0 - x, y0 - y, x0 - x1, y0 - y1); //quadrant TL
        SDL_RenderDrawLine(r, x0 - x, y0 + y, x0 - x1, y0 + y1); //quadrant BL
        SDL_RenderDrawLine(r, x0 + x, y0 + y, x0 + x1, y0 + y1); //quadrant BR
    }
}
