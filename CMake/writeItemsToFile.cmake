#see https://stackoverflow.com/questions/5248749/passing-a-list-to-a-cmake-macro :
#Double quote (") the list variable when calling this functions else only the
#1st element is passed.
function(write1ItemPerLneToFile filePath list)
 file(WRITE ${filePath} "")#Empty file/set file size to 0.
 #if debug
  #message("list:" ${list})
 #endif
 #https://cmake.org/cmake/help/v3.0/command/foreach.html
 foreach(listEle ${list})
  #see https://cmake.org/cmake/help/v3.0/command/file.html
  file(APPEND ${filePath} ${listEle} "\n")
 endforeach()
endfunction()
