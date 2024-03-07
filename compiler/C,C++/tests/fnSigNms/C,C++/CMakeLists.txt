##(c) from 2024 by Stefan Gebauer(Computer Science Master from TU Berlin)
##@author Stefan Gebauer(TU Berlin matriculation number 361095)

##from https://cmake.org/cmake-tutorial/
cmake_minimum_required (VERSION 2.8)
project(fnSigNmsTest)##FuNction SIGnature NaMeS TEST

if(NOT DEFINED cmnSrcRootDir)
  set(cmnSrcRootDir "${PROJECT_SOURCE_DIR}/../../../../../")
  include(${cmnSrcRootDir}FileSystem/setAndResolveFileSysDir.cmake)
  setAndResolveFileSysDir(cmnSrcRootDir ${cmnSrcRootDir} 0)
  message("set \"cmnSrcRootDir\" to \"${cmnSrcRootDir}\"")
endif()

##Passed to CMake as command line argument via "-D[...]"
if(DEFINED oneCmdLneArgForFn)
  message("\"oneCmdLneArgForFn\" defined")
## http://cmake.org/cmake/help/latest/prop_dir/COMPILE_DEFINITIONS.html :
	set(COMPILE_DEFINITIONS
	  ${COMPILE_DEFINITIONS}
	  -DoneCmdLneArgForFn
	)
endif()

if(DEFINED showIncludeHierarchy)
  include(${cmnSrcRootDir}compiler/C,C++/printInclFiles.cmake)
endif()

#add_compile_definitions(${COMPILE_DEFINITIONS})

#see http://stackoverflow.com/questions/8934295/add-source-in-a-subdirectory-to-a-cmake-project
set(srcFlPaths
  ${srcFlPaths}
  ${PROJECT_SOURCE_DIR}/fnSigNmsTestMain.c#pp
)

set(inclDirs
  ${inclDirs}
  ${cmnSrcRootDir}
)

include_directories(${inclDirs})

add_executable(${PROJECT_NAME} ${srcFlPaths})

target_compile_definitions(${PROJECT_NAME} PRIVATE ${COMPILE_DEFINITIONS})
get_target_property(compileDefs ${PROJECT_NAME} COMPILE_DEFINITIONS)
if(DEFINED COMPILE_DEFINITIONS)
  message("${PROJECT_NAME}'s \"COMPILE_DEFINITIONS\":\"${compileDefs}\"")
else()
  message("${PROJECT_NAME}'s \"COMPILE_DEFINITIONS\" not set")
endif()