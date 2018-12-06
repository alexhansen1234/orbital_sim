cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(Quaternion LANGUAGES CXX)

add_library(Quaternion INTERFACE)

target_include_directories(Quaternion
INTERFACE
  include
  swig
)

set(CMAKE_CURRENT_BINARY_DIRECTORY ${PROJECT_SOURCE_DIR}/build)

FIND_PACKAGE(SWIG REQUIRED)
INCLUDE(${SWIG_USE_FILE})

FIND_PACKAGE(PythonLibs)
INCLUDE_DIRECTORIES(${PYTHON_INCLUDE_PATH})

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/include)

SET(CMAKE_SWIG_FLAGS "")

SET_SOURCE_FILES_PROPERTIES(swig/Quaternion.i PROPERTIES CPLUSPLUS ON)
SWIG_ADD_LIBRARY(Quaternion LANGUAGE python SOURCES swig/Quaternion.i)
SWIG_LINK_LIBRARIES(Quaternion ${PYTHON_LIBRARIES})

file(GLOB SCRIPTS "script/*")
file(COPY ${SCRIPTS} DESTINATION ${CMAKE_CURRENT_BINARY_DIRECTORY})

if(${BUILD_TESTS})
  set(QUAT_TEST Quaternion_test.elf)
  add_executable(${QUAT_TEST}
    example/main.cpp
  )
  target_link_libraries(${QUAT_TEST}
    stdc++
  )
  target_include_directories(${QUAT_TEST}
    PUBLIC
      include
  )
  target_compile_options(${QUAT_TEST}
    PUBLIC
      -Wall
      -O3
      -std=c++14
  )
endif(${BUILD_TESTS})
