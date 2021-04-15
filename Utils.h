#pragma once
#include <SDL2/SDL.h>

inline int vlineRGBA(SDL_Renderer *renderer, int x, int y1, int y2, SDL_Color color)
{
	int result = 0;
	// if (color.a != 255) result |= SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	result |= SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	result |= SDL_RenderDrawLine(renderer, x, y1, x, y2);
	return result;
}

inline int hlineRGBA(SDL_Renderer *renderer, Sint16 x1, Sint16 x2, Sint16 y, SDL_Color color)
{
	int result = 0;
	// if (color.a != 255) result |= SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	result |= SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	result |= SDL_RenderDrawLine(renderer, x1, y, x2, y);
	return result;
}

inline int hline(SDL_Renderer *renderer, Sint16 x1, Sint16 x2, Sint16 y)
{
	return SDL_RenderDrawLine(renderer, x1, y, x2, y);
}

inline int filledEllipseRGBA(SDL_Renderer *renderer, Sint16 x, Sint16 y, Sint16 rx, Sint16 ry, SDL_Color color)
{
	int result;
	int ix, iy;
	int h, i, j, k;
	int oh, oi, oj, ok;
	int xmh, xph;
	int xmi, xpi;
	int xmj, xpj;
	int xmk, xpk;

	/*
	 *Sanity check radius
	 */
	if ((rx < 0) || (ry < 0))
	{
		return (-1);
	}

	/*
	 *Special case for rx=0 - draw a vline
	 */
	if (rx == 0)
	{
		return (vlineRGBA(renderer, x, y - ry, y + ry, color));
	}
	/*
	 *Special case for ry=0 - draw a hline
	 */
	if (ry == 0)
	{
		return (hlineRGBA(renderer, x - rx, x + rx, y, color));
	}

	/*
	 *Set color
	 */
	result = 0;
	// if (color.a != 255) result |= SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	result |= SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

	/*
	 *Init vars
	 */
	oh = oi = oj = ok = 0xFFFF;

	/*
	 *Draw
	 */
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

inline int filledEllipseColor(SDL_Renderer *renderer, Sint16 x, Sint16 y, Sint16 rx, Sint16 ry, SDL_Color color)
{
	return filledEllipseRGBA(renderer, x, y, rx, ry, color);
}
