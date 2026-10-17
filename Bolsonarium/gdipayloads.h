#pragma once

#include "Bolsonarium.h"

int w = GetSystemMetrics(0);
int h = GetSystemMetrics(1);                                              //idk

enum
{
	MEM_ALLOC_TYPES = MEM_COMMIT | MEM_RESERVE
};

namespace GDIPayloads
{
	DWORD WINAPI GDIShader1(LPVOID lpParam) // coded by ???, i really don't know who made this code
	{
		while (1)
		{
			HDC hdc = GetDC(NULL);
			HDC dcCopy = CreateCompatibleDC(hdc);

			HBITMAP hbit = CreateCompatibleBitmap(hdc, w, h);
			SelectObject(dcCopy, hbit);

			HBRUSH brush = CreateSolidBrush(RGB(rand() % 25, rand() % 142, rand() % 255));
			SelectObject(hdc, brush);

			int i = 1 + rand() % 32;

			SetStretchBltMode(hdc, STRETCH_HALFTONE);
			SetStretchBltMode(dcCopy, STRETCH_HALFTONE);

			StretchBlt(dcCopy, 0, 0, w / i, h / i, hdc, 0, 0, w, h, SRCCOPY);
			StretchBlt(hdc, 0, 0, w, h, dcCopy, 0, 0, w / i, h / i, SRCCOPY);
			BitBlt(hdc, 0, 0, w, h, hdc, 0, 0, PATINVERT);
			BitBlt(hdc, rand() % 10, rand() % 10, w, h, hdc, rand() % 10, rand() % 10, SRCCOPY);
			ReleaseDC(NULL, hdc);
			DeleteObject(hbit);
			DeleteObject(brush);
			DeleteDC(dcCopy);
		}
	}

	DWORD WINAPI GDIShader2(LPVOID lpParam) // coded by Danoni631
	{
		HDC hdc = GetDC(0);
		HDC dcCopy = CreateCompatibleDC(hdc);

		BITMAPINFO bmi = { 0 };
		bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bmi.bmiHeader.biBitCount = 32;
		bmi.bmiHeader.biPlanes = 1;
		bmi.bmiHeader.biWidth = w;
		bmi.bmiHeader.biHeight = -h;

		PRGBQUAD_t prgbDst = nullptr;
		HBITMAP hbmTemp = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, (void**)&prgbDst, NULL, 0);
		SelectObject(dcCopy, hbmTemp);

		PRGBQUAD_t prgbSrc =
		(PRGBQUAD_t)VirtualAlloc(NULL, w * h * sizeof(RGBQUAD_t), MEM_ALLOC_TYPES, PAGE_READWRITE);

		float angle = 0.0f;

		HSL hsl;

		while (1)
		{
			BitBlt(dcCopy, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
			memcpy(prgbSrc, prgbDst, w * h * sizeof(RGBQUAD_t));

			float frequency = 0.05f;
			float amplitude = 20.0f;

			int t = 0;
			const float f = 1.0f / 4.0f;

			for (int y = 0; y < h; y++)
			{
				int offsetX = (int)(sinf(y * frequency + angle) * amplitude);

				for (int x = 0; x < w; x++)
				{
					int srcX = (x + offsetX) % w;
					if (srcX < 0) srcX += w;

					int dstIdx = y * w + x;
					int srcIdx = y * w + srcX;

					int rawU = ~((x + t) & y);
					int rawV = ~((y + t) & x);

					UINT u = (UINT)(abs(rawU) % w);
					UINT v = (UINT)(abs(rawV) % h);

					Reflect2D((PINT)&u, (PINT)&v, w, h);

					RGBQUAD_t rgbDst = prgbSrc[v * w + u];
					RGBQUAD_t rgbSrc = prgbSrc[y * w + x];

					if (!rgbSrc.rgb)
					{
						rgbSrc.rgb = 1;
					}

					rgbDst.rgb &= rgbDst.rgb % ((rgbSrc.rgb << 8) + 1);
					FLOAT r = (FLOAT)rgbDst.colors.r * f + (FLOAT)rgbSrc.colors.r * (1.f - f);
					FLOAT g = (FLOAT)rgbDst.colors.g * f + (FLOAT)rgbSrc.colors.g * (1.f - f);
					FLOAT b = (FLOAT)rgbDst.colors.b * f + (FLOAT)rgbSrc.colors.b * (1.f - f);
					rgbDst.rgb = ((BYTE)b | ((BYTE)g << 8) | ((BYTE)r << 16));

					hsl = RGBtoHSL(rgbDst);
					hsl.h /= 1.0125f;
					hsl.s /= 1.0125f;
					hsl.l /= 1.0125f;

					if (hsl.l < .2f)
					{
						hsl.l += .2f;
					}

					rgbDst = HSLtoRGB(hsl);
					prgbDst[y * w + x] = rgbDst;
				}
			}

			BitBlt(hdc, 0, 0, w, h, dcCopy, 0, 0, SRCCOPY);
			angle += 0.15f;
			Sleep(10);
		}

		VirtualFree(prgbSrc, 0, MEM_RELEASE);
		DeleteObject(hbmTemp);
		DeleteDC(dcCopy);
		ReleaseDC(NULL, hdc);

		return 0;
	}

