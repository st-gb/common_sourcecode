@rem Disable output of batch file commands:
@echo off

rem Call this script file via "call" or "cmd /C" from another batch file in
rem  order to continue processing after this file.
rem http://en.wikibooks.org/wiki/Windows_Batch_Scripting#CALL :
rem "calling a batch program from a batch without using the "call" keyword
rem  results in the execution never returning to the caller once the callee
rem  finishes"

rem For getting the number of command line arguments see:
rem http://en.wikibooks.org/wiki/Windows_Batch_Scripting#Command-line_arguments
rem Do not use the "for"-loop version with "in (%*)" because for example passing
rem  only 1 command line argument '*' leaded to a count of 14 command line
rem  arguments.
rem Without defining/initializing the count was not correct.
set cmdLneArgCnt=0

:cntCmdLneArgsStart
if -%1-==-- goto cntCmdLneArgsEnd
Set /A cmdLneArgCnt+=1 &
rem http://en.wikibooks.org/wiki/Windows_Batch_Scripting#SHIFT : moves the
rem  batch file arguments index down : %2 -> %1
shift
goto cntCmdLneArgsStart
:cntCmdLneArgsEnd
