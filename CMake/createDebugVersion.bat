@REM Disable output of batch file commands.
@echo off
REM "%*" : All command line arguments passed to _this_ script.
SET dirOfThisScript=%~dp0\
%dirOfThisScript%\runCMakeBuildSysGenerator.bat %* "-DCMAKE_BUILD_TYPE=Debug"