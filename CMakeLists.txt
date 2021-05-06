cmake_minimum_required(VERSION 3.16.3)
project(Pokemon)

set(CMAKE_CXX_STANDARD 20)

set(
    SRC
    include/battle/State.hpp
    src/battle/State.cpp
    include/config/Time.hpp src/config/Time.cpp
    include/tilemap/Region.hpp src/tilemap/Region.cpp
    include/tilemap/Region.hpp src/tilemap/Region.cpp
        include/tilemap/Engine.hpp src/tilemap/Engine.cpp
    include/renderer/Region.hpp
        include/controller/Controller.hpp src/controller/Controller.cpp
    include/controller/KeyboardController.hpp src/controller/KeyboardController.cpp
        include/config/Math.hpp include/config/Assets.hpp src/tilemap/Layer.cpp include/tilemap/Layer.hpp src/tilemap/LayerOfTiles.cpp include/tilemap/LayerOfTiles.hpp include/config/Json.hpp src/tilemap/RegionLoader.cpp include/tilemap/RegionLoader.hpp include/common.hpp src/tilemap/Tileset.cpp include/tilemap/Tileset.hpp src/tilemap/TileType.cpp include/tilemap/TileType.hpp src/tilemap/systems/MovementSystem.cpp include/tilemap/systems/MovementSystem.hpp src/renderer/FPSCounter.cpp include/renderer/FPSCounter.hpp src/config/Interpolation.cpp include/config/Interpolation.hpp src/tilemap/systems/InteractionSystem.cpp include/tilemap/systems/InteractionSystem.hpp include/tilemap/Direction.hpp src/tilemap/Direction.cpp src/renderer/SceneManager.cpp include/renderer/SceneManager.hpp src/renderer/Scene.cpp include/renderer/Scene.hpp src/tilemap/TilemapScene.cpp include/tilemap/TilemapScene.hpp src/observer/Observer.cpp include/observer/Observer.hpp src/observer/Subject.cpp include/observer/Subject.hpp src/tilemap/System.cpp include/tilemap/System.hpp src/tilemap/systems/PlayerMovementSystem.cpp include/tilemap/systems/PlayerMovementSystem.hpp include/controller/Command.hpp src/ui/DialogScene.cpp include/ui/DialogScene.hpp include/pokemon/Pokemon.hpp src/pokemon/Pokemon.cpp include/pokemon/Move.hpp include/pokemon/Trainer.hpp include/pokemon/MoveSlot.hpp include/observer/LambdaObserver.hpp src/battle/BattleScene.cpp include/battle/BattleScene.hpp src/renderer/ImGuiObserver.cpp include/renderer/ImGui.hpp include/battle/BattleAI.hpp src/battle/RandomAI.cpp include/battle/RandomAI.hpp include/config/Algorithm.hpp src/pokemon/MoveSlot.cpp include/config/ECS.hpp src/ui/MenuWidget.cpp include/ui/MenuWidget.hpp
    include/tilemap/Property.hpp
    src/tilemap/Property.cpp
        include/config/Config.hpp
        src/config/Config.cpp
        src/controller/Command.cpp src/config/Iterator2D.cpp include/config/Iterator2D.hpp include/config/Debug.hpp src/config/Debug.cpp src/tilemap/LayerOfObjects.cpp include/tilemap/LayerOfObjects.hpp src/tilemap/TileRenderer.cpp include/tilemap/TileRenderer.hpp src/common.cpp src/battle/InitState.cpp include/battle/InitState.hpp src/battle/PrepareTurnState.cpp include/battle/PrepareTurnState.hpp)

set(LIBS sfml-graphics sfml-graphics sfml-window sfml-system GL)
add_executable(Pokemon src/main.cpp ${SRC})

target_include_directories(Pokemon PUBLIC include/)
target_include_directories(Pokemon PUBLIC thirdparty/json/single_include)
target_include_directories(Pokemon PUBLIC thirdparty/SFML-Math/include)
target_include_directories(Pokemon PUBLIC thirdparty/magic_enum/include)

target_link_libraries(Pokemon ${LIBS})

# Warnings

target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -Wall -Wpedantic -Wextra -Wall)

# fmt -------------------------------------

set(FMT_PATH thirdparty/fmt)
target_link_directories(Pokemon PRIVATE ${FMT_PATH}/build)
target_link_libraries(Pokemon fmt)
target_include_directories(Pokemon PRIVATE ${FMT_PATH}/include)

# TMXLite --------------------------------------

target_link_directories(Pokemon PRIVATE thirdparty/tmxlite/build)
target_link_libraries(Pokemon tmxlite)
target_include_directories(Pokemon PRIVATE thirdparty/tmxlite/tmxlite/include)

# EnTT -----------------------------------------

find_package(EnTT CONFIG REQUIRED)
target_link_libraries(Pokemon EnTT::EnTT)

# IMGUI -----------------------------------------

set(IMGUI_PATH thirdparty/imgui)
set(IMGUI_BACKEND opengl3)
file(
    GLOB
    IMGUI_SRC
    "${IMGUI_PATH}/*.h"
    "${IMGUI_PATH}/*.cpp"
)

target_sources(Pokemon PRIVATE "${IMGUI_SRC}")
target_include_directories(
    Pokemon
    PUBLIC
    "${IMGUI_PATH}"
    "${IMGUI_PATH}/backend"
)
