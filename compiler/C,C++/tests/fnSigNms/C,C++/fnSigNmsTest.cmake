##(c) from 2024 by Stefan Gebauer(Computer Science Master from TU Berlin)
##@author Stefan Gebauer(TU Berlin matriculation number 361095)

if(NOT DEFINED cmnSrcRootDir)
  set(cmnSrcRootDir "${PROJECT_SOURCE_DIR}/../../../../..")
  include(${cmnSrcRootDir}/FileSystem/setAndResolveFileSysDir.cmake)
  setAndResolveFileSysDir(cmnSrcRootDir ${cmnSrcRootDir} 0)
  message("set \"cmnSrcRootDir\" to \"${cmnSrcRootDir}\"")
endif()

if(DEFINED CMAKE_C_COMPILER_ID)
  set(COMPILE_DEFINITIONS
    ${COMPILE_DEFINITIONS}
    -DC_compiler=${CMAKE_C_COMPILER_ID}
    )
endif()
if(DEFINED CMAKE_CXX_COMPILER_ID)
  set(COMPILE_DEFINITIONS
    ${COMPILE_DEFINITIONS}
    -DCppCompiler=${CMAKE_CXX_COMPILER_ID}
    )
endif()
if(DEFINED CMAKE_C_COMPILER_VERSION)
  set(COMPILE_DEFINITIONS
    ${COMPILE_DEFINITIONS}
    -DC_compilerVersion=${CMAKE_C_COMPILER_VERSION}
    )
endif()
if(DEFINED CMAKE_CXX_COMPILER_VERSION)
  set(COMPILE_DEFINITIONS
    ${COMPILE_DEFINITIONS}
    -DCppCompilerVersion=${CMAKE_CXX_COMPILER_VERSION}
    )
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
  include(${cmnSrcRootDir}/compiler/C,C++/printInclFiles.cmake)
endif()

#add_compile_definitions(${COMPILE_DEFINITIONS})

set(inclDirs
  ${inclDirs}
  ${cmnSrcRootDir}
)

include_directories(${inclDirs})

add_executable(${PROJECT_NAME} ${srcFlPaths})

target_compile_definitions(${PROJECT_NAME} PRIVATE ${COMPILE_DEFINITIONS})
get_target_property(compileDefs ${PROJECT_NAME} COMPILE_DEFINITIONS)
if(DEFINED COMPILE_DEFINITIONS)
  include(${cmnSrcRootDir}/CMake/ShowMsg_CompLvl.cmake)
  show1ItmPerLne(5 "${PROJECT_NAME}'s \"COMPILE_DEFINITIONS\":" "${compileDefs}"
    )
else()
  message("${PROJECT_NAME}'s \"COMPILE_DEFINITIONS\" not set")
endif()