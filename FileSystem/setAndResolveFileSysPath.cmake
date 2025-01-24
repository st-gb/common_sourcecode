##(c)beginning from 2022? Stefan Gebauer,TU Berlin matriculation number 361095
## @author Stefan Gebauer(Computer Science Master from TU Berlin)

##@brief can be defined on CMake command line (via "-D")
if(NOT DEFINED TU_Bln361095logLvl)
  set(TU_Bln361095logLvl 0)##Set this to the desired log level
endif()

##@brief Sets a file system path for \p varName and resolves it afterwards.
## It can be a directory or file path
##@param defaultPath file system path to use if \p varName is not set.
function(TU_Bln361095setAndResolveFileSysPath varName defaultPath# logLvl
  )
  if(DEFINED ${varName})# AND ${varName} NOT STREQUAL "")
    if(${TU_Bln361095logLvl} GREATER 0)
      message("\"${varName}\" defined for CMake:\"${${varName}}\"")
    endif()
  else()
    if(${TU_Bln361095logLvl} GREATER 0)
      message("\"${varName}\" not defined for CMake->using default path \""
        "${defaultPath}\"")
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