	DWORD WINAPI GDIShader3(LPVOID lpParam) // coded by Danoni631
	{
		HDC hdc = GetDC(NULL);
		HDC dcCopy = CreateCompatibleDC(hdc);

		BITMAPINFO bmi = { 0 };
		bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bmi.bmiHeader.biWidth = w;
		bmi.bmiHeader.biHeight = -h;
		bmi.bmiHeader.biPlanes = 1;
		bmi.bmiHeader.biBitCount = 32;

		PRGBQUAD_t prgbDst = nullptr;
		HBITMAP hbmDst = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, (void**)&prgbDst, NULL, 0);
		SelectObject(dcCopy, hbmDst);

		PRGBQUAD_t prgbSrc =
		(PRGBQUAD_t)VirtualAlloc(NULL, w * h * sizeof(RGBQUAD_t), MEM_ALLOC_TYPES, PAGE_READWRITE);

		int t = 0;

		while (true)
		{
			BitBlt(dcCopy, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
			memcpy(prgbSrc, prgbDst, w * h * sizeof(RGBQUAD_t));

			int offsetX = (int)(sinf(t * 0.04f) * 18.0f);
			int offsetY = (int)(cosf(t * 0.03f) * 18.0f);

			for (int y = 0; y < h; y += 2)
			{
				int srcY = (y + offsetY) % h;
				if (srcY < 0) srcY += h;

				for (int x = 0; x < w; x += 2)
				{
					int srcX = (x + offsetX) % w;
					if (srcX < 0) srcX += w;

					RGBQUAD_t pixel = prgbSrc[srcY * w + srcX];

					int fractalVal = (x ^ y ^ t) & 0xFF;

					pixel.colors.r = (BYTE)(pixel.colors.r * 0.15f);
					pixel.colors.g = (BYTE)((pixel.colors.g ^ fractalVal) + 30);
					pixel.colors.b = (BYTE)(pixel.colors.b * 0.15f);

					for (int by = 0; by < 2; by++)
					{
						for (int bx = 0; bx < 2; bx++)
						{
							int targetX = x + bx;
							int targetY = y + by;

							if (targetX < w && targetY < h)
							{
								prgbDst[targetY * w + targetX] = pixel;
							}
						}
					}
				}
			}

			BitBlt(dcCopy, 2, 2, w - 2, h - 2, dcCopy, 0, 0, SRCERASE);

			BitBlt(hdc, 0, 0, w, h, dcCopy, 0, 0, SRCCOPY);

			t++;
			Sleep(10);
		}

		VirtualFree(prgbSrc, 0, MEM_RELEASE);
		DeleteObject(hbmDst);
		DeleteDC(dcCopy);
		ReleaseDC(NULL, hdc);

		return 0;
	}

