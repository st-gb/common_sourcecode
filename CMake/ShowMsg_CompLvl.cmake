set(g_lvl 4)#Set this to the desired log level

#see https://stackoverflow.com/questions/5248749/passing-a-list-to-a-cmake-macro :
#Quote the list variable when calling this functions else only the 1st element
#is handled.
function(show1ItmPerLne lvl msg lst)
 if(DEFINED DEBUG_showMsg)
  message("whole list: ${lst}")
  #https://stackoverflow.com/questions/5272781/what-is-common-way-to-split-string-into-list-with-cmake?rq=1
  list(LENGTH lst numItems)
  message("# items: ${numItems}")
  message("show1ItmPerLne lvl: ${lvl} ${g_lvl}")
 endif()
  if(${lvl} GREATER ${g_lvl})
    message("${msg}")
    #see https://stackoverflow.com/questions/6902149/listing-include-directories-in-cmake
    foreach(item ${lst})
	  message(STATUS "item='${item}'")
    endforeach()
  endif()
endfunction()

#This function exists because the "VERBOSE" etc. levels are available from
#CMake version 3.15 on 
#(https://cmake.org/cmake/help/v3.15/command/message.html)
function(showMsg lvl msg)
  if(DEFINED DEBUG_showMsg)
    message("lvl: ${lvl} ${g_lvl}")
  endif()
  if(${lvl} GREATER ${g_lvl})
    message("${msg}")
  endif()
endfunction()

function(showInclDirs lvl)
 if(${lvl} GREATER ${g_lvl})
  #from
  #https://stackoverflow.com/questions/6902149/listing-include-directories-in-cmake
  get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
  foreach(dir ${dirs})
    message(STATUS "incl.dir='${dir}'")
  endforeach()
 endif()
endfunction()