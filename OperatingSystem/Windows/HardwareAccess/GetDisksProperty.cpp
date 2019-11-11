#ifdef MS_COMPILER
  #include <windef.h> //for "BYTE" etc.
  #include "afx.h" //for TRACE()
#endif

//Make "windows.h" as the 1st include: else g++ compilation errors like
// "error: `GetDriveTypeW' cannot be used as a function"
#include <windows.h> //DeviceIoControl(...)
//#include <vector>
//#include <winioctl.h> //from (Windows/ Microsoft) Platform SDK

#include "GetDisksProperty.hpp"
#include "HardwareAccess.hpp" //IOCTL_STORAGE_QUERY_PROPERTY
//#include "global.h"
//#include "../Controller/Sync_String.h"
//#include "UserInterface/UserInterface.hpp"

/****************************************************************************
*FUNCTION:GetDisksProperty(HANDLE hDevice, PSTORAGE_DEVICE_DESCRIPTOR pDevDesc)
*PURPOSE:get the info of specified device
****************************************************************************/
BOOL GetDisksProperty(HANDLE hDevice, PSTORAGE_DEVICE_DESCRIPTOR pDevDesc)
{
	STORAGE_PROPERTY_QUERY	Query;	// input param for query
	DWORD dwOutBytes;				// IOCTL output length
	BOOL bResult;					// IOCTL return val

	// specify the query type
	Query.PropertyId = StorageDeviceProperty;
	Query.QueryType = PropertyStandardQuery;

	// Query using IOCTL_STORAGE_QUERY_PROPERTY 
	bResult = ::DeviceIoControl(
	  hDevice,			// device handle
    IOCTL_STORAGE_QUERY_PROPERTY,			// info of device property
    & Query,
    sizeof(STORAGE_PROPERTY_QUERY),	// input data buffer
    pDevDesc, pDevDesc->Size,				// output data buffer
    & dwOutBytes,							// out's length
    (LPOVERLAPPED) NULL
    );
	return bResult;
}
