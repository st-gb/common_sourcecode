
wxInclDir=$1 #e.g. E:/wxWidgets/3.1.0/include
wxLibsRootDir=$2 #e.g. E:/wxWidgets/MSW-3.1.0_gcc510TDM_x64_Dev

cmake \
-G "Unix Makefiles" \
-DwxInclDir=$wxInclDir \
-DwxLibsRootDir=$wxLibsRootDir
