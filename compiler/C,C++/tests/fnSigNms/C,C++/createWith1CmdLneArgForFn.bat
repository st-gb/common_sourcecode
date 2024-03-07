@rem Disable printing commands
@echo off
echo Pass CMake build generator as 1st command line argument.
echo Enclose command line argument in brackets if it includes space characters.
SET CMakeBuildSysGenerator=%1
echo CMakeBuildSysGenerator: %CMakeBuildSysGenerator%
cmake -G %CMakeBuildSysGenerator% ^
 \" -DoneCmdLneArgForFn=TRUE\"