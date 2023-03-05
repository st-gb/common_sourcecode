project(readSMART_identity)

cmake_minimum_required(VERSION 2.10)#TODO really min. ver.?

set(cmnSrcDir ${PROJECT_SOURCE_DIR}/../../../../../../..)

set(CmnSrcOS ${cmnSrcDir}/OperatingSystem)
set(srcFilePaths
  main.c
  )

#include(${cmnSrcDir}/compiler/C,C++/staticStdC,StdC++.cmake)

include_directories(${cmnSrcDir})

include(${cmnSrcDir}/CMake/ShowMsg_CompLvl.cmake)
#showInclDirs(6)

if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
  set(exeName ${PROJECT_NAME}_dbg)
else()
  set(exeName ${PROJECT_NAME})
endif()
add_executable(${exeName} ${srcFilePaths})