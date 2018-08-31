set(PROJECT_TEST_NAME ${PROJECT_NAME}_test)
# set(PROJECT_TEST_LIBS ${PROJECT_LIB_NAME} ${WGE_LIBRARIES})

include(ParseAndAddCatchTests)

if (CMAKE_COMPILER_IS_GNUCXX AND CMAKE_BUILD_TYPE STREQUAL "Debug" AND USE_GCOV)
  setup_target_for_coverage(unittest_coverage ${PROJECT_TEST_NAME} unittest_coverage)
endif ()

# set(WAGIC_TEST_MTG_SRC    "${CMAKE_CURRENT_SOURCE_DIR}/mtg/card_basics_tests.cxx"
#                           "${CMAKE_CURRENT_SOURCE_DIR}/mtg/mana_cost_array_tests.cxx"
#                           "${CMAKE_CURRENT_SOURCE_DIR}/mtg/mana_cost_hybrid_tests.cxx"
# )

add_executable (${PROJECT_TEST_NAME}  ${CATCH_MAIN_FILE}
)

# target_link_libraries (${PROJECT_TEST_NAME} ${PROJECT_TEST_LIBS})

ParseAndAddCatchTests (${PROJECT_TEST_NAME})