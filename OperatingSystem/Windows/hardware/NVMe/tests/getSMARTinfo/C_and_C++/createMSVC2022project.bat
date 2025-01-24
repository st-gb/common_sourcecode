@REM Disable printing shell commands to standard output.
@echo off
REM Replace value of "boostRootDir" and "cxxoptsDir"(right of "=" character)
REM  with suitable paths.
cmake -G "Visual Studio 17 2022" -DboostRootDir=D:/Boost1.81.0/boost_1_81_0/ ^
-DcxxoptsDir=D:/