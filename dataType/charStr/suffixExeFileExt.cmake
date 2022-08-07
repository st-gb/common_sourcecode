##(c)2022 Stefan Gebauer,Computer Science Master(TU Berlin matricul. no. 361095)
##Place this file in a directory called ~"character string" because it is not
## restricted to file names.
##Call this file "suffix[...]" because it is the (only) unambiguous/non-homonym/
## non-equivocal verb for "add at end".

##http://cmake.org/cmake/help/latest/command/function.html :"A function opens a
## new scope"
#function(
##Call this function "suffix[...]" because it is the (only) unambiguous/non-
## homonym/non-equivocal verb for "add at end".
#  suffixExeFileExt filePath)#Callers pass variable name without "${" "}"
macro(suffixExeFileExt charStr)
 if(UNIX)
  #http://stackoverflow.com/questions/22487215/cmake-function-parameter-and-return
  #http://stackoverflow.com/questions/14375519/how-to-write-a-nice-function-that-passes-variables-by-reference
  ##For filtering by ".elf" in file ".gitignore"
  set(${charStr}##"${"[...]"}" to get variable name
    ##"${${"[...]"}}" to get variable value
    ${${charStr}}.elf
## http://cmake.org/cmake/help/latest/command/set.html#command:set :
##"If the PARENT_SCOPE option is given the variable will be set in the scope
## above the current scope."
    #PARENT_SCOPE##To set to scope outside of function
    )
 else()
##In Microsoft Windows,".exe" is automatically suffixed.
  #http://cmake.org/cmake/help/v3.0/variable/CMAKE_EXECUTABLE_SUFFIX.html
  #set(${charStr} "${${charStr}}.${CMAKE_EXECUTABLE_SUFFIX}")
 endif()
#endfunction()
endmacro()
