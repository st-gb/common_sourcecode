@REM "@echo off":disable output of commands
@echo off
REM Don't name this script "start.bat" because when leaving out the ".bat" file
REM  extension it equals Microsoft's "start" command:
REM  "Starts a separate window to run a specified program or command"
REM https://docs.microsoft.com/en-us/windows-server/administration/windows-commands/start
REM  and then this command is run instead.

set exePath=%1
REM wxWidgets DLLs are neccessary, else the executable does not start.
REM wxDLLdir e.g. E:\wxWidgets\MSW-3.1.0_gcc510TDM_x64_Dev\lib\gcc_dll
set wxDLLdir=%2
echo wxDLLdir: %wxDLLdir%
set PATH=%PATH%;%wxDLLdir%
%exePath%