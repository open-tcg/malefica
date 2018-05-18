#configure directories
set (THIRD_PARTY_MODULE_PATH "${PROJECT_SOURCE_DIR}/3rd")

# -------------------------------------------------------------------------
# catch
set (CATCH_MODULE_PATH "${THIRD_PARTY_MODULE_PATH}/Catch2")
set (CATCH_INCLUDE_PATH "${CATCH_MODULE_PATH}/single_include")

include ("${CATCH_MODULE_PATH}/contrib/ParseAndAddCatchTests.cmake")
set (THIRD_PARTY_TEST_INCLUDE_DIR  ${CATCH_INCLUDE_PATH})
set (THIRD_PARTY_TEST_INCLUDE_DIR  ${THIRD_PARTY_TEST_INCLUDE_DIR} PARENT_SCOPE)

# -------------------------------------------------------------------------
# entt
set (ENTT_INCLUDE_DIR ${THIRD_PARTY_MODULE_PATH}/entt/src)

# -------------------------------------------------------------------------
# json
set (JSON_INCLUDE_DIR ${THIRD_PARTY_MODULE_PATH}/json/single_include)

# -------------------------------------------------------------------------
# physfs_cxx
# find_package (PhysFS REQUIRED)

# set (PHYSFS_CXX_INCLUDE_DIRS "${THIRD_PARTY_MODULE_PATH}/physfs_cxx/inc" "${PHYSFS_INCLUDE_DIR}")
# set (PHYSFS_CXX_LIBRARY "${PHYSFS_LIBRARY}")
# -------------------------------------------------------------------------
# sdl2_cxx
set (SDL2_CXX_MODULE_PATH "${THIRD_PARTY_MODULE_PATH}/sdl2_cxx")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${SDL2_CXX_MODULE_PATH}/cmake")
# include (FindSDL2)
# find_package (SDL2 REQUIRED)
# set (SDL2_CXX_INCLUDE_DIRS "${SDL2_CXX_INCLUDE_DIRS}" "${SDL2_INCLUDE_DIR}")

# include ("FindSDL2_image")
# find_package (SDL2_image REQUIRED)

# include ("FindSDL2_mixer")
# find_package (SDL2_mixer REQUIRED)

# include ("FindSDL2_net")
# find_package (SDL2_net REQUIRED)

# include ("FindSDL2_ttf")
# find_package (SDL2_ttf REQUIRED)

# set (SDL2_CXX_INCLUDE_DIRS "${SDL2_CXX_MODULE_PATH}/inc" "${SDL2_INCLUDE_DIR}" "${SDL2_IMAGE_INCLUDE_DIR}" "${SDL2_MIXER_INCLUDE_DIR}" "${SDL2_NET_INCLUDE_DIR}" "${SDL2_TTF_INCLUDE_DIR}")
# set (SDL2_CXX_LIBRARIES "${SDL2_LIBRARY}" "${SDL2_IMAGE_LIBRARY}" "${SDL2_MIXER_LIBRARY}" "${SDL2_NET_LIBRARY}" "${SDL2_TTF_LIBRARY}")
# -------------------------------------------------------------------------
# sol
set (SOL_CXX_INCLUDE_DIR ${THIRD_PARTY_MODULE_PATH}/sol2/single)

# -------------------------------------------------------------------------
# tinyformat
set (TINYFORMAT_INCLUDE_DIR ${THIRD_PARTY_MODULE_PATH}/tinyformat)


set (THIRD_PARTY_INCLUDE_DIRS  "${ENTT_INCLUDE_DIR}" "${JSON_INCLUDE_DIR}" "${PHYSFS_CXX_INCLUDE_DIRS}" "${SDL2_CXX_INCLUDE_DIRS}" "${SOL_CXX_INCLUDE_DIR}" "${TINYFORMAT_INCLUDE_DIR}")
set (THIRD_PARTY_INCLUDE_DIRS  ${THIRD_PARTY_INCLUDE_DIRS} PARENT_SCOPE)

set (THIRD_PARTY_LIBRARIES  "${PHYSFS_CXX_LIBRARY}" "${SDL2_CXX_LIBRARIES}")
set (THIRD_PARTY_LIBRARIES  ${THIRD_PARTY_LIBRARIES} PARENT_SCOPE)