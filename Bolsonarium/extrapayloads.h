#pragma once

namespace ExtraPayloads
{
	DWORD WINAPI Statics(LPVOID lpParam)
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

        int totalPixels = w * h;

        while (true)
        {
            for (int i = 0; i < totalPixels; i++)
            {
                BYTE noise = (BYTE)(rand() & 0xFF);

                if ((rand() % 10) == 0)
                {
                    noise = (rand() % 2 == 0) ? 255 : 0;
                }

                prgbDst[i].colors.r = noise;
                prgbDst[i].colors.g = noise - 2;
                prgbDst[i].colors.b = noise + 2;
                prgbDst[i].colors.Reserved = 0;
            }

            BitBlt(hdc, 0, 0, w, h, dcCopy, 0, 0, SRCCOPY);
            Sleep(1);
        }

        DeleteObject(hbmDst);
        DeleteDC(dcCopy);
        ReleaseDC(NULL, hdc);

        return 0;
	}
}