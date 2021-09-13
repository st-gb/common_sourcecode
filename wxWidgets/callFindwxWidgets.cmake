#This script helps to debug calling "find_package(wxWidgets ...)"

include(${cmnSrcDir}/CMake/SGR_terminalColours.cmake)#SGR_Cyan,SGR_ColourReset

#For "FindwxWidgets.cmake" these variables may be set 
# (see top of "FindwxWidgets.cmake" or 
#  https://cmake.org/cmake/help/v3.0/module/FindwxWidgets.html):
# -wxWidgets_ROOT_DIR : Base wxWidgets directory (e.g., C:/wxWidgets-2.6.3)
# -wxWidgets_LIB_DIR : Path to wxWidgets libraries (e.g., 
#  C:/wxWidgets-2.6.3/lib/vc_lib)
# -wxWidgets_CONFIGURATION : Configuration to use (e.g., msw, mswd, mswu, 
#  mswunivud, etc.)

#in "FindwxWidgets.cmake":
# "if(WIN32 AND NOT CYGWIN AND NOT MSYS AND NOT CMAKE_CROSSCOMPILING)
#  set(wxWidgets_FIND_STYLE "win32")"

#wxWidgets_FIND_STYLE "win32" & "MinGW Makefiles" build system generator :
# it sets wxWidgets_LIB_DIR to either:
#  -"${WX_ROOT_DIR}/lib/gcc_dll"
#  -"${WX_ROOT_DIR}/lib/gcc_lib"

#for "MSYS Makefiles" build system generator?:
#-download and install https://github.com/Uskok/wx-config
#-build: E:\wxWidgets\wx-config-master>mingw32-g++
# wx-config.cpp Options.cpp Compiler.cpp -s -o wx-config.exe

#"findwxWidgets.cmake" works as follows:
#For "MSYS Makefiles" generator if uses "unix" style.
# https://stackoverflow.com/questions/18433305/cmake-find-wxwidgets-built-with-mingw-msys
# "So Unix-style tree is assumed for the "MSYS Makefiles" generator (cmake -G 
# "MSYS Makefiles") but not for the "MinGW Makefiles" generator."

#before including this script set at least the "wxWidgets_ROOT_DIR"?!, e.g.:
# SET(wxWidgets_ROOT_DIR "E:/wxWidgets/MSW-3.1.0_gcc510TDM_x64_Dev")

#May also set the wxWidgets_LIB_DIR, e.g.:
#https://cmake.org/cmake/help/v3.1/module/FindwxWidgets.html :
#https://stackoverflow.com/questions/41574177/cmake-findwxwidgets-fails-only-on-first-invocation-of-configure-command
#set( wxWidgets_LIB_DIR "E:/wxWidgets/wxMSW-3.1.1_gcc510TDM_ReleaseDLL/lib/gcc510TDM_dll" CACHE PATH "wxWidgets_LIB_DIR" FORCE)
#set( wxWidgets_LIB_DIR "E:/wxWidgets/wxWidgets-2.8.10/MinGW_unicode_static_debug/lib")
#set(wxWidgets_LIB_DIR "M:/wxWidgets/lib/gcc510TDM_x64_dll"
#  CACHE PATH "wxWidgets_LIB_DIR FORCE")

#TODO make as function with parameter "wxLibs"?! (e.g. set to "core base adv")?
#https://stackoverflow.com/questions/5248749/passing-a-list-to-a-cmake-macro :
#Must double quote (") actual variable for wxLibs to have multiple elements
#function(callFindwxWidgets wxLibs)
  #message(STATUS "wxLibs: ${wxLibs} ${${wxLibs}}")
  if(UNIX)
    #https://wiki.wxwidgets.org/CMake
    set(wxWidgets_CONFIGURATION gtkud)
  endif()
  if(WIN32)
    #set(wxWidgets_FIND_STYLE "win32")
    if(CMAKE_BUILD_TYPE STREQUAL "Release")
      set(wxWidgets_CONFIGURATION mswu)
	endif()
    #message("setting wxWidgets_CONFIGURATION to mswud")
    #msw="MicroSoft Windows" ud="Unicode Debug"
    #set(wxWidgets_CONFIGURATION mswud)
    #https://cmake.org/cmake/help/v3.0/module/FindwxWidgets.html
    #set(wxWidgets_CONFIG_OPTIONS --toolkit=base --prefix=/usr)
  endif()

  #SET(wxWidgets_INCLUDE_DIRS "wxWidgets/include")

  message(wxWidgets_ROOT_DIR: ${wxWidgets_ROOT_DIR})
  message(wxWidgets_LIB_DIR: ${wxWidgets_LIB_DIR})
  
