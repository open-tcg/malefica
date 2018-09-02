set(PROJECT_TEST_NAME ${PROJECT_NAME}_test)
set(PROJECT_TEST_LIBS ${PROJECT_LIB_NAME} ${MALEFICA_LIBRARIES})

include(ParseAndAddCatchTests)

if (CMAKE_COMPILER_IS_GNUCXX AND CMAKE_BUILD_TYPE STREQUAL "Debug" AND USE_GCOV)
  setup_target_for_coverage(unittest_coverage ${PROJECT_TEST_NAME} unittest_coverage)
endif ()

set(MALEFICA_TEST_LOG_SRC   "${CMAKE_CURRENT_SOURCE_DIR}/mge/log/formatter_tests.cxx"
                            "${CMAKE_CURRENT_SOURCE_DIR}/mge/log/message_tests.cxx"
)

set(MALEFICA_TEST_MATH_SRC  "${CMAKE_CURRENT_SOURCE_DIR}/mge/math/vector_2d_tests.cxx"
                            "${CMAKE_CURRENT_SOURCE_DIR}/mge/math/vector_3d_tests.cxx"
)

set(MALEFICA_TEST_MGE_SRC   ${MALEFICA_TEST_LOG_SRC}
                            ${MALEFICA_TEST_MATH_SRC}
)

set(MALEFICA_TEST_MTG_SRC   "${CMAKE_CURRENT_SOURCE_DIR}/mtg/mana_types_tests.cxx"
)

add_executable (${PROJECT_TEST_NAME}  ${CATCH_MAIN_FILE}
                                      ${MALEFICA_TEST_MGE_SRC}
                                      ${MALEFICA_TEST_MTG_SRC}
)

target_link_libraries (${PROJECT_TEST_NAME} ${PROJECT_TEST_LIBS})

ParseAndAddCatchTests (${PROJECT_TEST_NAME})