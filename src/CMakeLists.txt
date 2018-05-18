set(PROJECT_LIB_NAME "${PROJECT_NAME}")
set(PROJECT_APP_NAME "${PROJECT_NAME}_app")

if (CMAKE_COMPILER_IS_GNUCXX AND CMAKE_BUILD_TYPE STREQUAL "Debug" AND USE_GCOV)
  include(CodeCoverage)
  set(CMAKE_CXX_FLAGS "-g -O0 -Wall -Wdeprecated-declarations --coverage")
  set(LCOV_REMOVE_EXTRA '${CMAKE_SOURCE_DIR}/3rd/*' '${CMAKE_CURRENT_SOURCE_DIR}/tests/*')
endif()

add_subdirectory(malefica)
add_subdirectory(tests)