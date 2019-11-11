#include <basetsd.h> //ULONG_PTR
#include <windef.h>
#include <windows.h> //GetProcAddress(...)
//#include <winternl.h> //for struct PPEB

//from http://msdn.microsoft.com/en-us/library/ms684280%28v=vs.85%29.aspx
typedef struct _PROCESS_BASIC_INFORMATION {
    PVOID Reserved1;
//    PPEB PebBaseAddress;
    PVOID PebBaseAddress;
    PVOID Reserved2[2];
    ULONG_PTR UniqueProcessId;
    PVOID Reserved3;
} PROCESS_BASIC_INFORMATION;

//from http://stackoverflow.com/questions/185254/how-can-a-win32-process-get-the-pid-of-its-parent:
// / see http://msdn.microsoft.com/en-us/library/ms684280%28v=vs.85%29.aspx:
ULONG_PTR GetParentProcessIDviaNtQueryInformationProcess()
{
  PROCESS_BASIC_INFORMATION process_basic_information;
  ULONG_PTR ar_ulong_ptrProcessBasicInformation[6];
  ULONG ulSize = 0;
  LONG (WINAPI * NtQueryInformationProcess)(
   HANDLE ProcessHandle,
   ULONG ProcessInformationClass,
   PVOID ProcessInformation,
   ULONG ProcessInformationLength,
   PULONG ReturnLength
   );
  * (FARPROC *) & NtQueryInformationProcess =
  ::GetProcAddress( ::LoadLibraryA("NTDLL.DLL"), "NtQueryInformationProcess");
  if(NtQueryInformationProcess)
  {
    //see http://msdn.microsoft.com/en-us/library/ms684280%28v=vs.85%29.aspx
    if( NtQueryInformationProcess(
         ::GetCurrentProcess(), //__in       HANDLE ProcessHandle,
          //0 = ProcessBasicInformation
         0, //__in       PROCESSINFOCLASS ProcessInformationClass,
//         & ar_ulong_ptrProcessBasicInformation,
         & process_basic_information,
//         sizeof(ar_ulong_ptrProcessBasicInformation),
         sizeof(process_basic_information),
         & ulSize
       )
       >= 0 && ulSize == //sizeof(ar_ulong_ptrProcessBasicInformation)
           sizeof(process_basic_information)
      )
      return
        //The parent process ID.
        //ar_ulong_ptrProcessBasicInformation[5];
        (ULONG_PTR) process_basic_information.Reserved3;
  }
  return (ULONG_PTR) -1;
}

//DWORD GetParentProcessIDviaProcess32First()
//{
//  HANDLE h = CreateToolhelp32Snapshot(
//    TH32CS_SNAPPROCESS, //__in  DWORD dwFlags,
//    0 //__in  DWORD th32ProcessID
//  );
//  if( h != INVALID_HANDLE_VALUE )
//  {
//    PROCESSENTRY32 pe32;
//    ::Process32First( h);
//    ::Process32Nex(h, & pe32);
//  }
//}

DWORD GetParentProcessID() // By Napalm @ NetCore2K
{
  //http://msdn.microsoft.com/en-us/library/ms684868%28v=vs.85%29.aspx:
  // "A process can use the Process32First function to obtain the process identifier of its parent process."
//  return GetParentProcessIDviaProcess32First
  return GetParentProcessIDviaNtQueryInformationProcess();
}
