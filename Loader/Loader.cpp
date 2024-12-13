#include <windows.h>
#include <tlhelp32.h>
#include <iostream>
#include <string>
#include <vector>

enum class LoaderError
{
    ProcessListSnapshot,
    ModuleHandle,
    FunctionAddress,
    OpenProcessNull,
    AllocationFailed
};

const char* errorToString(LoaderError err)
{
    switch (err)
    {
    case LoaderError::ProcessListSnapshot: return "Couldn't create a process list snapshot.";
    case LoaderError::ModuleHandle: return "Couldn't find a module handle.";
    case LoaderError::FunctionAddress: return "Couldn't find a function address.";
    case LoaderError::OpenProcessNull: return
            "OpenProcess returned 0, make sure Process is opened before running this.";
    case LoaderError::AllocationFailed: return "Couldn't allocate memory for the DLL path.";
    default: return "Unknown error.";
    }
}

DWORD getProcessIdByName(const std::string& name) {
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snapshot == INVALID_HANDLE_VALUE) {
        std::cerr << errorToString(LoaderError::ProcessListSnapshot) << std::endl;
        return 0;
    }

    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(PROCESSENTRY32);

    if (Process32First(snapshot, &entry)) {
        do {
            // 将 WCHAR 数组转换为 std::string
            int size_needed = WideCharToMultiByte(CP_UTF8, 0, entry.szExeFile, -1, NULL, 0, NULL, NULL);
            std::string exeName(size_needed - 1, 0);
            WideCharToMultiByte(CP_UTF8, 0, entry.szExeFile, -1, &exeName[0], size_needed, NULL, NULL);

            if (exeName == name) {
                CloseHandle(snapshot);
                return entry.th32ProcessID;
            }
        } while (Process32Next(snapshot, &entry));
    }

    CloseHandle(snapshot);
    return 0;
}

FARPROC getFunctionAddress(const std::string& module, const std::string& function)
{
    HMODULE handle = GetModuleHandleA(module.c_str());
    if (!handle)
    {
        std::cerr << errorToString(LoaderError::ModuleHandle) << std::endl;
        return nullptr;
    }

    FARPROC func = GetProcAddress(handle, function.c_str());
    if (!func)
    {
        std::cerr << errorToString(LoaderError::FunctionAddress) << std::endl;
        return nullptr;
    }

    return func;
}

bool inject(DWORD processId, const std::string& dllPath)
{
    HANDLE proc = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_VM_OPERATION | PROCESS_VM_WRITE, FALSE, processId);
    if (!proc)
    {
        std::cerr << errorToString(LoaderError::OpenProcessNull) << std::endl;
        return false;
    }

    SIZE_T pathLen = dllPath.length() + 1;
    LPVOID allocation = VirtualAllocEx(proc, nullptr, pathLen, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    if (!allocation)
    {
        std::cerr << errorToString(LoaderError::AllocationFailed) << std::endl;
        CloseHandle(proc);
        return false;
    }

    std::cout << "Allocated memory for the library path at 0x" << allocation << std::endl;

    if (!WriteProcessMemory(proc, allocation, dllPath.c_str(), pathLen, nullptr))
    {
        std::cerr << "WriteProcessMemory failed." << std::endl;
        VirtualFreeEx(proc, allocation, 0, MEM_RELEASE);
        CloseHandle(proc);
        return false;
    }

    FARPROC loadLibrary = getFunctionAddress("kernel32.dll", "LoadLibraryA");
    if (!loadLibrary)
    {
        VirtualFreeEx(proc, allocation, 0, MEM_RELEASE);
        CloseHandle(proc);
        return false;
    }

    std::cout << "LoadLibraryA found at 0x" << loadLibrary << std::endl;

    HANDLE thread = CreateRemoteThread(proc, nullptr, 0, (LPTHREAD_START_ROUTINE)loadLibrary, allocation, 0, nullptr);
    if (!thread)
    {
        std::cerr << "CreateRemoteThread failed." << std::endl;
        VirtualFreeEx(proc, allocation, 0, MEM_RELEASE);
        CloseHandle(proc);
        return false;
    }

    WaitForSingleObject(thread, INFINITE);
    CloseHandle(thread);
    VirtualFreeEx(proc, allocation, 0, MEM_RELEASE);
    CloseHandle(proc);
    return true;
}

int main()
{
    std::cout << "Waiting for Process to start" << std::endl;

    DWORD processId = 0;
    while (!processId)
    {
        for (const auto& processName : {"notepad.exe", "notepad.exe", "notepad.exe"})
        {
            processId = getProcessIdByName(processName);
            if (processId)
            {
                break;
            }
        }
    }

    std::cout << "Injecting into " << processId << std::endl;

    char buffer[MAX_PATH];
    GetModuleFileNameA(nullptr, buffer, MAX_PATH);
    std::string exePath(buffer);
    exePath = exePath.substr(0, exePath.find_last_of("\\/") + 1) + "Library.dll";

    std::cout << "Library path: " << exePath << std::endl;

    if (!inject(processId, exePath))
    {
        std::cerr << "Failed to inject the library." << std::endl;
        return 1;
    }

    std::cout << "Done." << std::endl;
    return 0;
}
