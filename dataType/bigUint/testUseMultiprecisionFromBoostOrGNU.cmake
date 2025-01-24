##(c)from 2024 Stefan Gebauer,Computer Science Master(TU Berlin matr.no.361095)
## @author Stefan Gebauer(TU Berlin matriculation number 361095)

message("CMAKE_CXX_COMPILER_ID: ${CMAKE_CXX_COMPILER_ID}")

function(TU_Bln361095testUseMultiprecisionFromBoostOrGNU inclDirs)
  ##http://cmake.org/cmake/help/latest/variable/CMAKE_LANG_COMPILER_ID.html :
  ## "MSVC"
  ##https://stackoverflow.com/questions/10046114/in-cmake-how-can-i-test-if-the-compiler-is-clang
  #if(${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
  if(${CMAKE_CXX_COMPILER_ID} STREQUAL "")##<=> C++ compiler NOT present
  ##https://stackoverflow.com/questions/10046114/in-cmake-how-can-i-test-if-the-compiler-is-clang
    if(${CMAKE_C_COMPILER_ID} STREQUAL "GNU")##TODO test: also "clang"??
      include(${cmnSrcDir}/dataType/bigUint/testUseGNUmultiPrecisionArithmLib.cmake)
      ##Pass variable name because its contents should be changed inside the function.
      TU_Bln361095testUseGNUmultiPrecisionArithmLib("inclDirs")
    endif()
  else()##<=>C++ compiler name is present<=>compiling with C++ compiler
    message(#"CMAKE_CXX_COMPILER_ID=MSVC"
      "C++ compiler present")

    include(${cmnSrcDir}/dataType/bigUint/testUseBoostMultiPrecisionArithmLib.cmake)
    ##Pass variable name because its contents should be changed inside the function.
    TU_Bln361095testUseBoostMultiPrecisionArithmLib("inclDirs")
  endif()
endfunction()