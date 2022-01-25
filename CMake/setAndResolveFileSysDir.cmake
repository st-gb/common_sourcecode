#Sets a file system path for @varName and resolves it afterwards.
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
#Get away/resolve ".." etc. in file system path.
get_filename_component(resolvedDir "${resolvedDir}" ABSOLUTE)
#"PARENT_SCOPE" to propagate changes to the caller of this function.
set(${varName} ${resolvedDir} PARENT_SCOPE)
endfunction()