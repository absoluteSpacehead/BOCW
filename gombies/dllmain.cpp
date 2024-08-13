// gombies.dll: inject in the multiplayer menu to switch to zombies.

#include "pch.h"
#include <cstdint>

template<class T>
T* Offset(uintptr_t offset)
{
    return reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(GetModuleHandle(0)) + offset);
}

typedef uint64_t QWORD;

void (*Cbuf_AddText)(QWORD param_1, const char* param_2) = nullptr;

DWORD MainThread(LPVOID hModule)
{
    Cbuf_AddText = Offset<void(QWORD, const char*)>(0x16F3A10);

    *Offset<DWORD>(0x65259E4) = 0x40C0;
    *Offset<DWORD>(0xB7D18A0) = 0;
    *Offset<DWORD>(0xB3333A9) = 0x616C637A;
    Cbuf_AddText(0, "disconnect");

    FreeLibraryAndExitThread((HMODULE)hModule, 0);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
    {
        CreateThread(0, 0, MainThread, hModule, 0, 0);
    }

    return TRUE;
}