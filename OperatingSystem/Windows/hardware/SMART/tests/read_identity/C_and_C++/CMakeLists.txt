project(readSMART_identity)

cmake_minimum_required(VERSION 2.10)#TODO really min. ver.?

set(cmnSrcDir ${PROJECT_SOURCE_DIR}/../../../../../../..)

set(CmnSrcOS ${cmnSrcDir}/OperatingSystem)
set(srcFilePaths
  main.c
  ${CmnSrcOS}/Windows/hardware/dataCarrier/getIdentityEnRsltMsgs.c
  )

#include(${cmnSrcDir}/compiler/C,C++/staticStdC,StdC++.cmake)

include_directories(${cmnSrcDir})

include(${cmnSrcDir}/CMake/ShowMsg_CompLvl.cmake)
#showInclDirs(6)

include(${cmnSrcDir}/dataType/charStr/suffixCMakeBuildType.cmake)
set(exeName ${PROJECT_NAME})
suffixCMakeBuildType(exeName 1)

add_executable(${exeName} ${srcFilePaths})