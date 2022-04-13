cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

project(qx-qml-treeview)

option(BUILD_EXAMPLES "Build examples" NO)

include(CMakeDependentOption)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH};${DEPENDENCIES_DIR}/share/cmakemodules)
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH};${DEPENDENCIES_DIR}/share/cmake)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(QX_BIN_DIR "bin" CACHE STRING "Binaries directory")
set(QX_CONFIG_DIR "share/cmake" CACHE STRING "Config directory")
set(QX_INCLUDE_DIR "include" CACHE STRING "Includes directory")
set(QX_LIB_DIR "lib" CACHE STRING "Libraries directory")

set(OUTPUT_DIR "${CMAKE_BINARY_DIR}/${PROJECT_NAME}")

include(UseFiles)

use_files(cmake "cmake/*")

add_subdirectory(src)

if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