	DWORD WINAPI GDIShader4(LPVOID lpParam) // coded by Danoni631
	{
		HDC hdc = GetDC(NULL);
		HDC dcCopy = CreateCompatibleDC(hdc);
		BITMAPINFO bmpi = { 0 };
		HBITMAP bmp;

		bmpi.bmiHeader.biSize = sizeof(bmpi);
		bmpi.bmiHeader.biWidth = w;
		bmpi.bmiHeader.biHeight = h;
		bmpi.bmiHeader.biPlanes = 1;
		bmpi.bmiHeader.biBitCount = 32;
		bmpi.bmiHeader.biCompression = BI_RGB;

		PRGBQUAD_t rgbquad = NULL;
		HSL hslcolor;

		bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
		SelectObject(dcCopy, bmp);

		INT i = 0;
		RECT rect;

		while (1) {
			hdc = GetDC(NULL);

			int offsetX = (int)(sinf(i * 0.04f) * 12.0f);
			int offsetY = (int)(cosf(i * 0.03f) * 12.0f);

			StretchBlt(dcCopy, offsetX, offsetY, w, h, hdc, 0, 0, w, h, SRCCOPY);

			RGBQUAD_t rgbquadCopy;

			for (int x = 0; x < w; x++)
			{
				for (int y = 0; y < h; y++)
				{
					int index = y * w + x;

					int fx = (int)((i ^ 4) + (i * 4) * cbrt((double)(x + y)));
					int light = ((y + (int)tan(x / (1.0 + (i * 9.0)))));

					rgbquadCopy = rgbquad[index];

					hslcolor = RGBtoHSL(rgbquadCopy);
					hslcolor.h = (float)fmod(fx / 400.0f + (float)y / h * 0.2f, 1.0);

					hslcolor.l *= 0.88f;

					if (hslcolor.l > .5f)
					{
						hslcolor.l -= .3f;
					}

					else if (hslcolor.l < .25f)
					{
						hslcolor.l += .1f;
					}

					else if (hslcolor.l > .75f)
					{
						hslcolor.l += 0.01f;
					}

					else
					{
						hslcolor.l = (float)fmod(light / 3000.0f + (float)y / w * 0.2f, 1.0);
					}

					rgbquad[index] = HSLtoRGB(hslcolor);
				}
			}

			i++;

			GetWindowRect(GetDesktopWindow(), &rect);

			StretchBlt(hdc, 0, 0, w, h, dcCopy, 0, 0, w, h, SRCCOPY);

			ReleaseDC(NULL, hdc);
			Sleep(10);
		}

		DeleteObject(bmp);
		DeleteDC(dcCopy);
		return 0;
	}

	DWORD WINAPI GDIShader5(LPVOID lpParam) // coded by Danoni631
	{
		HDC hdc = GetDC(0);
		HDC dcCopy = CreateCompatibleDC(hdc);

		BITMAPINFO bmi = { 0 };
		bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bmi.bmiHeader.biWidth = w;
		bmi.bmiHeader.biHeight = -h;
		bmi.bmiHeader.biPlanes = 1;
		bmi.bmiHeader.biBitCount = 32;
		bmi.bmiHeader.biCompression = BI_RGB;

		PRGBQUAD_t rgbScreen = NULL;
		HBITMAP hbmTemp = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, (void**)&rgbScreen, NULL, 0);
		SelectObject(dcCopy, hbmTemp);

		PRGBQUAD_t rgbSrc =
		(PRGBQUAD_t)VirtualAlloc(NULL, w * h * sizeof(RGBQUAD_t), MEM_ALLOC_TYPES, PAGE_READWRITE);

		float t = 0.0f;
		float cx = w / 2.0f;
		float cy = h / 2.0f;

		while (true)
		{
			hdc = GetDC(0);
			BitBlt(dcCopy, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
			memcpy(rgbSrc, rgbScreen, w * h * sizeof(RGBQUAD_t));

			float angleRot = t * 0.012f;
			float segments = 6.0f;
			float segAngle = 6.2831853f / segments;

			for (int y = 0; y < h; y += 2)
			{
				float dy = (float)y - cy;

				for (int x = 0; x < w; x += 2)
				{
					float dx = (float)x - cx;

					float r = sqrtf(dx * dx + dy * dy);
					float theta = atan2f(dy, dx) + angleRot;

					theta = fmodf(theta, segAngle);

					if (theta < 0.0f) theta += segAngle;

					if (theta > segAngle * 0.5f)
					{
						theta = segAngle - theta;
					}

					int srcX = (int)(cx + r * cosf(theta));
					int srcY = (int)(cy + r * sinf(theta));

					if (srcX < 0) srcX = 0; if (srcX >= w) srcX = w - 1;
					if (srcY < 0) srcY = 0; if (srcY >= h) srcY = h - 1;

					RGBQUAD_t pixel = rgbSrc[srcY * w + srcX];

					COLORREF colorVal = RGB(pixel.colors.r, pixel.colors.g, pixel.colors.b);
					colorVal = (colorVal * 2) % RGB(255, 255, 255);

					pixel.colors.r = GetRValue(colorVal);
					pixel.colors.g = GetGValue(colorVal);
					pixel.colors.b = GetBValue(colorVal);

					for (int by = 0; by < 2; by++)
					{
						for (int bx = 0; bx < 2; bx++)
						{
							int tx = x + bx;
							int ty = y + by;

							if (tx < w && ty < h)
							{
								rgbScreen[ty * w + tx] = pixel;
							}
						}
					}
				}
			}

			BitBlt(hdc, 0, 0, w, h, dcCopy, 0, 0, SRCCOPY);
			ReleaseDC(NULL, hdc);

			t += 1.0f;
			Sleep(10);
		}

		VirtualFree(rgbSrc, 0, MEM_RELEASE);
		DeleteObject(hbmTemp);
		DeleteDC(dcCopy);

		return 0;
	}

