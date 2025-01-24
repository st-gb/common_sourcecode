##(c)from 2024 Stefan Gebauer,Computer Science Master(TU Berlin matr.no.361095)
## @author Stefan Gebauer(TU Berlin matriculation number 361095)

##TU_Bln361095printList1ItemPerLine(...)
include(${cmnSrcDir}/CMake/printList1ItemPerLine.cmake)

##@param inclDirsVarNm the variable name of the list of items/character string
## that the boost root file system directory is added to
##@param inclDirs the list of items/character string that the boost root file
## system directory is added to
function(TU_Bln361095testUseBoostMultiPrecisionArithmLib #inclDirsVar
  inclDirs cppLibBoostRootDir)

  ## http://cmake.org/cmake/help/latest/variable/CMAKE_CURRENT_FUNCTION.html :
  ## "CMAKE_CURRENT_FUNCTION" needs at least CMake version "3.17"
  if(CMAKE_VERSION GREATER 3.17)
    set(currFnNm  ${CMAKE_CURRENT_FUNCTION})
  else()
    set(currFnNm TU_Bln361095testUseBoostMultiPrecisionArithmLib)
  endif()

  #message("BoostMultiPrecisionArithmLibRootDir:${BoostMultiPrecisionArithmLibRootDir}")
  #set(inclDirs ${inclDirs} #${BoostMultiPrecisionArithmLibRootDir}
  #  D:/Boost1.81.0/boost_1_81_0/)
  if(#DEFINED
    NOT ##${BoostMultiPrecisionArithmLibRootDir}<
     ${cppLibBoostRootDir} STREQUAL ""
    )
    #message("inclDirsVar: \"${inclDirsVar}\" \"${${inclDirsVar}}\"")
    message("${currFnNm}--inclDirs: \"${inclDirs}\"")
    set(
      #${inclDirsVarNm}
      #${${inclDirsVarNm}}
      inclDirs
      ${inclDirs}
      #${BoostMultiPrecisionArithmLibRootDir}
      ${cppLibBoostRootDir}
      ##To propagate variable value changes to the caller of this function.
      PARENT_SCOPE
    )
    message("${currFnNm}--\"Boost\" root directory:"
      "${cppLibBoostRootDir}")
    ##http://cmake.org/cmake/help/latest/command/add_compile_definitions.html
    add_compile_definitions(useBoostMultiPrecisionArithmLib)
  else()
    message("${currFnNm}--cppLibBoostRootDir is not defined")
  endif()
  #message("${currFnNm} end--incl dirs: ${inclDirsVar}")
  ##Can't use the character string directly as parameter. So store it in a
  ## variable.
  #set(msg "${currFnNm} end--content of \"inclDirs\" variable:")
  #TU_Bln361095printList1ItemPerLine(${msg} "${inclDirs}")

endfunction()