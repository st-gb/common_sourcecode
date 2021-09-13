#see https://stackoverflow.com/questions/5248749/passing-a-list-to-a-cmake-macro :
#Double quote (") the list variable when calling this functions else only the
#1st element is passed. E.g. delimitStringsByPlusChar("${includedExes}")
#Callers pass actual variable name for plusCharDelimitedStrings without "${" "}"

#macro
function(delimitStringsByPlusChar charStrings plusCharDelimitedStrings)
  message("charStrings: ${charStrings}")
  #from https://stackoverflow.com/questions/17666003/cmake-output-a-list-with-delimiters
  # "," not possible: dpkg: "error processing archive 
  # /media/sg/devel1/SourceCodeManagement/wxSMARTmonitor/src/SMARTmonitor_wxGUI,
  # UNIX_service_x86_64_Lubuntu_Release-1.0.0-Linux.deb (--install):
  # parsing file '/var/lib/dpkg/tmp.ci/control' near line 1:
  # invalid package name (character ',' not allowed (only letters, digits and
  # characters '-+._'))"

  set(plusCharDelimitedStrings1 "")
  #https://cmake.org/cmake/help/latest/command/string.html : "string(REPLACE
  # <match_string> <replace_string> <output_variable> <input> [<input>...])"
  string(REPLACE ";" "+" plusCharDelimitedStrings1 "${charStrings}")
#  foreach(includedExe IN ${includedExes})
#    message("includedExe: " ${includedExe})
#    set(CPACK_PACKAGE_NAME "${CPACK_PACKAGE_NAME}${includedExe}+")
#  endforeach()
  message("plusCharDelimitedStrings1: ${plusCharDelimitedStrings1}")

  #http://stackoverflow.com/questions/14375519/how-to-write-a-nice-function-that-passes-variables-by-reference
  set(${plusCharDelimitedStrings} "${plusCharDelimitedStrings1}" PARENT_SCOPE)

  #set(plusCharDelimitedStrings plusCharDelimitedStrings1)
  #message("plusCharDelimitedStrings: ${plusCharDelimitedStrings} \"${plusCharDelimitedStrings}\"")
  #set(${charStrings} plusCharDelimitedStrings PARENT_SCOPE)
  #message("plusCharDelimitedStrings: ${plusCharDelimitedStrings}")
endfunction()
#endmacro()
