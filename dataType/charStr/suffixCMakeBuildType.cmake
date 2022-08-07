##(c)2022 Stefan Gebauer,Computer Science Master,TU Berlin matriculation #361095
##Place this file in a directory called ~"character string" because it is not
## restricted to file names.
##Call this file "suffix[...]" because it is the (only) unambiguous/non-homonym/
## non-equivocal verb for "add at end".

##http://cmake.org/cmake/help/latest/command/function.html
function(
##Call this file "suffix[...]" because it is the (only) unambiguous/non-homonym/
## non-equivocal verb for "add at end".
  suffixCMakeBuildType
##Callers pass variable name (without "${" "}"), else its value is not changed.
  str
  debugLevel
)
 ##Setting the file name within this function ensures it is not changed (via
 ## another "set(...)" after including _this_ file.
 set(currFlNm "suffixCMakeBuildType.cmake")

 if(debugLevel GREATER 0)
  message("${currFlNm} CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
  message("${currFlNm} str: ${str}")
 endif()

##Only add "_" to file name if "CMAKE_BUILD_TYPE" is set/defined.
##http://cmake.org/cmake/help/latest/variable/CMAKE_BUILD_TYPE.html
 if(#DEFINED
  NOT ${CMAKE_BUILD_TYPE} STREQUAL "")#Avoid unnecessary "_" in file name
  if(debugLevel GREATER 0)
   message("${currFlNm} CMAKE_BUILD_TYPE is set")
  endif()

  set(${str}##"${" "}":actual parameter (name)
   ##"${${" "}}":actual parameter value
   ${${str}}_${CMAKE_BUILD_TYPE}
   ##http://cmake.org/cmake/help/latest/command/set.html :
   ##"PARENT_SCOPE" to affect actual parameters to caller of this function.
   PARENT_SCOPE)
 endif()
 if(debugLevel GREATER 0)
##http://en.wikipedia.org/wiki/Parameter_(computer_programming)#Parameters_and_arguments
## for "actual parameter"
  message("${currFlNm} actual param. name:${str} actual param. value:${${str}}")
 endif()
endfunction()
