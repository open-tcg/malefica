include_directories ("${THIRD_PARTY_TEST_INCLUDE_DIR}")

set(PROJECT_TEST_NAME ${PROJECT_NAME}_test)
set(PROJECT_TEST_LIBS ${THIRD_PARTY_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} )
#set(PROJECT_TEST_LIBS ${PROJECT_LIB_NAME} ${THIRD_PARTY_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} )

if (CMAKE_COMPILER_IS_GNUCXX AND CMAKE_BUILD_TYPE STREQUAL "Debug" AND USE_GCOV)
  setup_target_for_coverage(coverage ${PROJECT_TEST_NAME} coverage)
endif ()

set(CATCH_MAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/catch_main.cxx")
add_executable (${PROJECT_TEST_NAME}  "${CATCH_MAIN_FILE}"
                                      "${CMAKE_CURRENT_SOURCE_DIR}/malefica/ecs/entity_factory_tests.cxx"
                                      "${CMAKE_CURRENT_SOURCE_DIR}/malefica/debug/formatter_tests.cxx"
)
target_link_libraries (${PROJECT_TEST_NAME} ${PROJECT_TEST_LIBS})
ParseAndAddCatchTests (${PROJECT_TEST_NAME})