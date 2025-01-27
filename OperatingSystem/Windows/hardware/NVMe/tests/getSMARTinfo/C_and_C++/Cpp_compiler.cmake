##(c)from 2024 Stefan Gebauer,Computer Science Master(TU Berlin matr.no.361095)
## @author Stefan Gebauer(TU Berlin matriculation number 361095)

function(testUseCpp_compiler inclDirs srcFilePaths
  NVMeReadSMARTattrValTestRootDir boostRootDir cxxoptsDir
  )
  ## http://cmake.org/cmake/help/latest/variable/CMAKE_CURRENT_FUNCTION.html :
  ## "CMAKE_CURRENT_FUNCTION" needs at least CMake version "3.17"
  if(CMAKE_VERSION GREATER 3.17)
    set(currFnNm  ${CMAKE_CURRENT_FUNCTION})
  else()
    set(currFnNm "testUseCpp_compiler")
  endif()

  #message("${currCMakeListsFilePath}--Test if GNU C compiler failed--testing with C++")
  ##http://cmake.org/cmake/help/latest/variable/CMAKE_LANG_COMPILER_ID.html :
  if(NOT ${CMAKE_CXX_COMPILER_ID} STREQUAL "")##<=> C++ compiler present
    message("${currFilePath}--CMAKE_CXX_COMPILER_ID:"
      "\"${CMAKE_CXX_COMPILER_ID}\"")

    set(mainSrcFlPath
      ${NVMeReadSMARTattrValTestRootDir}/C_and_C++/readNVMeSMARTattrVals_main.cpp)
    TU_Bln361095setAndResolveFileSysPath(reslvedMainSrcFlPath ${mainSrcFlPath} )
    set(srcFilePaths
      ${srcFilePaths}
      ${reslvedMainSrcFlPath}
      PARENT_SCOPE
      )

    include(${cmnSrcDir}/dataType/bigUint/testUseBoostMultiPrecisionArithmLib.cmake)
    ##Pass variable name because its contents should be changed inside the
    ## function.
    TU_Bln361095testUseBoostMultiPrecisionArithmLib(#"inclDirs"
      ${inclDirs} ${boostRootDir})
  endif()

  if(NOT ${CMAKE_CXX_COMPILER_ID} STREQUAL "" ##<=>C++ compiler
    AND NOT ${cxxoptsDir} STREQUAL "")
    message("cxxoptsDir:${cxxoptsDir}")
    ##http://cmake.org/cmake/help/latest/command/add_compile_definitions.html :
    ## 
    add_compile_definitions(cxxoptsDir=${cxxoptsDir})
    ##Set the variable contents again without "PARENT_SCOPE", else outputting 
    ## its values does not show changes.
    set(inclDirs ${inclDirs} ${cxxoptsDir})
  endif()
  message("${currFnNm} end:include directories:${inclDirs}")
  ##Set the variable contents again with "PARENT_SCOPE" to propagate its
  ## changes to the caller of this function.
  set(inclDirs ${inclDirs} PARENT_SCOPE)
endfunction()