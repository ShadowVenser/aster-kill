set(TARGET_NAME aster_killer)
set(SOURCES main.cpp
        Sample/Systems/MovementSystem.cpp
        Sample/Systems/MovementSystem.h
        Sample/Systems/InitSystem.cpp
        Sample/Systems/InitSystem.h
        Sample/Systems/InputSystem.cpp
        Sample/Systems/InputSystem.h

        Sample/Systems/KillerSystem.cpp
        Sample/Systems/CleanerSystem.cpp
        Sample/Systems/RenderSystem.cpp
        Sample/Systems/SpawnSystem.cpp
        Sample/Systems/MoveEventSystem.cpp
        Sample/Systems/CollisionDetectionSystem.cpp
        Sample/Systems/EndGameSystem.cpp
        Sample/Systems/ShootingSystem.cpp
        Sample/Systems/HitSystem.cpp

        Sample/Components/PositionComponent.h
        Sample/Components/MovementComponent.h

        Objects/Config.cpp
        Objects/Drawer.cpp
        Objects/Randomiser.cpp
        Objects/Timer.cpp
        Objects/Gui.cpp
)

add_subdirectory(Ecs)

add_executable(${TARGET_NAME} 
    ${SOURCES})

target_compile_options(${TARGET_NAME} PRIVATE -Wall -Wextra -Wpedantic -Werror)
# target_compile_options(${TARGET_NAME} PRIVATE -g3 -O0)
target_compile_options(${TARGET_NAME} PRIVATE -Ofast)

target_compile_features(${TARGET_NAME} PRIVATE cxx_std_20)

target_link_libraries(${TARGET_NAME} PUBLIC ${ECS_LIB_NAME})
target_link_libraries(${TARGET_NAME} PUBLIC ImGui-SFML::ImGui-SFML)
target_link_libraries(${TARGET_NAME} PUBLIC nlohmann_json::nlohmann_json)