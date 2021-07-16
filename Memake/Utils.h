#pragma once
#include <SDL2/SDL.h>

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
	return (*(const int *) a) - (*(const int *) b);
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

		do {
			h = (ix + 32) >> 6;
			i = (iy + 32) >> 6;
			j = (h *ry) / rx;
			k = (i *ry) / rx;

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

		do { 	h = (ix + 32) >> 6;
			i = (iy + 32) >> 6;
			j = (h *rx) / ry;
			k = (i *rx) / ry;

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
inline int filledPolygonRGBAMT(SDL_Renderer * renderer, const int * vx, const int * vy, int n, Uint8 r, Uint8 g, Uint8 b, Uint8 a, int **polyInts, int *polyAllocated)
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
	if (vx == NULL) {
		return (-1);
	}
	if (vy == NULL) {
		return (-1);
	}

	/* Sanity check number of edges */
	if (n < 3) {
		return -1;
	}

	/* Map polygon cache */
	if ((polyInts==NULL) || (polyAllocated==NULL)) {
		/* Use global cache */
		gfxPrimitivesPolyInts = primitivesPolyIntsGlobal;
		gfxPrimitivesPolyAllocated = primitivesPolyAllocatedGlobal;
	} else {
		/* Use local cache */
		gfxPrimitivesPolyInts = *polyInts;
		gfxPrimitivesPolyAllocated = *polyAllocated;
	}

	/* Allocate temp array, only grow array */
	if (!gfxPrimitivesPolyAllocated) {
		gfxPrimitivesPolyInts = (int *) malloc(sizeof(int) * n);
		gfxPrimitivesPolyAllocated = n;
	} else {
		if (gfxPrimitivesPolyAllocated < n) {
			gfxPrimitivesPolyIntsNew = (int *) realloc(gfxPrimitivesPolyInts, sizeof(int) * n);
			if (!gfxPrimitivesPolyIntsNew) {
				if (!gfxPrimitivesPolyInts) {
					free(gfxPrimitivesPolyInts);
					gfxPrimitivesPolyInts = NULL;
				}
				gfxPrimitivesPolyAllocated = 0;
			} else {
				gfxPrimitivesPolyInts = gfxPrimitivesPolyIntsNew;
				gfxPrimitivesPolyAllocated = n;
			}
		}
	}

	/* Check temp array */
	if (gfxPrimitivesPolyInts==NULL) {
		gfxPrimitivesPolyAllocated = 0;
	}

	/* Update cache variables */
	if ((polyInts==NULL) || (polyAllocated==NULL)) {
		primitivesPolyIntsGlobal =  gfxPrimitivesPolyInts;
		primitivesPolyAllocatedGlobal = gfxPrimitivesPolyAllocated;
	} else {
		*polyInts = gfxPrimitivesPolyInts;
		*polyAllocated = gfxPrimitivesPolyAllocated;
	}

	/* Check temp array again */
	if (gfxPrimitivesPolyInts==NULL) {
		return(-1);
	}

	/* Determine Y maxima */
	miny = vy[0];
	maxy = vy[0];
	for (i = 1; (i < n); i++) {
		if (vy[i] < miny) {
			miny = vy[i];
		} else if (vy[i] > maxy) {
			maxy = vy[i];
		}
	}

	/* Draw, scanning y */
	result = 0;
	for (y = miny; (y <= maxy); y++) {
		ints = 0;
		for (i = 0; (i < n); i++) {
			if (!i) {
				ind1 = n - 1;
				ind2 = 0;
			} else {
				ind1 = i - 1;
				ind2 = i;
			}
			y1 = vy[ind1];
			y2 = vy[ind2];
			if (y1 < y2) {
				x1 = vx[ind1];
				x2 = vx[ind2];
			} else if (y1 > y2) {
				y2 = vy[ind1];
				y1 = vy[ind2];
				x2 = vx[ind1];
				x1 = vx[ind2];
			} else {
				continue;
			}
			if ( ((y >= y1) && (y < y2)) || ((y == maxy) && (y > y1) && (y <= y2)) ) {
				gfxPrimitivesPolyInts[ints++] = ((65536 * (y - y1)) / (y2 - y1)) * (x2 - x1) + (65536 * x1);
			}
		}

		qsort(gfxPrimitivesPolyInts, ints, sizeof(int), _gfxPrimitivesCompareInt);

		/* Set color */
		result = 0;
	    if (a != 255) result |= SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
		result |= SDL_SetRenderDrawColor(renderer, r, g, b, a);

		for (i = 0; (i < ints); i += 2) {
			xa = gfxPrimitivesPolyInts[i] + 1;
			xa = (xa >> 16) + ((xa & 32768) >> 15);
			xb = gfxPrimitivesPolyInts[i+1] - 1;
			xb = (xb >> 16) + ((xb & 32768) >> 15);
			result |= hline(renderer, xa, xb, y);
		}
	}

	return (result);
}

inline int filledPolygonColor(SDL_Renderer * renderer, const int * vx, const int * vy, int n, SDL_Color color)
{
	return filledPolygonRGBAMT(renderer, vx, vy, n, color.r, color.g, color.b, color.a, NULL, NULL);
}

//draw one quadrant arc, and mirror the other 4 quadrants
inline void borderEllipse(SDL_Renderer* r, int x0, int y0, int radiusX, int radiusY, SDL_Color color)
{
    float pi  = 3.14159265358979323846264338327950288419716939937510;
    float pih = pi / 2.0; //half of pi

    //drew  28 lines with   4x4  circle with precision of 150 0ms
    //drew 132 lines with  25x14 circle with precision of 150 0ms
    //drew 152 lines with 100x50 circle with precision of 150 3ms
    const int prec = 27; // precision value; value of 1 will draw a diamond, 27 makes pretty smooth circles.
    float theta = 0;     // angle that will be increased each loop

    //starting point
    int x  = (float)radiusX * cos(theta);//start point
    int y  = (float)radiusY * sin(theta);//start point
    int x1 = x;
    int y1 = y;

	SDL_SetRenderDrawColor(r, color.r, color.g, color.b, 255);
    //repeat until theta >= 90;
    float step = pih/(float)prec; // amount to add to theta each time (degrees)
    for(theta=step;  theta <= pih;  theta+=step)//step through only a 90 arc (1 quadrant)
    {
        //get new point location
        x1 = (float)radiusX * cosf(theta) + 0.5; //new point (+.5 is a quick rounding method)
        y1 = (float)radiusY * sinf(theta) + 0.5; //new point (+.5 is a quick rounding method)

        //draw line from previous point to new point, ONLY if point incremented
        if( (x != x1) || (y != y1) )//only draw if coordinate changed
        {
            SDL_RenderDrawLine(r, x0 + x, y0 - y,  x0 + x1, y0 - y1 );//quadrant TR
            SDL_RenderDrawLine(r, x0 - x, y0 - y,  x0 - x1, y0 - y1 );//quadrant TL
            SDL_RenderDrawLine(r, x0 - x, y0 + y,  x0 - x1, y0 + y1 );//quadrant BL
            SDL_RenderDrawLine(r, x0 + x, y0 + y,  x0 + x1, y0 + y1 );//quadrant BR
        }
        //save previous points
        x = x1;//save new previous point
        y = y1;//save new previous point
    }
    //arc did not finish because of rounding, so finish the arc
    if(x!=0)
    {
        x=0;
        SDL_RenderDrawLine(r, x0 + x, y0 - y,  x0 + x1, y0 - y1 );//quadrant TR
        SDL_RenderDrawLine(r, x0 - x, y0 - y,  x0 - x1, y0 - y1 );//quadrant TL
        SDL_RenderDrawLine(r, x0 - x, y0 + y,  x0 - x1, y0 + y1 );//quadrant BL
        SDL_RenderDrawLine(r, x0 + x, y0 + y,  x0 + x1, y0 + y1 );//quadrant BR
    }
}
