
#https://cmake.org/cmake/help/v3.5/prop_tgt/CXX_STANDARD.html
#set_property(TARGET PROPERTY ${EXE_NAME} CXX_STANDARD 11)

#https://crascit.com/2015/03/28/enabling-cxx11-in-cmake/
#set_target_properties(${EXE_NAME}
#    PROPERTIES
#        CXX_STANDARD 11
#        CXX_STANDARD_REQUIRED YES
#        CXX_EXTENSIONS NO
#  )

#https://stackoverflow.com/questions/10851247/how-do-i-activate-c-11-in-cmake
macro(use_cxx11)
  if (CMAKE_VERSION VERSION_LESS "3.1")
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
      set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
    endif ()
  else ()
    set (CMAKE_CXX_STANDARD 11)
  endif ()
endmacro()

