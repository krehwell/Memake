#pragma once
#include <SDL2/SDL.h>

/*
 *
 * VAR UTILS
 *
 */
/* CACHE FOR TELLING THINGS IN DRAWING FOR POLYGON */
static int *gfxPrimitivesPolyIntsGlobal = NULL;
static int gfxPrimitivesPolyAllocatedGlobal = 0;


/*
 *
 * UTILS
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

		do { 	h = (ix + 32) >> 6;
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
		gfxPrimitivesPolyInts = gfxPrimitivesPolyIntsGlobal;
		gfxPrimitivesPolyAllocated = gfxPrimitivesPolyAllocatedGlobal;
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
		gfxPrimitivesPolyIntsGlobal =  gfxPrimitivesPolyInts;
		gfxPrimitivesPolyAllocatedGlobal = gfxPrimitivesPolyAllocated;
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

inline int filledTrigonColor(SDL_Renderer * renderer, int x1, int y1, int x2, int y2, int x3, int y3, SDL_Color color)
{
	int vx[3];
	int vy[3];

	vx[0]=x1;
	vx[1]=x2;
	vx[2]=x3;
	vy[0]=y1;
	vy[1]=y2;
	vy[2]=y3;

	return(filledPolygonColor(renderer,vx,vy,3,color));
}
