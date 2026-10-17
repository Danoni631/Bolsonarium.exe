#pragma once

#include "Bolsonarium.h"

typedef union
{
    COLORREF rgb;

    struct RGBSTRUCT
    {
        BYTE b;
        BYTE g;
        BYTE r;
        BYTE Reserved;
    };

    RGBSTRUCT colors;
} RGBQUAD_t, * PRGBQUAD_t;

typedef struct
{
	FLOAT h;
	FLOAT s;
	FLOAT l;
} HSL;

static float HueToRGB(float p, float q, float t)
{
	if (t < 0.0f) t += 1.0f;
	if (t > 1.0f) t -= 1.0f;
	if (t < 1.0f / 6.0f) return p + (q - p) * 6.0f * t;
	if (t < 1.0f / 2.0f) return q;
	if (t < 2.0f / 3.0f) return p + (q - p) * (2.0f / 3.0f - t) * 6.0f;
	return p;
}

RGBQUAD_t HSLtoRGB(HSL hsl)
{
	RGBQUAD_t rgb;
	rgb.colors.Reserved = 0;

	if (hsl.s == 0.0f)
	{
		BYTE val = (BYTE)(hsl.l * 255.0f);
		rgb.colors.r = val;
		rgb.colors.g = val;
		rgb.colors.b = val;
	}

	else
	{
		float q =
			(hsl.l < 0.5f) ? (hsl.l * (1.0f + hsl.s)) :
			(hsl.l + hsl.s - hsl.l * hsl.s);

		float p = 2.0f * hsl.l - q;

		rgb.colors.r = (BYTE)(HueToRGB(p, q, hsl.h + 1.0f / 3.0f) * 255.0f);
		rgb.colors.g = (BYTE)(HueToRGB(p, q, hsl.h) * 255.0f);
		rgb.colors.b = (BYTE)(HueToRGB(p, q, hsl.h - 1.0f / 3.0f) * 255.0f);
	}

	return rgb;
}

HSL RGBtoHSL(RGBQUAD_t rgb)
{
	float r = rgb.colors.r / 255.0f;
	float g = rgb.colors.g / 255.0f;
	float b = rgb.colors.b / 255.0f;
	float max = fmaxf(r, fmaxf(g, b));
	float min = fminf(r, fminf(g, b));
	float h, s, l = (max + min) / 2.0f;

	if (max == min)
	{
		h = s = 0;
	}

	else
	{
		float d = max - min;
		s = l > 0.5f ? d / (2 - max - min) : d / (max + min);
		if (max == r) h = (g - b) / d + (g < b ? 6 : 0);
		else if (max == g) h = (b - r) / d + 2;
		else h = (r - g) / d + 4;
		h /= 6;
	}

	return { h, s, l };
}