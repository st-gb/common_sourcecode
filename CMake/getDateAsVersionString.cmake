#Useful e.g. for versioning software packages, e.g. for .deb or .zip files.
function(getDateAsVersionString dateAsVersionString)
  #message(STATUS "Creating version:begin")

  #See "man date"
  #execute_process(COMMAND date +'%y' OUTPUT_VARIABLE currYear)
  #execute_process(COMMAND date +'%m' OUTPUT_VARIABLE currMonth)
  #execute_process(COMMAND date +'%d' OUTPUT_VARIABLE currDay)
  #"PARENT_SCOPE" to propagate the new value outside of this function.
  #set(dateAsVersionString "${currYear}.${currMonth}.${currDay}" PARENT_SCOPE)

  execute_process(COMMAND date +%y.%m.%d OUTPUT_VARIABLE dateAsVersionString)
  #from https://stackoverflow.com/questions/39496043/how-to-strip-trailing-whitespace-in-cmake-variable
  string(REGEX REPLACE "\n$" "" dateAsVersionString "${dateAsVersionString}")
  #"PARENT_SCOPE" to propagate the new value outside of this function.
  set(dateAsVersionString ${dateAsVersionString} PARENT_SCOPE)

  #message(STATUS "Creating version:end")
endfunction()
