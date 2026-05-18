# =============================================================================
# tcxJuliaCxxWrap - TrussC Julia CxxWrap.jl binding generator
# =============================================================================

cmake_minimum_required(VERSION 3.16)
# cmake_policy(SET CMP0077 NEW)

find_package(JlCxx)
get_target_property(JlCxx_location JlCxx::cxxwrap_julia LOCATION)
get_filename_component(JlCxx_location ${JlCxx_location} DIRECTORY)
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib;${JlCxx_location}")

message(STATUS "Found JlCxx at ${JlCxx_location}")

set(ADDON_NAME tcxZZJuliaCxxWrap)
set(SHARED_LIB_NAME JlTrussC)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set_property(TARGET snappy PROPERTY POSITION_INDEPENDENT_CODE TRUE)
set_property(TARGET tcxHap PROPERTY POSITION_INDEPENDENT_CODE TRUE)
set_property(TARGET tcxOsc PROPERTY POSITION_INDEPENDENT_CODE TRUE)

# file(GLOB ADDON_INCLUDE_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)
file(GLOB ADDON_SOURCES_FOR_SHARED ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB ADDON_SOURCES_GENERATED ${CMAKE_CURRENT_SOURCE_DIR}/src/generated/*.cpp)
file(GLOB ADDON_HEADERS_FOR_SHARED ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h)
file(GLOB ADDON_HEADERS_GENERATED ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h)

# NOTE: this is dummy sources for compilation
file(GLOB ADDON_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/src_dummy/*.h)
file(GLOB ADDON_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src_dummy/*.cpp)

# NOTE: this lib is dummy for compilation
add_library(${ADDON_NAME} STATIC
    ${ADDON_SOURCES}
    ${ADDON_HEADERS}
)

add_library(${SHARED_LIB_NAME} SHARED
    ${ADDON_SOURCES_FOR_SHARED}
    ${ADDON_SOURCES_GENERATED}
    ${ADDON_HEADERS_FOR_SHARED}
    ${ADDON_HEADERS_GENERATED}
)

# target_compile_definitions(${SHARED_LIB_NAME} PRIVATE A=1 B=1)
target_include_directories(${SHARED_LIB_NAME} PUBLIC
    # ${CMAKE_CURRENT_SOURCE_DIR}/other/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/generated
)

if(WIN32 AND MSVC)
    # MSVC on Windows: enable large object support to avoid
    # "too many sections" (/bigobj)
    target_compile_options(${SHARED_LIB_NAME} PRIVATE /bigobj)
endif()

target_link_libraries(${ADDON_NAME} PUBLIC TrussC)
target_link_libraries(${SHARED_LIB_NAME} PUBLIC TrussC tcxHap tcxOsc tcxObj tcxGltf JlCxx::cxxwrap_julia JlCxx::cxxwrap_julia_stl)