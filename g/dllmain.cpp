// g.dll: allows bypassing the "connecting to online services" screen.

#include "pch.h"
#include <cstdint>

// small utility so i dont have to retype this
template<class T>
T* Offset(uintptr_t offset)
{
    return reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(GetModuleHandle(0)) + offset);
}

typedef uint64_t QWORD;

void (*Cbuf_AddText)(QWORD param_1, const char* param_2) = nullptr;
void (*LiveStorage_ParseKeysTxt)(const char* param) = nullptr;
void (*LiveStorage_ParseKeysTxt2)(const char* param) = nullptr;
void (*SetScreen)(QWORD param) = nullptr;

DWORD MainThread(LPVOID hModule)
{
    *Offset<DWORD>(0xA8609C8) = 1;

    if (!Cbuf_AddText)
        Cbuf_AddText = Offset<void(QWORD, const char*)>(0x16F3A10);

    if (!LiveStorage_ParseKeysTxt)
        LiveStorage_ParseKeysTxt = Offset<void(const char*)>(0x1011720);

    if (!LiveStorage_ParseKeysTxt2)
        LiveStorage_ParseKeysTxt2 = Offset<void(const char*)>(0x1012900);

    if (!SetScreen)
        SetScreen = Offset<void(QWORD)>(0x105d9c0);

    SetScreen(10);
    LiveStorage_ParseKeysTxt("mp_common,1,LKBcjAtLFtrhGQqXZP3GQN2MXbGe4yBA4CJ8KK+Tmyw=\nzm_common,1,uVkxOTxN2vKCJHt2p iY5tGqy33LKZ0dKlKizutZifuI=\nwz_common,1,qYOw3RHpf/4LoNqha7D8w0l1uJs1a8f1GXvz9RSlcpc=\ncp_common,1,1Xms8bivDnvtle9GlNy3IHsDBYi5q6kSJTqMJUZbUBo=");
    LiveStorage_ParseKeysTxt2("mp_common,1,LKBcjAtLFtrhGQqXZP3GQN2MXbGe4yBA4CJ8KK+Tmyw=\nzm_common,1,uVkxOTxN2vKCJHt2p iY5tGqy33LKZ0dKlKizutZifuI=\nwz_common,1,qYOw3RHpf/4LoNqha7D8w0l1uJs1a8f1GXvz9RSlcpc=\ncp_common,1,1Xms8bivDnvtle9GlNy3IHsDBYi5q6kSJTqMJUZbUBo=");
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