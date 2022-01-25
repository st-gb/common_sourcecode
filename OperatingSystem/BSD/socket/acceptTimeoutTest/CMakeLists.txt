project(acceptTimeoutTest)

cmake_minimum_required(VERSION 2.10)#TODO really min. ver.?

if(DEFINED cmnSrcDir)
  message("\"cmnSrcDir\" defined for CMake:\"${cmnSrcDir}\"")
else()
  #For "include_directories(...)" and "include(...)"
  set(cmnSrcDir ../../../..)
  message("\"cmnSrcDir\" not defined for CMake->using default path")
endif()
#Get away/resolve ".." (etc.) in file path.
get_filename_component(cmnSrcDir "${cmnSrcDir}" ABSOLUTE)

include(${cmnSrcDir}/CMake/SGR_terminalColours.cmake)
message("(Resolved) ${SGR_Magenta}cmnSrcDir:\"${SGR_ColourReset}${cmnSrcDir}\
${SGR_Magenta}\"${SGR_ColourReset}")

if(DEFINED cxxoptsDir)
  message("\"cxxoptsDir\" defined for CMake:\"${cxxoptsDir}\"")
else()
  #For "include_directories(...)"
  set(cxxoptsDir "${cmnSrcDir}/../../cxxopts-master/include")
  message("cxxoptsDir not defined for CMake->using default path")
endif()
#Get away/resolve ".." (etc.) in file path.
get_filename_component(cxxoptsDir "${cxxoptsDir}" ABSOLUTE)
message("${SGR_Magenta}cxxoptsDir${SGR_ColourReset}:\"${cxxoptsDir}\"")

include_directories(${cmnSrcDir} ${cxxoptsDir})

set(srcFilePaths
  acceptTimeoutTest.cpp
  ../initSrv.cpp
  ../prepAccept.cpp
  )

set(exeFileName ${PROJECT_NAME}_${CMAKE_BUILD_TYPE})
include(${cmnSrcDir}/CMake/ShowMsg_CompLvl.cmake)
showInclDirs(5)

include(${cmnSrcDir}/CMake/addExeFileExt.cmake)
#For filtering by ".elf" or ".exe" in file ".gitignore"
addExeFileExt(exeFileName)

add_executable(${exeFileName} ${srcFilePaths})
include(${cmnSrcDir}/libraries/cxxopts/addCompileOptions.cmake)

#Link to accept(...),bind(...),htons(...),listen(...),inet_ntoa(...),socket(...)
include(linkToBSDsockFns.cmake)
