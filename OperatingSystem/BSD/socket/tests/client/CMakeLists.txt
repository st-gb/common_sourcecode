project(socketClientTest)

cmake_minimum_required(VERSION 2.10)#TODO really min. ver.?

set(srcFilePaths
  main.cpp
  ../../prepCnnctToSrv.c#prepCnnctToSrv(...)
  )

add_executable(${PROJECT_NAME} ${srcFilePaths})
