// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "framework.h"

#define CREATEHOOK(Address, Hook, Og) \
MH_CreateHook((void*)(Address), Hook, (void**)(Og)); \
MH_EnableHook((void*)(Address));

void __fastcall RequestExit(char a1) {

}

__int64 __fastcall UnsafeEnvironment(__int64* a1, char a2, __int64 a3, char a4) {
    return 0;
}

DWORD WINAPI Main(LPVOID) {
    MH_Initialize();

    //9.41 offsets for now
    CREATEHOOK(uintptr_t(GetModuleHandle(0)) + 0x175CEB0, UnsafeEnvironment, nullptr);
    CREATEHOOK(uintptr_t(GetModuleHandle(0)) + 0x1F19230, RequestExit, nullptr); // if this doesn't work then create issue on github

    return 0;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(0, 0, Main, 0, 0, 0);
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

