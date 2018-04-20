
set(MALEFICA_SOURCES    "${CMAKE_CURRENT_SOURCE_DIR}/log/logger.cxx"
                        "${CMAKE_CURRENT_SOURCE_DIR}/log/message_sink.cxx"
)

add_library(${PROJECT_LIB_NAME} STATIC ${MALEFICA_SOURCES})