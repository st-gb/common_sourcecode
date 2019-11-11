#include ""

bool GetAllocatedFileSizeWithinFileSystem(
  std::string & r_stdstrFullFilePath,
  DWORD dwClusterSize,
  ULARGE_INTEGER & r_uliAllocatedFileSize)
{
  bool bSuccess = false ;
  WIN32_FILE_ATTRIBUTE_DATA win32FileAttributeData;
  if( 
    //MSDN:"The GetFileAttributesEx function retrieves attributes for a 
    //specified file or directory."
    ::GetFileAttributesEx(
      // pointer to string that specifies a file or directory
      //(LPCTSTR) 
      r_stdstrFullFilePath.c_str(),
      // value that specifies the type of 
      // attribute information to obtain
      GetFileExInfoStandard, 
      // pointer to buffer to receive attribute information
      &win32FileAttributeData
    ) 
  )
  {
    r_uliAllocatedFileSize = ::GetAllocatedFileSizeWithinFileSystem(
      win32FileAttributeData.nFileSizeHigh,
      win32FileAttributeData.nFileSizeLow,
      dwClusterSize);
    bSuccess = true ;
  }
  return bSuccess ;
}
