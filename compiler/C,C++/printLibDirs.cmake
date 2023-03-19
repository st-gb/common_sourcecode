set(TU_Bln361095logLvl 4)##Set this to the desired log level

##Lib=LIBrary: http://www.abbreviations.com/abbreviation/Library
##Dirs:DIRectorieS: http://www.abbreviations.com/abbreviation/directories
function(printLibDirs logLvl)
 if(${logLvl} GREATER ${TU_Bln361095logLvl})
  get_property(dirs DIRECTORY PROPERTY
  ##http://cmake.org/cmake/help/latest/prop_dir/LINK_DIRECTORIES.html :
  ## "List of linker search directories.
  ##
  ## This property holds a semicolon-separated list of directories and is
  ## typically populated using the link_directories() command. It gets its
  ## initial value from its parent directory, if it has one."
    LINK_DIRECTORIES)
  foreach(dir ${dirs})
    message(STATUS "lib.dir='${dir}'")
  endforeach()
 endif()
endfunction()