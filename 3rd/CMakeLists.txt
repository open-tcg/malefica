set(THIRD_PARTY_MODULE_PATH "${PROJECT_SOURCE_DIR}/3rd")
set(THIRD_PARTY_MODULE_PATH ${THIRD_PARTY_MODULE_PATH} PARENT_SCOPE)

# -------------------------------------------------------------------------
# physfs_cxx

find_package (PhysFS REQUIRED)
set (PHYSFS_CXX_INCLUDE_DIR ${THIRD_PARTY_MODULE_PATH}/physfs_cxx/inc ${PHYSFS_INCLUDE_DIR})
set (PHYSFS_CXX_INCLUDE_DIR ${PHYSFS_CXX_INCLUDE_DIR} PARENT_SCOPE)

# -------------------------------------------------------------------------
# spdlog
set (SPDLOG_INCLUDE_DIR ${THIRD_PARTY_MODULE_PATH}/spdlog/include)

# -------------------------------------------------------------------------
# tinyformat
set (TINYFORMAT_INCLUDE_DIR ${THIRD_PARTY_MODULE_PATH}/tinyformat)

set (THIRD_PARTY_INCLUDE_DIRS  ${SPDLOG_INCLUDE_DIR} ${PHYSFS_CXX_INCLUDE_DIR})
set (THIRD_PARTY_INCLUDE_DIRS  ${THIRD_PARTY_INCLUDE_DIRS} PARENT_SCOPE)

set (THIRD_PARTY_LIBRARIES  ${PHYSFS_LIBRARY})
set (THIRD_PARTY_LIBRARIES  ${THIRD_PARTY_LIBRARIES} PARENT_SCOPE)