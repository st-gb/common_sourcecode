@REM Disable output of batch file commands.
@echo off
echo You may need to replace "\" with "/" in file system paths to work.
echo Else errors like "Invalid escape sequence \c" may appear.

set CMakeBuildSysGenerator=%1
echo CMake build system generator (enclose in quotation marks if space^
 character in between):%CMakeBuildSysGenerator%
set CMakeC_compiler=%2
echo CMake C compiler (file system path):%CMakeC_compiler%
set CMakeCxx_compiler=%3
echo CMake C++ compiler (file system path):%CMakeCxx_compiler%

set additionalCMakeArgs=%4

set cmdLneArgCnt=0
for %%x in (%*) do Set /A cmdLneArgCnt+=1
echo # command line args:%cmdLneArgCnt%

REM Defining variables within "if-block" didn't work, so use "goto".
if %cmdLneArgCnt% LSS 5 goto UnQuoteAdditionalCMakeArgs

REM Command line argument may come from a call of "createDebugVersion.bat"
set callerCMakeArgs=%5
echo Arguments to CMake from caller script:%callerCMakeArgs%
REM CMake arguments with "=" or " " usually need to be quoted. Remove quotation.
set callerCMakeArgs=%callerCMakeArgs:"=%
REM Concatenate strings
set additionalCMakeArgs=%additionalCMakeArgs% %callerCMakeArgs%

:UnQuoteAdditionalCMakeArgs
REM Additional CMake arguments usually need to be quoted. Remove quotation, else
REM  CMake error "CMake Error: The source directory  [...] does not exist."
REM '"' to '' (remove '"' character)
set additionalCMakeArgs=%additionalCMakeArgs:"=%
echo additional CMake arguments:%additionalCMakeArgs%

cmake ^
-G %CMakeBuildSysGenerator% ^
-DCMAKE_C_COMPILER=%CMakeC_compiler% ^
-DCMAKE_CXX_COMPILER=%CMakeCxx_compiler% ^
%additionalCMakeArgs% ^
-DCMAKE_EXPORT_COMPILE_COMMANDS=ON ^
.