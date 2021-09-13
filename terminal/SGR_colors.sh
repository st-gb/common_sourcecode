#Include this file from another shell script with the "source" shell command.

#Accordung to http://en.wikipedia.org/wiki/ANSI_escape_code#3-bit_and_4-bit
# these color codes are supported in Linux, Windows, puTTy, etc.,
# i.e. not (always) related/specific to an Operating System.
# And they are for "text terminals and terminal emulators."
# (http://en.wikipedia.org/wiki/ANSI_escape_code)
# place this file into "common_sourcecode/terminal"?

#http://en.wikipedia.org/wiki/ANSI_escape_code#SGR_(Select_Graphic_Rendition)_parameters
# : "Select Graphic Rendition (SGR) sets display attributes. Several attributes
# can be set in the same sequence, separated by semicolons."

#Can be used in "echo" shell script commands

#http://en.wikipedia.org/wiki/ANSI_escape_code#SGR_(Select_Graphic_Rendition)_parameters
# : "0	Reset or normal" "All attributes off"
SGRreset=\\033[0m

#http://en.wikipedia.org/wiki/ANSI_escape_code#3-bit_and_4-bit
# : "FG" (ForeGround)
#   "31 [...] Red"
SGRcyan=\\033[36m
