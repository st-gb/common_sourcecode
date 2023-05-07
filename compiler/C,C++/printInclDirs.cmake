set(TU_Bln361095logLvl 4)#Set this to the desired log level

##Incl=INCLude: http://www.abbreviations.com/abbreviation/include
##Dirs:DIRectorieS: http://www.abbreviations.com/abbreviation/directories
function(printInclDirs logLvl)
 if(${logLvl} GREATER ${TU_Bln361095logLvl})
##from
##http://stackoverflow.com/questions/6902149/listing-include-directories-in-cmake
  get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY
##http://cmake.org/cmake/help/latest/prop_dir/INCLUDE_DIRECTORIES.html#prop_dir:INCLUDE_DIRECTORIES
## "List of preprocessor include file search directories.
## 
## This property specifies the list of directories given so far to the
## include_directories() command."
    INCLUDE_DIRECTORIES)
  foreach(dir ${dirs})
    message(STATUS "incl.dir='${dir}'")
  endforeach()
 endif()
endfunction()