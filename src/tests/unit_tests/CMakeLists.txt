include_directories ("${THIRD_PARTY_TEST_INCLUDE_DIR}")

set(PROJECT_TEST_NAME ${PROJECT_NAME}_test)
set(PROJECT_TEST_LIBS ${PROJECT_LIB_NAME} ${THIRD_PARTY_LIBRARIES})

if (CMAKE_COMPILER_IS_GNUCXX AND CMAKE_BUILD_TYPE STREQUAL "Debug" AND USE_GCOV)
  setup_target_for_coverage(coverage ${PROJECT_TEST_NAME} coverage)
endif ()

set(CATCH_MAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/catch_main.cxx")
add_executable (${PROJECT_TEST_NAME}  "${CATCH_MAIN_FILE}"
                                      "${CMAKE_CURRENT_SOURCE_DIR}/malefica/ecs/entity_factory_tests.cxx"

                                      "${CMAKE_CURRENT_SOURCE_DIR}/malefica/log/formatter_tests.cxx"
                                      "${CMAKE_CURRENT_SOURCE_DIR}/malefica/log/logger_tests.cxx"
                                      "${CMAKE_CURRENT_SOURCE_DIR}/malefica/log/message_dispatcher_tests.cxx"

                                      "${CMAKE_CURRENT_SOURCE_DIR}/malefica/thread/queue_tests.cxx"
                                      "${CMAKE_CURRENT_SOURCE_DIR}/malefica/thread/dispatcher_tests.cxx"
)
target_link_libraries (${PROJECT_TEST_NAME} ${PROJECT_TEST_LIBS})
ParseAndAddCatchTests (${PROJECT_TEST_NAME})