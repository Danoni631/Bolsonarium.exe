#include "Bolsonarium.h"

int APIENTRY wWinMain
(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPWSTR lpCmdLine,
    int nCmdShow
)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    if
    (
        MessageBox
        (
            NULL,
            L"WARNING!!!\n\nYou are about to run a malware called Bolsonarium.exe, a malicious program. You downloaded the safe version, so your computer don't gonna be damaged :D, but already have the same flashing lights, strong language and loud noises of the destructive version.\n\nExtra warning: The creators of this malware don't have politic opinion, the politic jokes of this malware is only for meme and don't have intention to attack nobody.\n\nDo you want to run?\n\n[DATA EXPUNGED]",
            L"########################################################################################",
            MB_ICONWARNING | MB_YESNO
        ) != IDYES
    ) return 1;

    if
    (
        MessageBox
        (
            NULL,
            L"Are you really sure? DO YOU REALLY WANT RUN THIS MALWARE???",
            L"Bolsonarium. Made by a lot of noice peoples - Last Warning",
            MB_ICONWARNING | MB_YESNO
        ) != IDYES
    ) return 1;

    MessageBox
    (
        NULL,
        L"Credits :D\n\nGDI: UltraDasher, Nyexev, CrzxyMinty, N17Pro3426, DaniloSenseiPlus and X0ranix\n\nBytebeats: UltraDasher, X0ranix and DaniloSenseiPlus.\n\nSystem Payloads: SuperNaray, UltraDasher and DaniloSenseiPlus.\n\nExtra Payloads: DaniloSenseiPlus and Mimiberries.\n\nMBR Kernel: NicolasBickHoff.\n\nThanks for running this malware, enjoy the destruction if you are running destructive version, else if you running safety version, enjoy the party, this is going to be [FUN].",
        L"Bolsonarium. Made by a lot of noice peoples - Credits",
        MB_OK | MB_ICONASTERISK
    );

    InitPayloads();
}