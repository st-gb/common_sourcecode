project(acceptTimeoutTest)

cmake_minimum_required(VERSION 2.10)#TODO really min. ver.?

#For "include_directories(...)" and "include(...)" 
set(cmnSrcDir ../../../..)

include_directories(${cmnSrcDir})

set(srcFilePaths
  acceptTimeoutTest.cpp
  ../initSrv.cpp
  ../prepAccept.cpp
  )

set(exeFileName ${PROJECT_NAME}_${CMAKE_BUILD_TYPE})
include(${cmnSrcDir}/CMake/addExeFileExt.cmake)
#For filtering by ".elf" or ".exe" in file ".gitignore"
addExeFileExt(exeFileName)

add_executable(${exeFileName} ${srcFilePaths})
