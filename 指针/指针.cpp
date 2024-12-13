#include <codecvt>
#include <windows.h>
#include <tlhelp32.h>
#include <iostream>
#include <locale>
#include <vector>
#include <string>

#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "user32.lib")

// 错误处理
class LoaderError
{
public:
    std::string message;

    LoaderError(const std::string& msg) : message(msg)
    {
    }
};

// 获取进程 ID 通过进程名
DWORD GetProcessIdByName(const std::string& name)
{
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snapshot == INVALID_HANDLE_VALUE)
    {
        throw LoaderError("Couldn't create a process list snapshot.");
    }

    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(PROCESSENTRY32);

    if (Process32First(snapshot, &entry))
    {
        do
        {
            std::wstring exeFile(entry.szExeFile);
            if (exeFile == std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>>().from_bytes(name))
            {
                CloseHandle(snapshot);
                return entry.th32ProcessID;
            }
        }
        while (Process32Next(snapshot, &entry));
    }

    CloseHandle(snapshot);
    return 0;
}

// 获取函数地址
FARPROC GetFunctionAddress(HMODULE module, const std::string& function)
{
    if (module == NULL)
    {
        throw LoaderError("Couldn't find a module handle.");
    }

    FARPROC func = GetProcAddress(module, function.c_str());
    if (func == NULL)
    {
        throw LoaderError("Couldn't find a function address.");
    }
    return func;
}

// 注入 DLL
void InjectDLL(DWORD processId, const std::string& dllPath)
{
    HANDLE process = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_VM_OPERATION | PROCESS_VM_WRITE, FALSE, processId);
    if (process == NULL)
    {
        throw LoaderError("OpenProcess returned 0, make sure the target process is opened before running this.");
    }

    size_t pathLen = dllPath.length() + 1;
    LPVOID allocation = VirtualAllocEx(process, NULL, pathLen, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    if (allocation == NULL)
    {
        throw LoaderError("Couldn't allocate memory for the DLL path.");
    }

    if (!WriteProcessMemory(process, allocation, dllPath.c_str(), pathLen, NULL))
    {
        throw LoaderError("Failed to write DLL path to process memory.");
    }

    FARPROC loadLibraryAddr = GetFunctionAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryA");
    HANDLE thread = CreateRemoteThread(process, NULL, 0, (LPTHREAD_START_ROUTINE)loadLibraryAddr, allocation, 0, NULL);
    CloseHandle(thread);
    CloseHandle(process);
}

// 初始化和注入
int main()
{
    std::cout << "Waiting for target process to start" << std::endl;

    DWORD processId = 0;
    std::vector<std::string> processNames = {"GenshinImpact.exe", "YuanShen.exe", "StarRail.exe"};

    while (processId == 0)
    {
        for (const auto& name : processNames)
        {
            try
            {
                processId = GetProcessIdByName(name);
                if (processId != 0)
                {
                    break;
                }
            }
            catch (const LoaderError& e)
            {
                std::cerr << "Error: " << e.message << std::endl;
                return 1;
            }
        }
    }

    std::cout << "Injecting into process with ID: " << processId << std::endl;

    std::string exePath = "./"; // Current directory, adjust as needed
    std::string dllPath = exePath + "library.dll"; // Adjust the DLL name and path as needed

    std::cout << "Library path: " << dllPath << std::endl;

    try
    {
        InjectDLL(processId, dllPath);
        std::cout << "Done." << std::endl;
    }
    catch (const LoaderError& e)
    {
        std::cerr << "Failed to inject the library: " << e.message << std::endl;
        return 1;
    }

    return 0;
}
