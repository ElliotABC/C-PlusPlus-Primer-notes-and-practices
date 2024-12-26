#include <iostream>
#include <vector>
#include <Windows.h>
#include <TlHelp32.h>
#include <Psapi.h>
#include <string>
#include <tchar.h>
using namespace std;

//由进程名获取进程ID
bool FindProcess(const wchar_t* processName, DWORD& dwProcess) {
    PROCESSENTRY32 pe32;  
    pe32.dwSize = sizeof(PROCESSENTRY32);      
    //获取进程快照
    HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);     
    if (hProcessSnap == INVALID_HANDLE_VALUE) {
        return false;
    }
    if (Process32First(hProcessSnap, &pe32)) {
        do {
            if (wcscmp(pe32.szExeFile, processName) == 0) {
                dwProcess = pe32.th32ProcessID;
                break;
            }
        } while (Process32Next(hProcessSnap, &pe32));
    }
    CloseHandle(hProcessSnap);
    if(dwProcess == 0) {
        return false;
    }
    return true;
}

//DLL远程线程注入
void CreateRemoteThread_Inject(){
    DWORD dwProcess = 0;
    char myDLL[] = "C:\\testDLL.dll";
    //查找进程FlappyBird.exe
    if(FindProcess(L"FlappyBird.exe", dwProcess)){
        HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwProcess);    //打开进程
        LPVOID allocatedMem = VirtualAllocEx(hProcess, NULL, sizeof(myDLL), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);  //在进程中分配内存
        WriteProcessMemory(hProcess, allocatedMem, myDLL, sizeof(myDLL), NULL); //写入DLL路径
        HMODULE hModule = LoadLibrary(L"kernel32.dll");                //获取kernel32.dll模块句柄
        //获取LoadLibraryA函数地址
        LPTHREAD_START_ROUTINE pfnStarAddress = (LPTHREAD_START_ROUTINE)GetProcAddress(hModule, "LoadLibraryA");
        if(pfnStarAddress == NULL){
            cout << "GetProcAddress failed" << endl;
            return;
        }
        HANDLE hRemoteThread = CreateRemoteThread(hProcess, NULL, NULL, pfnStarAddress, allocatedMem, NULL, NULL);  //创建远程线程
        if(hRemoteThread == NULL){
            cout << "CreateRemoteThread failed" << endl;
            return;
        }
        WaitForSingleObject(hRemoteThread, INFINITE);  //等待远程线程结束
        CloseHandle(hRemoteThread);                                
        VirtualFreeEx(hProcess, allocatedMem, 0, MEM_FREE);
    }
    return;
}

//***********************************************Shellcode远程线程注入***********************************************
bool EnableDebugPrivilege() {
    HANDLE hToken;
    TOKEN_PRIVILEGES tp;
    //打开进程令牌
    if(!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) {
        cout<<"OpenProcessToken failed"<<endl;
        return false;
    }
    //获取LUID
    if(!LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &tp.Privileges[0].Luid)) {
        cout<<"LookupPrivilegeValue failed"<<endl;
        return false ;
    }
    //设置权限
    tp.PrivilegeCount = 1;  //只设置一个权限
    tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;     //设置权限为启用，如果为SE_PRIVILEGE_REMOVED则为禁用
    //修改进程令牌，提升权限，使得能够访问受保护的进程，如系统进程，其他用户进程等
    if(!AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(tp), NULL, NULL)) {
        cout<<"AdjustTokenPrivileges failed"<<endl;
        return false;
    }
    return true;
}
//该结构体用于接收API和4个字符串
typedef struct _THREAD_PARAM {
	FARPROC pFunc[2];
	char szBuf[4][128];
} THREAD_PARAM, *PTHREAD_PARAM;
typedef HMODULE (WINAPI *PFLOADLIBRARYA)    
(
    LPCSTR lpLibFileName
);  //定义LoadLibraryA函数指针
typedef FARPROC (WINAPI *PFGETPROCADDRESS)
(
    HMODULE hModule,
    LPCSTR lpProcName
); //定义GetProcAddress函数指针
typedef int (WINAPI *PFMESSAGEBOXA)
(
    HWND hWnd,
    LPCSTR lpText,
    LPCSTR lpCaption,
    UINT uType
); //定义MessageBoxA函数指针

