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
    src/core/StateManager.cpp

    src/game/Player.cpp
    src/game/Level.cpp
    src/game/LevelLoader.cpp
    src/game/GameSession.cpp

    src/rendering/LevelRenderer.cpp

    src/states/MainMenuState.cpp
    src/states/LevelSelectState.cpp
    src/states/GameplayState.cpp

    src/ui/Button.cpp
    src/ui/HUD.cpp
    src/ui/PauseMenu.cpp
    src/ui/ExitConfirmation.cpp
    src/ui/SavedGameDialog.cpp

    src/persistence/SaveManager.cpp
    src/persistence/ProgressManager.cpp
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