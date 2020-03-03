#from https://cmake.org/cmake-tutorial/
cmake_minimum_required(VERSION 2.8)#TODO set to the real CMake minimal version

project(IconDrawTest)

set(CommonSourceCodeRootPath ../../../..)
  
set(CMAKE_BUILD_TYPE Release)
  
message("CMAKE_BUILD_TYPE:${CMAKE_BUILD_TYPE}")
  
#add_definitions(-D_DEBUG -Wno-deprecated-declarations)

#Avoid g++ warning:"'virtual void wxWindowBase::SetInitialBestSize(const 
# wxSize&)' is deprecated: use SetInitialSize() instead."
#https://stackoverflow.com/questions/13459602/how-can-i-get-rid-of-deprecated-warnings-in-deprecated-functions-in-gcc
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated")

#https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html#Warning-Options
# https://gcc.gnu.org/onlinedocs/gcc-3.4.6/gcc/Warning-Options.html
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-deprecated-declarations")
#Alternative: '#pragma gcc diagnostic ignored "-Wdeprecated-declarations"'
# before including the affected wxWidgets header file?!
 
set(SOURCE_FILE_PATHS
 main.cpp
 ${CommonSourceCodeRootPath}/wxWidgets/icon/IconDrawer.cpp
 )

set(wxWidgets_ROOT_DIR ${wxLibsRootDir})
include(${CommonSourceCodeRootPath}/wxWidgets/callFindwxWidgets.cmake)

include_directories(${CommonSourceCodeRootPath} ${wxInclDir})

add_executable(${PROJECT_NAME} ${SOURCE_FILE_PATHS})

#show1ItmPerLne(...), showMsg(...)
include(${CommonSourceCodeRootPath}/CMake/ShowMsg_CompLvl.cmake)

message("target_link_ibraries with wxWidgets_LIBRARIES")
show1ItmPerLne(5 "wxWidgets_LIBRARIES:" "${wxWidgets_LIBRARIES}")
#https://wiki.wxwidgets.org/CMake
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})
