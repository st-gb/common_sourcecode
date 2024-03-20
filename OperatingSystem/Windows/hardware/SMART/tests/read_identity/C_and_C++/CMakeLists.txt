cmake_minimum_required(VERSION 2.10)#TODO really min. ver.?
project(readSMART_identityTestCandCpp)##TEST for C and C++

include(../C_and_C++/readSMART_IDtest_init.cmake)

set(srcFilePaths
  ${srcFilePaths}
  main.c
  )

include(../C_and_C++/readSMART_IDtest_buildExe.cmake)
