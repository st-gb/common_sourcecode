##(c) from 2024 by Stefan Gebauer(Computer Science Master from TU Berlin)
##@author Stefan Gebauer(TU Berlin matriculation number 361095)
##File with CMake code that is common for C and C++.

if(NOT DEFINED cmnSrcRootDir)
  set(cmnSrcRootDir "${PROJECT_SOURCE_DIR}/../../../../../../..")
  include(${cmnSrcRootDir}/FileSystem/setAndResolveFileSysDir.cmake)
  setAndResolveFileSysDir(cmnSrcRootDir ${cmnSrcRootDir} 0)
  message("Set \"cmnSrcRootDir\" via CMake to \"${cmnSrcRootDir}\"")
else()
  message("Set \"cmnSrcRootDir\" via (CMake) compiler definition to "
    "\"${cmnSrcRootDir}\"")
endif()

set(cmnSrcOS ${cmnSrcRootDir}/OperatingSystem)
set(srcFilePaths
  ${srcFilePaths}
  ${cmnSrcOS}/Windows/hardware/dataCarrier/getIdentityEnRsltMsgs.c
  )

#include(${cmnSrcDir}/compiler/C,C++/staticStdC,StdC++.cmake)

#if(CMAKE_GENERATOR NOT MATCHES "Visual Studio")
if(NOT DEFINED dvcIOctrlHeaderFilesDir)
  message("Set \"dvcIOctrlHeaderFilesDir\" to the directory where \"nvme.h\" "
    "resides. If installing the Visual Studio Community Edition 2022, it may be"
    " a path like "
 "\"C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22000.0\\shared\"")
endif()
#endif()

set(inclDirs ${cmnSrcRootDir} ${dvcIOctrlHeaderFilesDir}
  ##_This_ directory for "handling command line arguments" header file.
  .)