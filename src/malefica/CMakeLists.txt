
set(MALEFICA_MTG_SOURCES  "${CMAKE_CURRENT_SOURCE_DIR}/mtg/mana_cost.cxx"
                          "${CMAKE_CURRENT_SOURCE_DIR}/mtg/mana_types.cxx"
)

set(MALEFICA_SOURCES ${MALEFICA_MTG_SOURCES})

add_library(${PROJECT_LIB_NAME} STATIC ${MALEFICA_SOURCES})