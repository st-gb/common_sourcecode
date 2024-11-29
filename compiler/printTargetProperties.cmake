##(c) from 2024 Stefan Gebauer,Computer Science Master(TU Berlin matr.no.361095)
## @author Stefan Gebauer(TU Berlin matriculation number 361095)

##-Place this file into "compiler" root file system directory and not into its
## "C/C++" subdirectory because these compiler properties may also exist in
## other programming languages.
##-include "target" in file system name for this file because by using the 
## "get_target_property(...)" function the properties are related to a target
## (and for example not to a file system directory).

##@param trgtName target name for getting the list of preprocessor definitions
## for
##@param msgPrfx character string to print in front of the preprocessor
## definitions for/to build target \p trgtName
function(TU_Bln361095cmplrPrintTargetPreprocDefs trgtName msgPrfx)
  ##http://cmake.org/cmake/help/latest/command/get_target_property.html
  get_target_property(trgtPreprocDefs ${trgtName}
    ##http://cmake.org/cmake/help/latest/prop_dir/COMPILE_DEFINITIONS.html :
    ## "Preprocessor definitions for compiling a directory's sources."
    COMPILE_DEFINITIONS)
  message("${msgPrfx}--CMake's COMPILE_DEFINITIONS(preprocessor definitions) "
    "for target \"${trgtName}\":\"${trgtCmplDefs}\"")
endfunction()

##@param trgtName target name for getting the list of source file paths for
##@param msgPrfx character string to print in front of the source files' file
## system paths for/to build target \p trgtName
function(TU_Bln361095cmplrPrintTargetSrcFiles trgtName msgPrfx)
  ##http://cmake.org/cmake/help/latest/command/get_target_property.html
  get_target_property(trgtSrcFiles ${trgtName}
    ##http://cmake.org/cmake/help/latest/prop_tgt/SOURCES.html :
    ## [..]"the list of paths to source files for the target"[..]
    SOURCES)
  message("${msgPrfx}--CMake's file systems paths for source files for target "
    "\"${trgtName}\":\"${trgtSrcFiles}\"")
endfunction()