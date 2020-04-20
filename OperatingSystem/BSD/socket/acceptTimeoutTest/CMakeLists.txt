project(acceptTimeoutTest)

cmake_minimum_required(VERSION 2.10)#TODO really min. ver.?

set(srcFilePaths
  acceptTimeoutTest.cpp
  ../initSrv.cpp
  ../prepAccept.cpp
  )

add_executable(${PROJECT_NAME} ${srcFilePaths})
