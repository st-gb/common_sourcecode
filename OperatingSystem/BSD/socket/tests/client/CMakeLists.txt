project(socketClientTest)

cmake_minimum_required(VERSION 2.10)#TODO really min. ver.?

if(DEFINED cmnSrcDir)
  message("\"cmnSrcDir\" defined for CMake:\"${cmnSrcDir}\"")
else()
  #For "include_directories(...)" and "include(...)"
  set(cmnSrcDir ../../../../..)
endif()
#Get away/resolve ".." etc. in file system path.
get_filename_component(cmnSrcDir "${cmnSrcDir}" ABSOLUTE)

include(${cmnSrcDir}/CMake/setAndResolveFileSysDir.cmake)
#For "include_directories(...)"
setAndResolveFileSysDir(cxxoptsDir ${cmnSrcDir}/../../../cxxopts-master/include
  2)
message("Resolved ${SGR_Magenta}cxxoptsDir${SGR_ColourReset}:\"${cxxoptsDir}\"")

include_directories(${cmnSrcDir} ${cxxoptsDir})


set(srcFilePaths
  main.cpp
  ../../prepCnnctToSrv.c#prepCnnctToSrv(...)
  )

message("CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
set(exeFileName ${PROJECT_NAME}_${CMAKE_BUILD_TYPE})
include(${cmnSrcDir}/CMake/addExeFileExt.cmake)
#For filtering by ".elf" or ".exe" in file ".gitignore"
addExeFileExt(exeFileName)

add_executable(${exeFileName} ${srcFilePaths})
#Must be after "add_executable(...)" because possibly (indirectly) calls
# "set_property(...)". If "set_property(TARGET [...])" is called before
# "add_executable(...)" then CMake error: "set_property could not find TARGET
# socketClientTest_Debug.  Perhaps it has not yet been created."
include(${cmnSrcDir}/libraries/cxxopts/addCompileOptions.cmake)
#Uses target_link_libraries(...) and so must be called after "add_executable":
#http://cmake.org/cmake/help/latest/command/target_link_libraries.html : "The
# named <target> must have been created by a command such as add_executable()"
include(linkToBSDsockets.cmake)
