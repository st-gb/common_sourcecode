function(addExeFileExt filePath)#Callers pass variable name without "${" "}"
#macro(addExeFileExt filePath)
if(UNIX)
  #http://stackoverflow.com/questions/22487215/cmake-function-parameter-and-return
  #http://stackoverflow.com/questions/14375519/how-to-write-a-nice-function-that-passes-variables-by-reference
  #For filtering by ".elf" in file ".gitignore"
  set(${filePath} ${${filePath}}.elf PARENT_SCOPE)
else()
  #http://cmake.org/cmake/help/v3.0/variable/CMAKE_EXECUTABLE_SUFFIX.html
  #set(EXE_NAME "${EXE_NAME}.${CMAKE_EXECUTABLE_SUFFIX}")
endif()
endfunction()
#endmacro()
