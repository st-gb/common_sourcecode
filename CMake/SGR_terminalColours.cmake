#http://en.wikipedia.org/wiki/ANSI_escape_code#SGR_(Select_Graphic_Rendition)_parameters
# : "Select Graphic Rendition (SGR) sets display attributes. Several attributes
# can be set in the same sequence, separated by semicolons."

#http://stackoverflow.com/questions/18968979/how-to-get-colorized-output-with-cmake
# "answered Oct 24 '13 at 23:07" by "Fraser"
if(NOT WIN32)
  string(ASCII 27 Esc)
#The codes can be found in
#http://en.wikipedia.org/wiki/ANSI_escape_code#SGR_(Select_Graphic_Rendition)_parameters
# : "If no codes are given, CSI m is treated as CSI 0 m (reset / normal)."
  set(SGR_ColourReset "${Esc}[m")
  set(SGR_ColourBold  "${Esc}[1m")
#The codes can be found in
# http://en.wikipedia.org/wiki/ANSI_escape_code#3-bit_and_4-bit
  set(SGR_Red         "${Esc}[31m")
  set(SGR_Green       "${Esc}[32m")
  set(SGR_Yellow      "${Esc}[33m")
  set(SGR_Blue        "${Esc}[34m")
  set(SGR_Magenta     "${Esc}[35m")
  set(SGR_Cyan        "${Esc}[36m")
  set(SGR_White       "${Esc}[37m")
endif()

