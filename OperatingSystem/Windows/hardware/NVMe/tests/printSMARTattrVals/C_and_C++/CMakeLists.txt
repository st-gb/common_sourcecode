##(c)from 2024 Stefan Gebauer,Computer Science Master(TU Berlin matr.no.361095)
## @author Stefan Gebauer(TU Berlin matriculation number 361095)

project(NVMeReadSMARTattrValC_andCpp)##attrVal=ATTRibute VALue

cmake_minimum_required(VERSION 2.10)#TODO really min. ver.?

set(currFilePath ##CURRent FILE PATH 
  ##https://cmake.org/cmake/help/latest/variable/CMAKE_CURRENT_LIST_FILE.html :
  ## "Full path to the listfile currently being processed."
  ## (the "CMakeLists.txt" file)
  ${CMAKE_CURRENT_LIST_FILE})

set(cmnSrcDir ${PROJECT_SOURCE_DIR}/../../../../../../..)

if(NOT DEFINED TU_Bln361095logLvl)
  set(TU_Bln361095logLvl 4)
  message("\"TU_Bln361095logLvl\" is not defined(can be set on CMake command "
    "line via \"-DTU_Bln361095logLvl=\")--so set it to "
    "\"${TU_Bln361095logLvl}\"")
endif()

##TU_Bln361095setAndResolveFileSysPath(...)
include(${cmnSrcDir}/FileSystem/setAndResolveFileSysPath.cmake)
TU_Bln361095setAndResolveFileSysPath(cmnSrcDir ${cmnSrcDir})

set(inclDirs ${cmnSrcDir})

##TU_Bln361095printList1ItemPerLine(...)
include(${cmnSrcDir}/CMake/printList1ItemPerLine.cmake)
TU_Bln361095printList1ItemPerLine("CMakeLists.txt" "${inclDirs}")

message("CMAKE_CXX_COMPILER_ID: ${CMAKE_CXX_COMPILER_ID}")

set(srcFilePaths "")
set(NVMeReadSMARTattrValTestRootDir ${CMAKE_CURRENT_LIST_DIR}/..)
message("${currFilePath}--NVMeReadSMARTattrValTestRootDir:"
  "${NVMeReadSMARTattrValTestRootDir}")

##http://cmake.org/cmake/help/latest/command/list.html#length
list(LENGTH srcFilePaths numSrcFilePathsBeforeGNU_C_Test)
if(DEFINED GNUmultiPrecisionArithmLibRootDir)

  include(../C/GNU_C_compiler.cmake)##testUseGNU_C_compiler(...)
  testUseGNU_C_compiler(#"${srcFilePaths}"
    ${inclDirs} "${srcFilePaths}" "${NVMeReadSMARTattrValTestRootDir}"
    ${GNUmultiPrecisionArithmLibRootDir} )

endif()
##http://cmake.org/cmake/help/latest/command/list.html#length
list(LENGTH srcFilePaths numSrcFilePathsAfterGNU_C_Test)

message("${currFilePath}--Number of source files before and after GNU C "
  "\"compiler test:${numSrcFilePathsBeforeGNU_C_Test}\","
  "\"${numSrcFilePathsAfterGNU_C_Test}\"")

if(numSrcFilePathsAfterGNU_C_Test EQUAL numSrcFilePathsBeforeGNU_C_Test)
  message("${currFilePath}--Test if GNU C compiler failed--testing with C++")
  include(Cpp_compiler.cmake)##testUseCpp_compiler(...)
  testUseCpp_compiler("${inclDirs}" "${srcFilePaths}"
    ${NVMeReadSMARTattrValTestRootDir} ${boostRootDir} ${cxxoptsDir})
endif()

include_directories(${inclDirs})

include(${cmnSrcDir}/compiler/C,C++/printInclDirs.cmake)
TU_Bln361095printCmplrInclDirs(${currFilePath})

include(${cmnSrcDir}/dataType/charStr/suffixCMakeBuildType.cmake)
set(exeName ${PROJECT_NAME})
TU_Bln361095suffixCMakeBuildType(#${exeName}
  exeName)

message("${currFilePath}--source file paths:\"${srcFilePaths}\" for "
  "\"${exeName}\"")
add_executable(${exeName} ${srcFilePaths})

#target_compile_definitions(${exeName} PUBLIC cxxoptsDir=${cxxoptsDir})

if(numSrcFilePathsAfterGNU_C_Test GREATER numSrcFilePathsBeforeGNU_C_Test)
  message("Test if GNU C compiler succeeded--linking \"${exeName}\" to GNU"
    " multiprecision arithmetic library")
  include(${cmnSrcDir}/dataType/bigUint/useGNUmultiPrecArithmLib.cmake)
  TU_Bln361095linkToGNUmultiPrecArithmLib(${exeName}
    ${GNUmultiPrecisionArithmLibRootDir})
endif()

#TU_Bln361095compilerPrintDefsAndSrcFilesAndInclDirs(${exeName})
#TU_Bln361095printCmplrPreprocDefs(${currFilePath})

##TU_Bln361095cmplrPrintPreprocDefs(...),
## TU_Bln361095cmplrPrintTargetSrcFiles(...)
include(${cmnSrcDir}/compiler/printTargetProperties.cmake)
TU_Bln361095cmplrPrintTargetPreprocDefs(${exeName} ${currFilePath})
TU_Bln361095cmplrPrintTargetSrcFiles(${exeName} ${currFilePath} )
