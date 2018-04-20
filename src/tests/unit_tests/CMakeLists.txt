include_directories ("${THIRD_PARTY_TEST_INCLUDE_DIR}")

set(PROJECT_TEST_NAME ${PROJECT_NAME}_test)
#set(PROJECT_TEST_LIBS ${PROJECT_LIB_NAME})

set(CATCH_MAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/catch_main.cxx")
add_executable( ${PROJECT_TEST_NAME} "${CATCH_MAIN_FILE}"
)
#target_link_libraries(${PROJECT_TEST_NAME} ${PROJECT_TEST_LIBS} )

ParseAndAddCatchTests (${PROJECT_TEST_NAME})