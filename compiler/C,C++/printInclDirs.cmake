##(c) from 2024 Stefan Gebauer,Computer Science Master(TU Berlin matr.no.361095)
## @author Stefan Gebauer(TU Berlin matriculation number 361095)

## @brief can be defined on CMake command line (via "-D")
if(NOT DEFINED TU_Bln361095logLvl)
  set(TU_Bln361095logLvl 4)#Set this to the desired log level
endif()

##Cmpl=CoMPiLer
##Incl=INCLude: http://www.abbreviations.com/abbreviation/include
##Dirs:DIRectorieS: http://www.abbreviations.com/abbreviation/directories
##@param msg is used in messages. This can be used to show where the call came
## from by passing function or file names.
function(TU_Bln361095printCmplrInclDirs msg)
##from
##http://stackoverflow.com/questions/6902149/listing-include-directories-in-cmake
  get_property(cmplInclDirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY
##http://cmake.org/cmake/help/latest/prop_dir/INCLUDE_DIRECTORIES.html#prop_dir:INCLUDE_DIRECTORIES
## "List of preprocessor include file search directories.
## 
## This property specifies the list of directories given so far to the
## include_directories() command."
    INCLUDE_DIRECTORIES)
  if(${TU_Bln361095logLvl} GREATER 0)
    message("${msg}--all include directories:\"${cmplInclDirs}\"")
  endif()
  foreach(cmplInclDir ${cmplInclDirs})
    message(#STATUS
      "${msg}--INCLUDE_DIRECTORIES item='${cmplInclDir}'")
  endforeach()
endfunction()