##(c) from 2024 Stefan Gebauer,Computer Science Master(TU Berlin matr.no.361095)
## @author Stefan Gebauer(TU Berlin matriculation number 361095)

## @brief can be defined on CMake command line (via "-D")
if(NOT DEFINED TU_Bln361095logLvl)
  set(TU_Bln361095logLvl 4)#Set this to the desired log level
endif()

##see https://stackoverflow.com/questions/5248749/passing-a-list-to-a-cmake-macro :
##Quote (") the list variable when calling this functions else only the 1st
## element is handled.
##@param msg Can be the name of the calling function/file for example.
##@lst list to print/output
function(TU_Bln361095printList1ItemPerLine msg lst)
  if(${TU_Bln361095logLvl} GREATER 0)
    message("${msg}--whole list:\"${lst}\"")
    #https://stackoverflow.com/questions/5272781/what-is-common-way-to-split-string-into-list-with-cmake?rq=1
    list(LENGTH lst numItems)
    message("${msg}--# list items: ${numItems}")
  endif()
  #see https://stackoverflow.com/questions/6902149/listing-include-directories-in-cmake
  foreach(item ${lst})
    message(STATUS "${msg}--item='${item}'")
  endforeach()
endfunction()