#pragma once
#include "Bolsonarium.h"

enum
{
	SAMPLE_RATE_A = 8000,
	SAMPLE_RATE_B = 12000,
	SAMPLE_RATE_C = 24000,
	SAMPLE_RATE_D = 48000,
	SAMPLE_RATE_E = 11025,
	SAMPLE_RATE_F = 22050,
	SAMPLE_RATE_G = 32768,
	SAMPLE_RATE_H = 44100
};

#define SECONDS 30

#define BUFFER_SIZE_A (SAMPLE_RATE_A * SECONDS)
#define BUFFER_SIZE_B (SAMPLE_RATE_B * SECONDS)
#define BUFFER_SIZE_C (SAMPLE_RATE_C * SECONDS)
#define BUFFER_SIZE_D (SAMPLE_RATE_D * SECONDS)
#define BUFFER_SIZE_E (SAMPLE_RATE_E * SECONDS)
#define BUFFER_SIZE_F (SAMPLE_RATE_F * SECONDS)
#define BUFFER_SIZE_G (SAMPLE_RATE_G * SECONDS)
#define BUFFER_SIZE_H (SAMPLE_RATE_H * SECONDS)

namespace Bytebeats
{
	DWORD WINAPI Sound1(LPVOID lpvd)
	{
		HWAVEOUT hWaveOut;
		WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, SAMPLE_RATE_A, SAMPLE_RATE_A, 1, 8, 0 };

