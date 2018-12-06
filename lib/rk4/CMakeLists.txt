cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(rk4 LANGUAGES CXX)

set(CMAKE_CURRENT_BINARY_DIRECTORY ${PROJECT_SOURCE_DIR}/build)

add_library(rk4 SHARED
  src/rk4.cpp
)

target_include_directories(rk4
PUBLIC
  include
  swig
)

target_compile_options(rk4
PUBLIC
  -Wall
  -O3
  -std=c++14
)

target_link_libraries(rk4
PUBLIC
  stdc++
)

FIND_PACKAGE(SWIG REQUIRED)
INCLUDE(${SWIG_USE_FILE})

FIND_PACKAGE(PythonLibs)
INCLUDE_DIRECTORIES(${PYTHON_INCLUDE_PATH})

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/include)

SET(CMAKE_SWIG_FLAGS "")

SET_SOURCE_FILES_PROPERTIES(swig/rk4.i PROPERTIES CPLUSPLUS ON)
SWIG_ADD_LIBRARY(rk4 LANGUAGE python SOURCES swig/rk4.i)
SWIG_LINK_LIBRARIES(rk4 ${PYTHON_LIBRARIES} rk4)

file(GLOB SCRIPTS "script/*")
file(COPY ${SCRIPTS} DESTINATION ${CMAKE_CURRENT_BINARY_DIRECTORY})

if(BUILD_TESTS)
    add_executable(rk4_example.elf
        example/rk4_example.cpp
    )

    target_link_libraries(rk4_example.elf
        stdc++
    )

    target_include_directories(rk4_example.elf
        PUBLIC
        include
    )

    target_compile_options(rk4_example.elf
        PUBLIC
        -Wall
        -O3
        -std=c++14
    )
endif(BUILD_TESTS)
