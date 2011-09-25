/*
 * StopDependentServices.cpp
 *
 *  Created on: 10.09.2011
 *      Author: Stefan
 */


//the following code is from
//http://msdn.microsoft.com/en-us/library/ms686335%28v=VS.85%29.aspx
////
//// Purpose:
////   Stops the service.
////
//// Parameters:
////   None
////
//// Return value:
////   None
////
//VOID __stdcall DoStopSvc()
//{
//    SERVICE_STATUS_PROCESS ssp;
//    DWORD dwStartTime = GetTickCount();
//    DWORD dwBytesNeeded;
//    DWORD dwTimeout = 30000; // 30-second time-out
//    DWORD dwWaitTime;
//
//    // Get a handle to the SCM database.
//
//    schSCManager = OpenSCManager(
//        NULL,                    // local computer
//        NULL,                    // ServicesActive database
//        SC_MANAGER_ALL_ACCESS);  // full access rights
//
//    if (NULL == schSCManager)
//    {
//        printf("OpenSCManager failed (%d)\n", GetLastError());
//        return;
//    }
//
//    // Get a handle to the service.
//
//    schService = OpenService(
//        schSCManager,         // SCM database
//        szSvcName,            // name of service
//        SERVICE_STOP |
//        SERVICE_QUERY_STATUS |
//        SERVICE_ENUMERATE_DEPENDENTS);
//
//    if (schService == NULL)
//    {
//        printf("OpenService failed (%d)\n", GetLastError());
//        CloseServiceHandle(schSCManager);
//        return;
//    }
//
//    // Make sure the service is not already stopped.
//
//    if ( !QueryServiceStatusEx(
//            schService,
//            SC_STATUS_PROCESS_INFO,
//            (LPBYTE)&ssp,
//            sizeof(SERVICE_STATUS_PROCESS),
//            &dwBytesNeeded ) )
//    {
//        printf("QueryServiceStatusEx failed (%d)\n", GetLastError());
//        goto stop_cleanup;
//    }
//
//    if ( ssp.dwCurrentState == SERVICE_STOPPED )
//    {
//        printf("Service is already stopped.\n");
//        goto stop_cleanup;
//    }
//
//    // If a stop is pending, wait for it.
//
//    while ( ssp.dwCurrentState == SERVICE_STOP_PENDING )
//    {
//        printf("Service stop pending...\n");
//
//        // Do not wait longer than the wait hint. A good interval is
//        // one-tenth of the wait hint but not less than 1 second
//        // and not more than 10 seconds.
//
//        dwWaitTime = ssp.dwWaitHint / 10;
//
//        if( dwWaitTime < 1000 )
//            dwWaitTime = 1000;
//        else if ( dwWaitTime > 10000 )
//            dwWaitTime = 10000;
//
//        Sleep( dwWaitTime );
//
//        if ( !QueryServiceStatusEx(
//                 schService,
//                 SC_STATUS_PROCESS_INFO,
//                 (LPBYTE)&ssp,
//                 sizeof(SERVICE_STATUS_PROCESS),
//                 &dwBytesNeeded ) )
//        {
//            printf("QueryServiceStatusEx failed (%d)\n", GetLastError());
//            goto stop_cleanup;
//        }
//
//        if ( ssp.dwCurrentState == SERVICE_STOPPED )
//        {
//            printf("Service stopped successfully.\n");
//            goto stop_cleanup;
//        }
//
//        if ( GetTickCount() - dwStartTime > dwTimeout )
//        {
//            printf("Service stop timed out.\n");
//            goto stop_cleanup;
//        }
//    }
//
//    // If the service is running, dependencies must be stopped first.
//
//    StopDependentServices();
//
//    // Send a stop code to the service.
//
//    if ( !ControlService(
//            schService,
//            SERVICE_CONTROL_STOP,
//            (LPSERVICE_STATUS) &ssp ) )
//    {
//        printf( "ControlService failed (%d)\n", GetLastError() );
//        goto stop_cleanup;
//    }
//
//    // Wait for the service to stop.
//
//    while ( ssp.dwCurrentState != SERVICE_STOPPED )
//    {
//        Sleep( ssp.dwWaitHint );
//        if ( !QueryServiceStatusEx(
//                schService,
//                SC_STATUS_PROCESS_INFO,
//                (LPBYTE)&ssp,
//                sizeof(SERVICE_STATUS_PROCESS),
//                &dwBytesNeeded ) )
//        {
//            printf( "QueryServiceStatusEx failed (%d)\n", GetLastError() );
//            goto stop_cleanup;
//        }
//
//        if ( ssp.dwCurrentState == SERVICE_STOPPED )
//            break;
//
//        if ( GetTickCount() - dwStartTime > dwTimeout )
//        {
//            printf( "Wait timed out\n" );
//            goto stop_cleanup;
//        }
//    }
//    printf("Service stopped successfully\n");
//
//stop_cleanup:
//    CloseServiceHandle(schService);
//    CloseServiceHandle(schSCManager);
//}
//
//BOOL __stdcall StopDependentServices()
//{
//    DWORD i;
//    DWORD dwBytesNeeded;
//    DWORD dwCount;
//
//    LPENUM_SERVICE_STATUS   lpDependencies = NULL;
//    ENUM_SERVICE_STATUS     ess;
//    SC_HANDLE               hDepService;
//    SERVICE_STATUS_PROCESS  ssp;
//
//    DWORD dwStartTime = GetTickCount();
//    DWORD dwTimeout = 30000; // 30-second time-out
//
//    // Pass a zero-length buffer to get the required buffer size.
//    if ( EnumDependentServices( schService, SERVICE_ACTIVE,
//         lpDependencies, 0, &dwBytesNeeded, &dwCount ) )
//    {
//         // If the Enum call succeeds, then there are no dependent
//         // services, so do nothing.
//         return TRUE;
//    }
//    else
//    {
//        if ( GetLastError() != ERROR_MORE_DATA )
//            return FALSE; // Unexpected error
//
//        // Allocate a buffer for the dependencies.
//        lpDependencies = (LPENUM_SERVICE_STATUS) HeapAlloc(
//            GetProcessHeap(), HEAP_ZERO_MEMORY, dwBytesNeeded );
//
//        if ( !lpDependencies )
//            return FALSE;
//
//        __try {
//            // Enumerate the dependencies.
//            if ( !EnumDependentServices( schService, SERVICE_ACTIVE,
//                lpDependencies, dwBytesNeeded, &dwBytesNeeded,
//                &dwCount ) )
//            return FALSE;
//
//            for ( i = 0; i < dwCount; i++ )
//            {
//                ess = *(lpDependencies + i);
//                // Open the service.
//                hDepService = OpenService( schSCManager,
//                   ess.lpServiceName,
//                   SERVICE_STOP | SERVICE_QUERY_STATUS );
//
//                if ( !hDepService )
//                   return FALSE;
//
//                __try {
//                    // Send a stop code.
//                    if ( !ControlService( hDepService,
//                            SERVICE_CONTROL_STOP,
//                            (LPSERVICE_STATUS) &ssp ) )
//                    return FALSE;
//
//                    // Wait for the service to stop.
//                    while ( ssp.dwCurrentState != SERVICE_STOPPED )
//                    {
//                        Sleep( ssp.dwWaitHint );
//                        if ( !QueryServiceStatusEx(
//                                hDepService,
//                                SC_STATUS_PROCESS_INFO,
//                                (LPBYTE)&ssp,
//                                sizeof(SERVICE_STATUS_PROCESS),
//                                &dwBytesNeeded ) )
//                        return FALSE;
//
//                        if ( ssp.dwCurrentState == SERVICE_STOPPED )
//                            break;
//
//                        if ( GetTickCount() - dwStartTime > dwTimeout )
//                            return FALSE;
//                    }
//                }
//                __finally
//                {
//                    // Always release the service handle.
//                    CloseServiceHandle( hDepService );
//                }
//            }
//        }
//        __finally
//        {
//            // Always free the enumeration buffer.
//            HeapFree( GetProcessHeap(), 0, lpDependencies );
//        }
//    }
//    return TRUE;
//}

