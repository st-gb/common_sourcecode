#Include this file from another shell script with the "source" shell command.

#http://en.wikipedia.org/wiki/ANSI_escape_code#SGR_(Select_Graphic_Rendition)_parameters
# : "Select Graphic Rendition (SGR) sets display attributes. Several attributes
# can be set in the same sequence, separated by semicolons."

function printError()
{  
#http://stackoverflow.com/questions/1983048/passing-a-string-with-spaces-as-a-function-argument-in-bash
# from "Samveen Jun 14 '13 at 7:06" for "$@"

#http://en.wikipedia.org/wiki/ANSI_escape_code#3-bit_and_4-bit
# : "FG" (ForeGround)
#   "31 [...] Red"
#http://en.wikipedia.org/wiki/ANSI_escape_code#SGR_(Select_Graphic_Rendition)_parameters
# : "0	Reset or normal"
  echo -e "\033[31m$@\033[0m"
}

function printSuccess()
{
#http://stackoverflow.com/questions/1983048/passing-a-string-with-spaces-as-a-function-argument-in-bash
# from "Samveen Jun 14 '13 at 7:06" for "$@"

#http://en.wikipedia.org/wiki/ANSI_escape_code#3-bit_and_4-bit
# : "FG" (ForeGround)
#   "32 [...] Green"
#http://en.wikipedia.org/wiki/ANSI_escape_code#SGR_(Select_Graphic_Rendition)_parameters
# : "0	Reset or normal"
  echo -e "\033[32m$@\033[0m"
}

