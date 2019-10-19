#from https://cmake.org/cmake-tutorial/
#TODO set to the real CMake minimal version
cmake_minimum_required (VERSION 2.8)

project(ThreadExitCodeTest)

set(CommonSourceCodeRootPath
  ../../../..
  )

add_definitions(-D_DEBUG)

if(UNIX)#unixoid operating systems:Linux etc.
 set(LIBRARIES
  pthread)
 set(SOURCE_FILE_PATHS
  #nativeThread_type for Linux
  ${CommonSourceCodeRootPath}/OperatingSystem/POSIX/multithread/pthreadBasedI_Thread.cpp)
endif()

set(
 SOURCE_FILE_PATHS
 ${SOURCE_FILE_PATHS}
 main.cpp
 ${CommonSourceCodeRootPath}/OperatingSystem/multithread/I_Thread.cpp
 )

include_directories(${CommonSourceCodeRootPath})

add_executable(${PROJECT_NAME} ${SOURCE_FILE_PATHS})
target_link_libraries(${PROJECT_NAME} ${LIBRARIES})

