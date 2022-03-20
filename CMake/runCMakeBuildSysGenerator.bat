@REM Disable output of batch file commands.
@echo off
echo You may need to replace "\" with "/" in file system paths to work.
echo Else errors like "Invalid escape sequence \c" may appear.

rem See http://en.wikibooks.org/wiki/Windows_Batch_Scripting#CALL ,
rem http://en.wikibooks.org/wiki/Windows_Batch_Scripting#Percent_tilde ,
rem http://en.wikibooks.org/wiki/Windows_Batch_Scripting#Variable_substitution :
rem  "%~dp0": d="Drive letter" p="Drive-less path with the trailing backslash"
rem  0:this script's file path %*:"is replaced with the values of all the
rem  command-line parameters except for %0"
call %~dp0\..\OperatingSystem\DOS\batch_files\getNumCmdLneArgs.bat %*

echo Number of command line arguments:%cmdLneArgCnt%

if %cmdLneArgCnt% lss 5 ( rem LeSS than (<) 5
  echo Pass command line arguments to this script:
  echo 1.CMake build system generator name. Enclose in quotation marks('"') if
  echo  space character between:for example '"Unix Makefiles"'
  echo 2.C compiler absolute or relative file system path
  echo 3.C++ compiler absolute or relative file system path
  echo 4.additional CMake arguments:put in quotation marks('"') if > 1 argument
  echo  or space character between:for example:'"-DMIN=1 -DMAX=2"'
  goto end
)
set CMakeBuildSysGenerator=%1
echo CMake build system generator (enclose in quotation marks if space^
 character in between):%CMakeBuildSysGenerator%
set CMakeC_compiler=%2
echo CMake C compiler (file system path):%CMakeC_compiler%
set CMakeCxx_compiler=%3
echo CMake C++ compiler (file system path):%CMakeCxx_compiler%

rem Command line argument from this script's indirect caller.
set additionalCMakeArgs=%4

REM Defining variables within "if-block" didn't work, so use "goto".
if %cmdLneArgCnt% LSS 5 goto UnQuoteAdditionalCMakeArgs

REM Command line argument may come from the *direct* caller, for example
rem  "createDebugVersion.bat" (as '"-DCMAKE_BUILD_TYPE=Debug"').
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
:end