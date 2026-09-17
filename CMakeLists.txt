cmake_minimum_required(VERSION 3.28)

project(DungeonEscape LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)

FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.1.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM
)

FetchContent_MakeAvailable(SFML)

add_executable(
    DungeonEscape

    src/main.cpp
    src/core/Game.cpp
)

target_include_directories(
    DungeonEscape
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(
    DungeonEscape
    PRIVATE
    cxx_std_20
)

target_link_libraries(
    DungeonEscape
    PRIVATE
    SFML::Graphics
)

set_property(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    PROPERTY VS_STARTUP_PROJECT DungeonEscape
)