cmake_minimum_required(VERSION 2.10)#TODO really min. ver.?
project(readSMART_identityTestCpp)##TEST for C++

set(srcFilePaths
  ${srcFilePaths}
  readSMART_identityMain.cpp
)

include(../C_and_C++/readSMART_IDtest_init.cmake)

if(NOT DEFINED cxxoptsRootDir)
  set(cxxoptsRootDir "${cmnSrcRootDir}/../..")
  setAndResolveFileSysDir(cxxoptsRootDir ${cxxoptsRootDir} 0)
  message("Set \"cxxoptsRootDir\" via CMake to \"${cxxoptsRootDir}\"")
else()
  message("Set \"cxxoptsRootDir\" via (CMake) compiler definition to "
    "\"${cxxoptsRootDir}\"")
endif()

set(inclDirs ${inclDirs} ${cxxoptsRootDir})

include(../C_and_C++/readSMART_IDtest_buildExe.cmake)
