#Add C++ 11 support because g++ compiler output:
#"In file included from /usr/include/c++/5/unordered_map:35:0,
#  from [..]/cxxopts-master/include/cxxopts.hpp:38,
# [...]
#/usr/include/c++/5/bits/c++0x_warning.h:32:2: error: #error This file requires
# compiler and library support for the ISO C++ 2011 standard. This support must
# be enabled with the -std=c++11 or -std=gnu++11 compiler options."
#http://cmake.org/cmake/help/latest/variable/CMAKE_CURRENT_LIST_DIR.html :
# "Full directory of the listfile currently being processed."
include(${CMAKE_CURRENT_LIST_DIR}/../../CMake/useCpp11.cmake)
useCxx11(${exeFileName})