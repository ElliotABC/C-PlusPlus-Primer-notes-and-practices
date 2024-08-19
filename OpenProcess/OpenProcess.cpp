#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>
#include <stdio.h>
#include <iostream>
bool GetProcessList();

void printError(TCHAR const* msg);

int main(void)
{
    GetProcessList();
    return 0;
}

bool GetProcessList()
{
    HANDLE hProcessSnap;
    HANDLE hProcess;
    PROCESSENTRY32 pe32;
    DWORD dwPriorityClass;
    WCHAR szProcessName[260] = TEXT("winlogon.exe");
    // Take a snapshot of all processes in the system.
    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE)
    {
        printError(TEXT("CreateToolhelp32Snapshot (of processes)"));
        return (false);
    }

    pe32.dwSize = sizeof(PROCESSENTRY32);
    if (!Process32First(hProcessSnap, &pe32))
    {
        printError(TEXT("Process32First"));
        CloseHandle(hProcessSnap);
        return (false);
    }
    do
    {
        if (std::wcscmp(pe32.szExeFile, szProcessName) == 1)
        {
            _tprintf(TEXT("\n\n====================================================="));
            _tprintf(TEXT("\nPROCESS NAME:  %s"), pe32.szExeFile);
            _tprintf(TEXT("\n-------------------------------------------------------"));
            dwPriorityClass = 0;
            hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, pe32.th32ProcessID);
            if (hProcess == NULL)
                printError(TEXT("OpenProcess"));
            else
            {
                dwPriorityClass = GetPriorityClass(hProcess);
                if (!dwPriorityClass)
                    printError(TEXT("GetPriorityClass"));
                CloseHandle(hProcess);
            }

            _tprintf(TEXT("\n  Process ID        = 0x%08X"), pe32.th32ProcessID);
            _tprintf(TEXT("\n  Thread count      = %d"), pe32.cntThreads);
            _tprintf(TEXT("\n  Parent process ID = 0x%08X"), pe32.th32ParentProcessID);
            _tprintf(TEXT("\n  Priority base     = %d"), pe32.pcPriClassBase);
            if (dwPriorityClass)
                _tprintf(TEXT("\n  Priority class    = %d"), dwPriorityClass);
        }
        
    }
    while (Process32Next(hProcessSnap, &pe32));

    CloseHandle(hProcessSnap);
    return (true);
}

void printError(TCHAR const* msg)
{
    DWORD eNum;
    TCHAR sysMsg[256];
    TCHAR* p;

    eNum = GetLastError();
    FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                  NULL, eNum,
                  MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
                  sysMsg, 256, NULL);

    // Trim the end of the line and terminate it with a null
    p = sysMsg;
    while ((*p > 31) || (*p == 9))
        ++p;
    do { *p-- = 0; }
    while ((p >= sysMsg) &&
        ((*p == '.') || (*p < 33)));


    _tprintf(TEXT("\n  WARNING: %s failed with error %d (%s)"), msg, eNum, sysMsg);
}