#see https://cmake.org/cmake/help/v3.0/module/FindwxWidgets.html
#"find_package(wxWidgets " may cause error: 
# "CMake Error at C:/Program Files/CMake/share/cmake-3.9/Modules/FindPackageHandleStandardArgs.cmake:137 (message):
#Could NOT find wxWidgets (missing: wxWidgets_LIBRARIES
#wxWidgets_INCLUDE_DIRS)
#Call Stack (most recent call first):
#C:/Program Files/CMake/share/cmake-3.9/Modules/FindPackageHandleStandardArgs.cmake:377 (_FPHSA_FAILURE_MESSAGE)
#C:/Program Files/CMake/share/cmake-3.9/Modules/FindwxWidgets.cmake:953 (find_package_handle_standard_args)"
  
  #SET(wxWidgets_USE_LIBS core base adv)
	
  message("wxWidgets_USE_LIBS: ${wxWidgets_USE_LIBS}")
  message("Before find_package(wxWidgets)")
  if(UNIX)
    message("${SGR_Cyan}NOTE: needs package \"libwxbase<<version>>dev\" installed"
      "${SGR_ColourReset}")
  endif()
  #Calls/includes "findwxWidgets.cmake".
  #TODO make usable with wxLibs
  #find_package(wxWidgets COMPONENTS ${${wxLibs}} REQUIRED)
  #Uses "wxWidgets_USE_LIBS" variable for "COMPONENTS"
  find_package(wxWidgets REQUIRED)
  message("After find_package(wxWidgets")
  
 if(debugCallFindwxWidgets)#only output if certain debug level?
  message("wxWidgets_USE_LIBS: ${wxWidgets_USE_LIBS}")
  #https://cmake.org/cmake/help/v3.0/module/FindwxWidgets.html :
  #"The following are set after the configuration is done for both windows and
  # unix style:"
  message(wxWidgets_FIND_STYLE: ${wxWidgets_FIND_STYLE})#is set by "findwxWidgets.cmake"
  message(wxWidgets_LIB_DIR: ${wxWidgets_LIB_DIR})
  message("wxWidgets_INCLUDE_DIRS: ${wxWidgets_INCLUDE_DIRS}")
  #message("wxWidgets_LIBRARIES: ${wxWidgets_LIBRARIES}")
  #showMsg(5, "wxWidgets_LIBRARIES: ${wxWidgets_LIBRARIES}")
  #Output "wxWidgets_LIBRARIES" in CMakeLists.txt before 
  # "target_link_libraries(${EXE_NAME} ${wxWidgets_LIBRARIES})"
  
  include(${CMAKE_CURRENT_LIST_DIR}/../CMake/ShowMsg_CompLvl.cmake)
  #include(${COMMON_SOURCECODE_ROOT_PATH}/CMake/ShowMsg_CompLvl.cmake)
  show1ItmPerLne(5 "wxWidgets_LIBRARIES:" "${wxWidgets_LIBRARIES}")
  message("wxWidgets_LIBRARY_DIRS: ${wxWidgets_LIBRARY_DIRS}")
  message("wxWidgets_DEFINITIONS: ${wxWidgets_DEFINITIONS}")
  message("wxWidgets_DEFINITIONS_DEBUG: ${wxWidgets_DEFINITIONS_DEBUG}")
  message("wxWidgets_CXX_FLAGS: ${wxWidgets_CXX_FLAGS}")
  message("wxWidgets_USE_FILE: ${wxWidgets_USE_FILE}")
 endif()
  
if(wxWidgets_FOUND)
  #https://cmake.org/cmake/help/v3.0/module/FindwxWidgets.html :
  #"The following are set after the configuration is done for both windows and
  # unix style:"
  message("wxWidgets FOUND")
  #Usually "UsewxWidgets.cmake": 
  # -calls include_directories(...) with wxWidgets_INCLUDE_DIRS
  # -calls link_directories(...) with wxWidgets_LIBRARY_DIRS
  # -adds wxWidgets_DEFINITIONS to "COMPILE_DEFINITIONS"
  # -adds wxWidgets_DEFINITIONS_DEBUG to "COMPILE_DEFINITIONS_DEBUG"
  # -adds wxWidgets_CXX_FLAGS to CMAKE_CXX_FLAGS
  include(${wxWidgets_USE_FILE}) #calls/includes CMake script
else()
  message( warning "wxWidgets not FOUND->maybe problem in findwxWidgets.cmake")
  #if(BUILD_SYSTEM_GENERATOR STREQUAL "MinGW Makefiles")
    message("wxWidgets_LIB_DIR: ${wxWidgets_LIB_DIR}")
  #endif()
endif()
#endfunction()