//线程函数
//未直接调用相关API和未直接定义使用字符串，而通过THREAD_PARAM结构体以线程参数的形式传递使用
DWORD WINAPI ThreadProc(LPVOID lpParam)
{   
    PTHREAD_PARAM pParam = (PTHREAD_PARAM)lpParam;
    HMODULE hMod = NULL;
    FARPROC pFunc = NULL;
    hMod = ((PFLOADLIBRARYA)pParam->pFunc[0])(pParam->szBuf[0]);        //调用LoadLibraryA函数
    if (hMod == NULL)
    {
        return 1;
    }
    pFunc = ((PFGETPROCADDRESS)pParam->pFunc[1])(hMod, pParam->szBuf[1]);   //获取MessageBoxA函数地址
    if (pFunc == NULL)
    {
        return 1;
    }
    ((PFMESSAGEBOXA)pFunc)(NULL, pParam->szBuf[2], pParam->szBuf[3], 0);    //调用MessageBoxA函数
    return 0;
}

//shellcode 注入
void CreateRemoteThread_shellcode()
{
    EnableDebugPrivilege(); //提升权限
    DWORD dwProcess = 0;
    //查找进程FlappyBird.exe
    if(FindProcess(L"FlappyBird.exe", dwProcess)){
        HMODULE hMod = NULL;
        THREAD_PARAM param = {0,};  //定义线程结构体变量
        HANDLE hProcess = NULL;
        HANDLE hThread = NULL;
        LPVOID pRemoteBuf[2] = {0,};
        DWORD dwSize = 0;

        hMod = GetModuleHandleA("kernel32.dll");

        //设置THREAD_PARAM结构体
	    //加载到所有进程的kernel32.dll的地址都相同，因此从本进程获取的API与在目标进程中获取的API地址是一样的
        param.pFunc[0] = GetProcAddress(hMod, "LoadLibraryA");
        param.pFunc[1] = GetProcAddress(hMod, "GetProcAddress");
        strcpy_s(param.szBuf[0], "user32.dll");
        strcpy_s(param.szBuf[1], "MessageBoxA");
        strcpy_s(param.szBuf[2], "shellcode Success");
        strcpy_s(param.szBuf[3], "inject");
        
        hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwProcess);
        if (hProcess == NULL)
        {
            cout<<"OpenProcess failed"<<endl;
            return;
        }
        //分配内存
        dwSize = sizeof(THREAD_PARAM);
        pRemoteBuf[0] = VirtualAllocEx(hProcess, NULL, dwSize, MEM_COMMIT, PAGE_READWRITE);
        if (pRemoteBuf[0] == NULL)
        {
            cout<<"VirtualAllocEx failed"<<endl;
            return;
        }
        //将线程参数写入目标进程
        if (!WriteProcessMemory(hProcess, pRemoteBuf[0], (LPVOID)&param, dwSize, NULL))
        {
            cout<<"WriteProcessMemory failed"<<endl;
            return;
        }
        dwSize = (DWORD)CreateRemoteThread_shellcode - (DWORD)ThreadProc;  //计算shellcode大小
        pRemoteBuf[1] = VirtualAllocEx(hProcess, NULL, dwSize, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
        if (pRemoteBuf[1] == NULL)
        {
            cout<<"VirtualAllocEx failed"<<endl;
            return;
        }
        //将shellcode写入目标进程
        if (!WriteProcessMemory(hProcess, pRemoteBuf[1], (LPVOID)ThreadProc, dwSize, NULL))
        {
            cout<<"WriteProcessMemory failed"<<endl;
            return;
        }
        //创建远程线程
        hThread = CreateRemoteThread(
            hProcess, 
            NULL, 
            0, 
            (LPTHREAD_START_ROUTINE)pRemoteBuf[1], //线程函数地址
            pRemoteBuf[0],                     //线程参数地址
            0, NULL
        );
        if (hThread == NULL)
        {
            cout<<"CreateRemoteThread failed"<<endl;
            return;
        }
        WaitForSingleObject(hThread, INFINITE);
        CloseHandle(hThread);
        CloseHandle(hProcess);
    }
}

//***********************************************消息钩子注入***********************************************

