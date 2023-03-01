##author Stefan Gebauer(TU Berlin matriculation number 361095)

#from https://cmake.org/cmake-tutorial/
cmake_minimum_required (VERSION 2.8)
##Avail=AVAILable:http://www.abbreviations.com/abbreviation/Available
##Gvrnrs=GoVeRNoRS(not "Gov", because this also means GOVernment)
project(getAvailGvrnrsTest)

if( NOT DEFINED cmnSrcRootDir )
  set(cmnSrcRootDir "${PROJECT_SOURCE_DIR}/../../../../../")
  message("setting cmnSrcRootDir to ${cmnSrcRootDir}")
endif()

#see http://stackoverflow.com/questions/8934295/add-source-in-a-subdirectory-to-a-cmake-project
set(srcFlPths
  ${PROJECT_SOURCE_DIR}/main.c
  ${PROJECT_SOURCE_DIR}/../../availGvrnrsAbsFilePathFmtStr.c
  ${PROJECT_SOURCE_DIR}/../../getAvailGvrnrs.c
)

set(INCLUDE_DIRS
  ${INCLUDE_DIRS}
  ${cmnSrcRootDir}
)

include_directories(${INCLUDE_DIRS})

set(exeFlNm ${PROJECT_NAME})
include(${cmnSrcRootDir}/dataType/charStr/suffixCMakeBuildType.cmake)
suffixCMakeBuildType(exeFlNm 0)
include(${cmnSrcRootDir}/dataType/charStr/suffixExeFileExt.cmake)
suffixExeFileExt(exeFlNm)

add_executable(${exeFlNm} ${srcFlPths})