		if (waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL) != MMSYSERR_NOERROR)
		{
			return 1;
		}

		std::vector<unsigned char> buffer(BUFFER_SIZE_A);

		for (int t = 0; t < BUFFER_SIZE_A; ++t)
		{
			buffer[t] =
			(unsigned char)((t | t >> 1 | t >> 7) * t + (t >> 11 | t >> 8));
		}

		WAVEHDR header = { (LPSTR)buffer.data(), (DWORD)buffer.size(), 0, 0, 0, 0, 0, 0 };

		waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
		waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));

		while (!(header.dwFlags & WHDR_DONE))
		{
			Sleep(100);
		}

		waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
		waveOutClose(hWaveOut);

		return 0;
	}

	DWORD WINAPI Sound2(LPVOID lpvd)
	{
		HWAVEOUT hWaveOut;
		WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, SAMPLE_RATE_B, SAMPLE_RATE_B, 1, 8, 0 };

		if (waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL) != MMSYSERR_NOERROR)
		{
			return 1;
		}

		std::vector<unsigned char> buffer(BUFFER_SIZE_B);

		for (int t = 0; t < BUFFER_SIZE_B; ++t)
		{
			buffer[t] =
			(unsigned char)((t * (t ^ t + (t >> 15 | 1) ^ (t - 1280 ^ t) >> 10)) + (t >> t));
		}

		WAVEHDR header = { (LPSTR)buffer.data(), (DWORD)buffer.size(), 0, 0, 0, 0, 0, 0 };

		waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
		waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));

		while (!(header.dwFlags & WHDR_DONE))
		{
			Sleep(100);
		}

		waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
		waveOutClose(hWaveOut);

		return 0;
	}

	DWORD WINAPI Sound3(LPVOID lpvd)
	{
		HWAVEOUT hWaveOut;
		WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, SAMPLE_RATE_B, SAMPLE_RATE_B, 1, 8, 0 };

		if (waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL) != MMSYSERR_NOERROR)
		{
			return 1;
		}

		std::vector<unsigned char> buffer(BUFFER_SIZE_B);

		for (int t = 0; t < BUFFER_SIZE_B; ++t)
		{
			buffer[t] =
				(unsigned char)(t * (2 + (t >> (t >> 9) ^ ((t >> 9) - 1) ^ 1) % 13));
		}

		WAVEHDR header = { (LPSTR)buffer.data(), (DWORD)buffer.size(), 0, 0, 0, 0, 0, 0 };

		waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
		waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));

		while (!(header.dwFlags & WHDR_DONE))
		{
			Sleep(100);
		}

		waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
		waveOutClose(hWaveOut);

		return 0;
	}

	DWORD WINAPI Sound4(LPVOID lpvd)
	{
		HWAVEOUT hWaveOut;
		WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, SAMPLE_RATE_A, SAMPLE_RATE_A, 1, 8, 0 };

		if (waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL) != MMSYSERR_NOERROR)
		{
			return 1;
		}

		std::vector<unsigned char> buffer(BUFFER_SIZE_A);

		for (int t = 0; t < BUFFER_SIZE_A; ++t)
		{
			buffer[t] =
			(unsigned char)((t * (0xCA98CA98 >> (t >> 9 & 30) & 15) | t >> 7) + (t >> 4));
		}

		WAVEHDR header = { (LPSTR)buffer.data(), (DWORD)buffer.size(), 0, 0, 0, 0, 0, 0 };

		waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
		waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));

		while (!(header.dwFlags & WHDR_DONE))
		{
			Sleep(100);
		}

		waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
		waveOutClose(hWaveOut);

		return 0;
	}

	DWORD WINAPI Sound5(LPVOID lpvd)
	{
		HWAVEOUT hWaveOut;
		WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, SAMPLE_RATE_G, SAMPLE_RATE_G, 1, 8, 0 };

		if (waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL) != MMSYSERR_NOERROR)
		{
			return 1;
		}

		std::vector<unsigned char> buffer(BUFFER_SIZE_G);

		int a = 0;
		int b = 0;
		int c = 0;
		int d = 0;

		for (int t = 0; t < BUFFER_SIZE_G; ++t)
		{
			buffer[t] =
			(unsigned char)
			((((t * (t >> 8 | t >> 9) & 46 & t >> 8)) ^ (t & t >> 13 | t >> 6)) +
			(a = t & t >> 6, b = t | t >> 8, c = t | t >> 7, d = t | t >> 9, a + b + c + d));
		}

		WAVEHDR header = { (LPSTR)buffer.data(), (DWORD)buffer.size(), 0, 0, 0, 0, 0, 0 };

		waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
		waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));

		while (!(header.dwFlags & WHDR_DONE))
		{
			Sleep(100);
		}

		waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
		waveOutClose(hWaveOut);

		return 0;
	}

	DWORD WINAPI Sound6(LPVOID lpvd)
	{
		HWAVEOUT hWaveOut;
		WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, SAMPLE_RATE_F, SAMPLE_RATE_F, 1, 8, 0 };

		if (waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL) != MMSYSERR_NOERROR)
		{
			return 1;
		}

		std::vector<unsigned char> buffer(BUFFER_SIZE_F);

		for (int t = 0; t < BUFFER_SIZE_F; ++t)
		{
			buffer[t] =
			(unsigned char)
			(
				(t >> 5) +
				(t >> 6 ^ t & t >> 9 ^ t >> 12 | (t << (t >> 6) % 4 ^ -t & -t >> 13) % 128 ^ -t >> 1)
			);
		}

		WAVEHDR header = { (LPSTR)buffer.data(), (DWORD)buffer.size(), 0, 0, 0, 0, 0, 0 };

		waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
		waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));

		while (!(header.dwFlags & WHDR_DONE))
		{
			Sleep(100);
		}

		waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
		waveOutClose(hWaveOut);

		return 0;
	}

	DWORD WINAPI Sound7(LPVOID lpvd)
	{
		HWAVEOUT hWaveOut;
		WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, SAMPLE_RATE_C, SAMPLE_RATE_C, 1, 8, 0 };

		if (waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL) != MMSYSERR_NOERROR)
		{
			return 1;
		}

		std::vector<unsigned char> buffer(BUFFER_SIZE_C);

		for (int t = 0; t < BUFFER_SIZE_C; ++t)
		{
			buffer[t] =
			(unsigned char)
			(
				(t * (((t >> 9) ^ ((t >> 9) - 1) ^ 1) % 13)) +
				t >> 6 ^ t & t >> 9 ^ t >> 12 | (t << (t >> 6) % 4 ^ -t & -t >> 13) % 128 ^ -t >> 1
			);
		}

		WAVEHDR header = { (LPSTR)buffer.data(), (DWORD)buffer.size(), 0, 0, 0, 0, 0, 0 };

		waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
		waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));

		while (!(header.dwFlags & WHDR_DONE))
		{
			Sleep(100);
		}

		waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
		waveOutClose(hWaveOut);

		return 0;
	}

	DWORD WINAPI Sound8(LPVOID lpvd)
	{
		HWAVEOUT hWaveOut;
		WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, SAMPLE_RATE_E, SAMPLE_RATE_E, 1, 8, 0 };

		if (waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL) != MMSYSERR_NOERROR)
		{
			return 1;
		}

		std::vector<unsigned char> buffer(BUFFER_SIZE_C);

		for (int t = 0; t < BUFFER_SIZE_C; ++t)
		{
			buffer[t] = (unsigned char)((t >> t) + (t >> 3) + (t >> 4));
		}

		WAVEHDR header = { (LPSTR)buffer.data(), (DWORD)buffer.size(), 0, 0, 0, 0, 0, 0 };

		waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
		waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));

		while (!(header.dwFlags & WHDR_DONE))
		{
			Sleep(100);
		}

		waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
		waveOutClose(hWaveOut);

		return 0;
	}
}