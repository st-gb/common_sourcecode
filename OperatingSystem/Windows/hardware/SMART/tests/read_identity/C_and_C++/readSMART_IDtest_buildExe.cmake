include_directories(${inclDirs})

include(${cmnSrcRootDir}/compiler/C,C++/printInclDirs.cmake)
printInclDirs(6)

include(${cmnSrcRootDir}/dataType/charStr/suffixCMakeBuildType.cmake)
set(exeName ${PROJECT_NAME})
suffixCMakeBuildType(exeName 1)

add_executable(${exeName} ${srcFilePaths})