#include <Windows.h>

//在DLL入口点中调用MessageBoxA
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        MessageBox(NULL, L"Inject", L"注射成功", MB_OK);
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

//导出函数
extern "C" __declspec(dllexport) int NextHook(int code, WPARAM wParam, LPARAM lParam){
    return CallNextHookEx(NULL, code, wParam, lParam);
}
