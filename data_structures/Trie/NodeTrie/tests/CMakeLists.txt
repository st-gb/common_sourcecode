#from https://cmake.org/cmake-tutorial/
cmake_minimum_required (VERSION 2.8)
project (NodeTrieIterator_test)

if( NOT DEFINED COMMON_SOURCECODE_ROOT_PATH )
  set(COMMON_SOURCECODE_ROOT_PATH "${PROJECT_SOURCE_DIR}/../../../../")
  message("setting COMMON_SOURCECODE_ROOT_PATH to ${COMMON_SOURCECODE_ROOT_PATH}")
endif()

set( CXX_DEFINITIONS
  ${CXX_DEFINITIONS}
  #-H #show includes hierarchy
)

add_definitions(${CXX_DEFINITIONS})

#see http://stackoverflow.com/questions/8934295/add-source-in-a-subdirectory-to-a-cmake-project
set(SOURCE_FILE_PATHS
  ${SOURCE_FILE_PATHS}
  ${PROJECT_SOURCE_DIR}/NodeTrieIterator_test.cpp
)

set( INCLUDE_DIRS
  ${INCLUDE_DIRS}
  ${COMMON_SOURCECODE_ROOT_PATH}
)

include_directories( ${INCLUDE_DIRS} )

add_executable(${PROJECT_NAME} ${SOURCE_FILE_PATHS})
target_link_libraries(${PROJECT_NAME} ${LIBRARIES})

