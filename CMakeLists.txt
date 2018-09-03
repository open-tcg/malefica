cmake_minimum_required(VERSION 3.1)

project(malefica LANGUAGES C CXX VERSION 0.1.0)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/modules")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wdeprecated-declarations")
endif()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

option(USE_GCOV "create coverage build" OFF)
if (CMAKE_COMPILER_IS_GNUCXX AND CMAKE_BUILD_TYPE STREQUAL "Debug" AND USE_GCOV)
  include(CodeCoverage)
  set(CMAKE_CXX_FLAGS "-g -O0 -Wall -Wextra -Wno-shadow -Wno-sign-conversion -Wnon-virtual-dtor -Wdeprecated-declarations -Wno-unused-parameter --coverage")
  set(LCOV_REMOVE_EXTRA '${CMAKE_SOURCE_DIR}/3rd/*' '${CMAKE_CURRENT_SOURCE_DIR}/src/tests/*')
endif()

option(USE_GPROF "create profiling build" OFF)
if (CMAKE_COMPILER_IS_GNUCXX AND CMAKE_BUILD_TYPE STREQUAL "Debug" AND USE_GPROF)
  set(CMAKE_CXX_FLAGS "-g -O0 -Wall -Wextra -Wno-shadow -Wno-sign-conversion -Wnon-virtual-dtor -Wdeprecated-declarations -Wno-unused-parameter -pg")
endif()


add_subdirectory (3rd EXCLUDE_FROM_ALL)

find_package(Threads REQUIRED)

include_directories ("${THIRD_PARTY_INCLUDE_DIRS}")
include_directories ("${CMAKE_SOURCE_DIR}/include")

set(MALEFICA_LIBRARIES ${CMAKE_THREAD_LIBS_INIT})

enable_testing()
add_subdirectory(src)

# find_package(Doxygen)
# if(DOXYGEN_FOUND)
#     add_subdirectory(doc)
# endif()