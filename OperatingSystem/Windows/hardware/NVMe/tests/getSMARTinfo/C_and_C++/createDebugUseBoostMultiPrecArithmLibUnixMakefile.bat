cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_COMPILER=g++ ^
  -DboostRootDir=D:\Boost1.81.0\boost_1_81_0 ^
  -DcxxoptsDir=D:\ ^
  -DCMAKE_C_FLAGS_DEBUG="-g3 -gdwarf-2" -DCMAKE_CXX_FLAGS_DEBUG="-g3 -gdwarf-2" ^
  -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ^
  .
REM cmake --build .