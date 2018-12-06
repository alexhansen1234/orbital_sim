cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(orbital_sim LANGUAGES CXX)

add_subdirectory(lib/rk4)
add_subdirectory(lib/Quaternion)

add_library(orbital_sim SHARED
  src/sv.cpp
)

target_include_directories(orbital_sim
PUBLIC
  include
)

target_link_libraries(orbital_sim
PUBLIC
  Quaternion
  rk4
  stdc++
)

target_compile_options(orbital_sim
PUBLIC
  -Wall
  -O3
  -std=c++14
)

set(CMAKE_CURRENT_BINARY_DIRECTORY ${PROJECT_SOURCE_DIR}/build)

get_property(QUATERNION_INCLUDES TARGET Quaternion PROPERTY INTERFACE_INCLUDE_DIRECTORIES)
get_property(RK4_INCLUDES TARGET rk4 PROPERTY INTERFACE_INCLUDE_DIRECTORIES)

FIND_PACKAGE(SWIG REQUIRED)
INCLUDE(${SWIG_USE_FILE})

FIND_PACKAGE(PythonLibs)
INCLUDE_DIRECTORIES(${PYTHON_INCLUDE_PATH})

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/include ${QUATERNION_INCLUDES} ${RK4_INCLUDES})

SET(CMAKE_SWIG_FLAGS "")

SET_SOURCE_FILES_PROPERTIES(swig/orbital_sim.i src/sv.cpp PROPERTIES CPLUSPLUS ON)
SWIG_ADD_LIBRARY(orbital_sim LANGUAGE python SOURCES swig/orbital_sim.i src/sv.cpp)
SWIG_LINK_LIBRARIES(orbital_sim rk4 Quaternion ${PYTHON_LIBRARIES})
set_property(TARGET orbital_sim PROPERTY SWIG_USE_LIBRARY_INCLUDE_DIRECTORIES TRUE)

file(GLOB SCRIPTS "script/*")
file(COPY ${SCRIPTS} DESTINATION ${CMAKE_CURRENT_BINARY_DIRECTORY})
