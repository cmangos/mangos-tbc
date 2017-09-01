project(lockless C CXX)
cmake_minimum_required(VERSION 2.6)

option(LOCKLESS_DEBUG_ALLOC "Debug lockless allocator" OFF)

if("${CMAKE_C_COMPILER_ID}" MATCHES "clang" OR "${CMAKE_C_COMPILER_ID}" MATCHES "Clang")
 set(CLANG 1)
endif("${CMAKE_C_COMPILER_ID}" MATCHES "clang" OR "${CMAKE_C_COMPILER_ID}" MATCHES "Clang")

set(CMAKE_C_FLAGS "")
set(CMAKE_CXX_FLAGS "")
set(CMAKE_C_FLAGS_RELEASE "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-g")
set(CMAKE_C_FLAGS_DEBUG "-ggdb")
set(CMAKE_CXX_FLAGS_DEBUG "-ggdb")

if(LOCKLESS_DEBUG_ALLOC)
 add_definitions(-DDEBUG_ALLOC -DDEBUG_ALLOC_SLOW)
endif()

if(CMAKE_COMPILER_IS_GNUCC OR CLANG OR MINGW)
 set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -fomit-frame-pointer -Wall -Wno-attributes -std=gnu99 -O3 -fno-builtin-malloc -fno-builtin-realloc -fno-builtin-calloc -fno-builtin-free -fno-builtin-memalign")
endif()

if(CLANG)
 set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-unused-function -Wno-ignored-attributes")
endif()

if(MINGW)
 set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -fomit-frame-pointer -O3 -fno-builtin-malloc -fno-builtin-realloc -fno-builtin-calloc -fno-builtin-free -fno-builtin-memalign")
 add_definitions(-DWINVER=0x0600 -D_WIN32_WINNT=0x0600)
endif()

if(MSVC)
 set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /O2 /MD")
 set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /O2 /MD")
endif()

if(NOT WIN32)
 set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread")
 add_library(lockless STATIC ${CMAKE_CURRENT_SOURCE_DIR}/src/ll_alloc.c)
else()
 add_library(lockless STATIC ${CMAKE_CURRENT_SOURCE_DIR}/src/ll_alloc.c ${CMAKE_CURRENT_SOURCE_DIR}/src/win_stub.cc)
endif()