int SetWindowHookEx_inject() {
    HWND hwnd = FindWindow(NULL, L"FlappyBird"); //查找窗口
    if (hwnd == NULL) {
        cout << "FindWindow failed" << endl;
        return 1;
    }
    DWORD pid = NULL;
    DWORD tid = GetWindowThreadProcessId(hwnd, &pid); //获取进程ID
    if (tid == NULL) {
        cout << "GetWindow tid/pid failed" << endl;
        return 1;
    }
    
    HMODULE dll = LoadLibraryEx(L"C:\\testDLL.dll", NULL, DONT_RESOLVE_DLL_REFERENCES); //加载DLL
    if (dll == NULL) {
        cout << "LoadLibraryEx DLL failed" << endl;
        return 1;
    }
    
    HOOKPROC addr = (HOOKPROC)GetProcAddress(dll, "NextHook"); //获取钩子函数地址
    if (addr == NULL) {
        cout << "GetProcAddress failed" << endl;
        return 1;
    }
    
    HHOOK handle = SetWindowsHookEx(WH_GETMESSAGE, addr, dll, tid); //设置钩子
    if (handle == NULL) {
        cout << "SetWindowsHookEx failed" << endl;
        return EXIT_FAILURE;
    }
    
    PostThreadMessage(tid, WM_NULL, 0, 0); //发送消息,触发钩子
    cout<<"SetWindowsHookEx_inject success"<<endl;
    cout<<"Press any key to unhook"<<endl;
    getchar();

    BOOL unhook = UnhookWindowsHookEx(handle); //卸载钩子
    if (unhook == NULL) {
        cout << "UnhookWindowsHookEx failed" << endl;
        return EXIT_FAILURE;
    }
    return 0;
}

//***********************************************APC注入***********************************************

//根据进程名获取进程ID及其所有线程ID
bool FindProcess2(const wchar_t* processName, DWORD& dwProcess, vector<DWORD>& dwThreads) {
    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32);
    HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);  //创建进程快照
    if (hProcessSnap == INVALID_HANDLE_VALUE) {
        cout << "CreateToolhelp32Snapshot failed" << endl;
        return false;
    }
    if (!Process32First(hProcessSnap, &pe32)) {     //获取第一个进程信息
        cout << "Process32First failed" << endl;
        CloseHandle(hProcessSnap);
        return false;
    }
    do {
        if (wcscmp(pe32.szExeFile, processName) == 0) {
            dwProcess = pe32.th32ProcessID;
            break;
        }
    } while (Process32Next(hProcessSnap, &pe32));
    CloseHandle(hProcessSnap);
    if (dwProcess == NULL) {
        cout << "FindProcess failed" << endl;
        return false;
    }
    THREADENTRY32 te32;
    te32.dwSize = sizeof(THREADENTRY32);
    HANDLE hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);    //创建线程快照
    if (hThreadSnap == INVALID_HANDLE_VALUE) {
        cout << "CreateToolhelp32Snapshot failed" << endl;
        return false;
    }
    if (!Thread32First(hThreadSnap, &te32)) {
        cout << "Thread32First failed" << endl;
        CloseHandle(hThreadSnap);
        return false;
    }
    do {
        if (te32.th32OwnerProcessID == dwProcess) {
            dwThreads.push_back(te32.th32ThreadID);     //获取目标进程的所有线程ID
        }
    } while (Thread32Next(hThreadSnap, &te32));
    CloseHandle(hThreadSnap);
    if (dwThreads.size() == 0) {
        cout << "FindThread failed" << endl;
        return false;
    }
    return true;
}

void APC_Inject(){
    DWORD pid;
    vector<DWORD> tids;     //需要获取进程所有的线程ID
    if (FindProcess2(L"FlappyBird.exe", pid, tids)) {
        HANDLE hProcess = OpenProcess(PROCESS_VM_WRITE | PROCESS_VM_OPERATION, FALSE, pid);
        if (hProcess == NULL) {
            cout << "OpenProcess failed" << endl;
            return;
        }
        auto p = VirtualAllocEx(hProcess, NULL, 1<<12, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE); //在目标进程中申请内存
        wchar_t buffer[] = L"C:\\testDLL.dll";
        WriteProcessMemory(hProcess, p, buffer, sizeof(buffer), NULL); //将DLL路径写入目标进程中
        for(const auto& tid: tids){
            HANDLE hThread = ::OpenThread(THREAD_SET_CONTEXT, FALSE, tid);
            if (hThread == NULL) {
                cout << "OpenThread failed" << endl;
                return;
            }
            QueueUserAPC((PAPCFUNC)GetProcAddress(GetModuleHandle(L"kernel32"),"LoadLibraryW"),hThread,(ULONG_PTR)p); //将APC注入到目标进程中
        }
        VirtualFreeEx(hProcess, p, 0, MEM_RELEASE | MEM_DECOMMIT);
    }
}



int main()
{
    printf("Inject\n");
    CreateRemoteThread_Inject();
    //CreateRemoteThread_shellcode();
    //SetWindowHookEx_inject();
    //APC_Inject();
    printf("执行结束\n");
    getchar();
    return 0;
}

