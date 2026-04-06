cmake_minimum_required(VERSION 3.20)

project(assignments LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(ENABLE_COVERAGE "Enable code coverage with gcov" OFF)
option(ENABLE_SANITIZERS "Enable AddressSanitizer and UndefinedBehaviorSanitizer" OFF)
option(ENABLE_PROFILING "Enable profiling with -pg flag" OFF)

set(CMAKE_CXX_FLAGS_INIT "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-g -O0")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-O3")

if(ENABLE_COVERAGE)
  set(CMAKE_CXX_FLAGS_INIT "${CMAKE_CXX_FLAGS_INIT} --coverage -fprofile-arcs -ftest-coverage")
  set(CMAKE_EXE_LINKER_FLAGS_INIT "--coverage")
endif()

if(ENABLE_SANITIZERS)
  set(CMAKE_CXX_FLAGS_INIT "${CMAKE_CXX_FLAGS_INIT} -fsanitize=address,undefined -fno-omit-frame-pointer")
  set(CMAKE_EXE_LINKER_FLAGS_INIT "${CMAKE_EXE_LINKER_FLAGS_INIT} -fsanitize=address,undefined")
endif()

if(ENABLE_PROFILING)
  set(CMAKE_CXX_FLAGS_INIT "${CMAKE_CXX_FLAGS_INIT} -pg")
  set(CMAKE_EXE_LINKER_FLAGS_INIT "${CMAKE_EXE_LINKER_FLAGS_INIT} -pg")
endif()

message(STATUS "Coverage: ${ENABLE_COVERAGE}")
message(STATUS "Sanitizers: ${ENABLE_SANITIZERS}")
message(STATUS "Profiling: ${ENABLE_PROFILING}")
message(STATUS "CXX Flags: ${CMAKE_CXX_FLAGS_INIT}")

enable_testing()

add_subdirectory(assignment_1)
