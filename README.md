# Aster Kill

**Aster Kill** is a small asteroid-style arcade game written in **C++20** with **SFML 3**.

The project is built around a custom **Entity Component System** architecture and was created as a practical experiment with game loops, component storage, systems, collision handling, runtime configuration and simple debugging tools.

The player controls a spaceship, dodges falling asteroids and shoots them to gain score.

## Features

- Custom ECS implementation
- Component-based game object model
- System-based game logic
- Player movement and shooting
- Random asteroid spawning
- Box-circle collision detection
- Score system
- Game over state
- JSON-based configuration
- ImGui debug panel for runtime inspection and spawn tweaking
- CMake-based build

## Tech Stack

- **C++20**
- **CMake**
- **SFML 3**
- **Dear ImGui**
- **ImGui-SFML**
- **nlohmann/json**

## Gameplay

The goal is simple: survive as long as possible and destroy asteroids before they hit the player.

Asteroids have different sizes, collision radii and score values. Their speed, spawn position, direction and rotation are generated using configuration values from `config.json`.

## Controls

| Key | Action |
|---|---|
| `A` / `Left Arrow` | Move left |
| `D` / `Right Arrow` | Move right |
| `Space` | Shoot |
| `Esc` | Pause / unpause |
| `I` | Toggle debug GUI |

## Project Structure

```text
aster-kill/
├── assets/              # Textures, fonts and other game assets
├── dependencies/        # CMake dependency setup via FetchContent
├── src/
│   ├── Ecs/             # Custom ECS implementation
│   ├── Objects/         # Config, rendering, GUI, timers, randomizer
│   ├── Sample/          # Game components and systems
│   └── main.cpp         # Application entry point
├── config.json          # Main game configuration
├── full_config.json     # Extended configuration example
├── CMakeLists.txt
└── README.md
```

## ECS Overview

The project is built around a simple custom ECS approach.

Entities are lightweight identifiers.
Components store data such as position, movement, sprites, colliders, bullets, asteroids and player state.
Systems process entities that match the required component sets.

Main gameplay systems include:

- `InitSystem` — creates the initial player entity
- `InputSystem` — processes keyboard input and creates input events
- `MovementSystem` — updates positions and rotation
- `SpawnSystem` — creates asteroid entities
- `ShootingSystem` — creates bullet entities
- `CollisionDetectionSystem` — detects box-circle collisions
- `HitSystem` — handles collisions, score updates and entity removal
- `RenderSystem` — draws entities
- `EndGameSystem` — checks player death
- `CleanerSystem` — removes entities marked for deletion

## Configuration

Game parameters are stored in `config.json`.

Example configurable values:

- window size
- player speed and start position
- bullet speed and cooldown
- asteroid speed range
- asteroid spawn timing
- asteroid score values
- texture paths
- font path

This makes it possible to tweak gameplay without recompiling the project.

## Build

### Requirements

You need:

- C++20 compatible compiler
- CMake 3.31 or newer
- Git
- Linux, macOS or Windows environment with graphics support

Project dependencies are downloaded by CMake via `FetchContent`.

### Linux notes

On Linux, SFML needs system development libraries for window creation, graphics and input handling. Make sure X11-related development packages are installed before building the project.

For Fedora:

```bash
sudo dnf install \
  libX11-devel libXrandr-devel libXcursor-devel libXi-devel systemd-devel \
  mesa-libGL-devel freetype-devel
```

If CMake fails while configuring or building SFML on Linux, first check that the X11 development packages are installed.

### Build commands

```bash
git clone https://github.com/ShadowVenser/aster-kill.git
cd aster-kill

cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

### Run

```bash
./build/src/aster_killer
```

On Windows, the executable path may look like this:

```bash
build/src/Release/aster_killer.exe
```

## Notes

The project was made as a learning project focused on ECS architecture and game logic organization.
It is intentionally compact, but the codebase contains enough systems to demonstrate how entities, components, filters and systems interact in a real-time application.

## License

See [`LICENSE.md`](./LICENSE.md).