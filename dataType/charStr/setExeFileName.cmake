##(c)2022 Stefan Gebauer,Computer Science Master,TU Berlin matricul. no. 361095

##http://cmake.org/cmake/help/latest/variable/CMAKE_CURRENT_LIST_DIR.html
##"Full directory of the listfile currently being processed."
include(${CMAKE_CURRENT_LIST_DIR}/suffixCMakeBuildType.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/suffixExeFileExt.cmake)

##Use function rather than macro because it has an own scope and so "currFlNm"
## does not influence other (outer) scopes.
function(setExeFileName
  exeFileName##Call with "${" "}" around variable name
  dbgLvl)
 ##Setting the file name within this function ensures it is not changed (via
 ## another "set(...)" after including _this_ file.
 set(currFlNm "setExeFileName.cmake"
##If set _inside_ this function, it gets the (full) file system path of
## "CMakeLists.txt" and not the path of _this_ file.
  #${CMAKE_CURRENT_LIST_FILE}
   )
 if(dbgLvl GREATER 0)
   message("${currFlNm} exeFileName:${exeFileName}")
 endif()
 suffixCMakeBuildType(${exeFileName} ${dbgLvl})
 #For filtering by ".elf" or ".exe" in file ".gitignore"
 suffixExeFileExt(exeFileName)
 if(dbgLvl GREATER 0)
   message("${currFlNm} exeFileName:${exeFileName}")
 endif()
 set(exeFileName ${exeFileName} PARENT_SCOPE)
endfunction()
