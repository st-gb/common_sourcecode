##(c)starting from 2022 by Stefan Gebauer(TU Berlin matriculation number 361095)
##@author Stefan Gebauer(Computer Science Master from TU Berlin)

##Place this file in a directory called ~"character string" because it is not
## restricted to file names.
##Call this file "suffix[...]" because it is the (only) unambiguous/non-homonym/
## non-equivocal verb for "add at end".

##Setting the file name within this function ensures it is not changed (via
## another "set(...)" after including _this_ file.
set(currFlNm "suffixCMakeBuildType.cmake")

function(printStrToSuffix str)
  message("${currFlNm}--character string to suffix:\""
    ##If the actual variable NAME (not within "${" and "}}") is passed to this
    ## function when calling this function then dereferencing the formal
    ## parameter TWICE via "${${" and "}}" gives the VALUE of the actual
    ## parameter.
    "${${str}}"
    "\" from variable named \""
    ##If the actual variable NAME (not within "${" and "}}") is passed to this
    ## function when calling this function then dereferencing the formal
    ## parameter ONCE via "${" and "}}" gives the NAME of the actual
    ## parameter.
    "${str}\"")
endfunction()

##A macro does not add a new scope, so no "PARENT_SCOPE" is needed for the "set"
## function.
macro(suffixCMakeBuildType str)
  set(##"${">>formal parameter name<<"}":the actual parameter NAME if only the
    ## actual parameter name (without any "${" and "}") is passed to this
    ## function.
    ${str}
    #str
    ##"${${">>formal parameter name<<"}}":the actual parameter VALUE if
    ## only the actual parameter name (without any "${" and "}") is passed to
    ## this function.
    ${${str}}_${CMAKE_BUILD_TYPE}
    #${str}_${CMAKE_BUILD_TYPE}
    )
endmacro()

##http://cmake.org/cmake/help/latest/command/function.html
#function(
##A macro does not add a new scope, so no "PARENT_SCOPE" is needed for the "set"
## function.
macro(
##Call this file "suffix[...]" because it is the (only) unambiguous/non-homonym/
## non-equivocal verb for "add at end".
  TU_Bln361095suffixCMakeBuildType
##see https://stackoverflow.com/questions/53278571/cmake-howto-modify-a-variable-from-inside-a-function :
##Callers must pass variable name (without "${" and "}") of the variable to
## change, else its value is not changed outside of this function.
  str
  )

  if(${TU_Bln361095logLvl} GREATER 0)
    message("${currFlNm}--CMAKE_BUILD_TYPE:\"${CMAKE_BUILD_TYPE}\"")
    printStrToSuffix(${str})
  endif()

  ##Only add "_" to file name if "CMAKE_BUILD_TYPE" is set/defined.
  ##http://cmake.org/cmake/help/latest/variable/CMAKE_BUILD_TYPE.html
  if(#DEFINED
     NOT ${CMAKE_BUILD_TYPE} STREQUAL "")##Avoid unnecessary "_" in file name
    if(${TU_Bln361095logLvl} GREATER 0)
      message("${currFlNm}--CMAKE_BUILD_TYPE is set")
    endif()

    suffixCMakeBuildType(${str})
    if(${TU_Bln361095logLvl} GREATER 0)
      message("${currFlNm}--new file name:\""
        ##"${${">>formal parameter name<<"}}":the actual parameter VALUE if only
        ## the actual parameter name (without any "${" and "}") is passed to
        ## this function.
        "${${str}}\"")
    endif()
  else()
    if(${TU_Bln361095logLvl} GREATER 0)
      message("${currFlNm}--CMAKE_BUILD_TYPE is not set")
    endif()
  endif()
  if(${TU_Bln361095logLvl} GREATER 0)
##http://en.wikipedia.org/wiki/Parameter_(computer_programming)#Parameters_and_arguments
## for "actual parameter"
  #message("${currFlNm} actual param. name:\"${str}\" actual param. value:"
  #  "\"${${str}}\"")
  endif()
#endfunction()
endmacro()
