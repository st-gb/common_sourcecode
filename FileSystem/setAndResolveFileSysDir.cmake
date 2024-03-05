##(c) Stefan Gebauer,Computer Science Master from TU Berlin
## @author Stefan Gebauer(TU Berlin matriculation number 361095)

##@brief Sets a file system path for \p varName and resolves it afterwards.
function(setAndResolveFileSysDir varName defaultPath log)
if(DEFINED ${varName})# AND ${varName} NOT STREQUAL "")
  if(${log} GREATER 0)
    message("\"${varName}\" defined for CMake:\"${${varName}}\"")
  endif()
else()
  if(${log} GREATER 0)
    message("\"${varName}\" not defined for CMake->using default path \"\
${defaultPath}\"")
  endif()
  set(${varName} ${defaultPath} PARENT_SCOPE)
endif()
set(resolvedDir ${defaultPath})

##http://cmake.org/cmake/help/latest/command/get_filename_component.html :
##-"get_filename_component(<var> <FileName> <mode> [BASE_DIR <dir>] [CACHE])"
## New in version 3.4.
## Sets <var> to the absolute path of <FileName>, where <mode> is one of:"
##-"REALPATH  = Full path to existing file with symlinks resolved"
if(${CMAKE_VERSION} VERSION_GREATER_EQUAL 3.4)
##<=>Get away/resolve ".." etc. in file system path.
  get_filename_component(resolvedDir "${resolvedDir}" REALPATH)
else()
##<=>Get away/resolve ".." etc. in file system path.
  get_filename_component(resolvedDir "${resolvedDir}" ABSOLUTE)
endif()

## http://cmake.org/cmake/help/latest/command/set.html :
## "PARENT_SCOPE" to propagate changes to the caller of this function.
set(${varName} ${resolvedDir} PARENT_SCOPE)
endfunction()