	DWORD WINAPI GDIShader6(LPVOID lpParam) // coded by Danoni631
	{
		DWORD rops[5] =
		{
			SRCCOPY,
			SRCAND,
			NOTSRCERASE,
			SRCPAINT,
			SRCINVERT
		};

		while (true)
		{
			HDC hdc = GetDC(NULL);

			int ropsIndex = rand() % 5;

			BitBlt(hdc, 5, 0, w, h, hdc, 0, 0, rops[ropsIndex]);
			Sleep(1);
			BitBlt(hdc, 0, 5, w, h, hdc, 0, 0, rops[ropsIndex]);
			Sleep(1);
			BitBlt(hdc, 0, 0, w, h, hdc, 5, 0, rops[ropsIndex]);
			Sleep(1);
			BitBlt(hdc, 0, 0, w, h, hdc, 0, 5, rops[ropsIndex]);
			Sleep(1);
			ReleaseDC(NULL, hdc);
		}
	}

	DWORD WINAPI GDIShader7(LPVOID lpParam) // coded by X0Ranix
	{
		HDC hdc = GetDC(NULL);

		BITMAPINFO bi;
		ZeroMemory(&bi, sizeof(bi));
		bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bi.bmiHeader.biWidth = w;
		bi.bmiHeader.biHeight = -h;
		bi.bmiHeader.biPlanes = 1;
		bi.bmiHeader.biBitCount = 32;
		bi.bmiHeader.biCompression = BI_RGB;

		PRGBQUAD_t buf;
		HBITMAP bmp = CreateDIBSection(hdc, &bi, DIB_RGB_COLORS, (void**)&buf, NULL, 0);
		HDC mdc = CreateCompatibleDC(hdc);
		SelectObject(mdc, bmp);

		float shift = 0.0f;

		while (1)
		{
			BitBlt(mdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);

			shift += 1.0f;
			if (shift >= 360.0f) shift -= 360.0f;

			int count = w * h;

			for (int i = 0; i < count; i++)
			{
				HSL hsl = RGBtoHSL(buf[i]);

				hsl.h += shift;
				if (hsl.h >= 360.0f) hsl.h -= 360.0f;
				if (hsl.h < 0.0f) hsl.h += 360.0f;

				buf[i] = HSLtoRGB(hsl);
			}

			BitBlt(hdc, 0, 0, w, h, mdc, 0, 0, SRCERASE);
			Sleep(1);
		}

		return 0;
	}
}

namespace WhileGDI
{
	DWORD WINAPI Texts(LPVOID lpParam) // coded by Danoni631
	{
		int state = 0;

		while (true)
		{
			int r = rand() % 255;
			int g = rand() % 255;
			int b = rand() % 255;

			int x = rand() % w;
			int y = rand() % h;

			HDC hdc = GetDC(NULL);

			LPCSTR strings[20] =
			{
				"Eletronic voting machine", "13", "22", "Politic", "we gonna fuck our country",
				"This shit country IS MINE", "Bolsonarium.exe", "fuck", "Danoni631", "UltraDasher965",
				"N17Pro3426", "CrzxyMinty", "Mimiberries", "Nyexev", "X0RANIX",
				"SuperNaray", "NicolasBickHoff", "2027", "cpuid", "xuxuxuxuxuxuxuxuxuxuxuxuxuxuxuxuxu"
			};

			int index = rand() % 20;

			SetBkMode(hdc, 0);

			int size = rand() % 100;

			SetTextColor(hdc, RGB(r, g, b));

			HFONT Font =
			CreateFontA
			(
				size, size, rand() % 3600, rand() % 60,
				FW_REGULAR, 0, 0, 0, ANSI_CHARSET, 0, 0, 0, 0, "Arial Black"
			);

			SelectObject(hdc, Font);
			TextOutA(hdc, x, y, strings[index], strlen(strings[index]));

			DeleteObject(Font);
			ReleaseDC(0, hdc);
			Sleep(10);
		}
	}

	DWORD WINAPI Pens(LPVOID lpParam)
	{
	}
}
