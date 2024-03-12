##(c) from 2024 by Stefan Gebauer(Computer Science Master from TU Berlin)
##@author Stefan Gebauer(TU Berlin matriculation number 361095)

##from https://cmake.org/cmake-tutorial/
cmake_minimum_required(VERSION 2.8)
project(fnSigNmsCppTest)##FuNction SIGnature NaMeS C++ TEST

#see http://stackoverflow.com/questions/8934295/add-source-in-a-subdirectory-to-a-cmake-project
set(srcFlPaths
  ${srcFlPaths}
  ${PROJECT_SOURCE_DIR}/fnSigNmsTestMain.cpp
)

include(../C,C++/fnSigNmsTest.cmake)
