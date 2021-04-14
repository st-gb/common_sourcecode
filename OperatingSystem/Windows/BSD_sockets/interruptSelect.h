#pragma once///Include guard

#ifdef __cplusplus
namespace OperatingSystem{namespace BSD{namespace sockets{
#endif

void P_APCfunc(ULONG_PTR Parameter)
{
}

/**https://docs.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-select
 * "Note  When issuing a blocking Winsock call such as select with the
 * timeout parameter set to NULL, Winsock may need to wait for a network
 * event before the call can complete. Winsock performs an alertable wait in
 * this situation, which can be interrupted by an asynchronous procedure
 * call (APC) scheduled on the same thread. Issuing another blocking Winsock
 * call inside an APC that interrupted an ongoing blocking Winsock call on
 * the same thread will lead to undefined behavior, and must never be
 * attempted by Winsock clients." */
inline void interruptSelect(void * p_v){
 ///https://stackoverflow.com/questions/30653779/if-windows-select-function-blocks-is-it-always-an-alertable-wait
 /// https://docs.microsoft.com/de-de/windows/win32/api/processthreadsapi/nf-processthreadsapi-queueuserapc?redirectedfrom=MSDN
 if( QueueUserAPC(
   ///https://docs.microsoft.com/en-us/windows/win32/api/winnt/nc-winnt-papcfunc
   P_APCfunc,
   (HANDLE) ((HANDLE *) p_v),
   NULL
     )
   )
   ;
}

#ifdef __cplusplus
}}}///end namespaces
#endif
