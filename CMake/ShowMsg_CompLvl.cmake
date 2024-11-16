set(g_lvl 4)#Set this to the desired log level

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
