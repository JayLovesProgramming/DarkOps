# HELL ENGINE

<!-- December 27 2023 -->
This codebase began as a CPU raycaster to explore the viability of a voxel based idea I had for global illumination. 
The voxel idea didn't work out in the end, the voxel grid caused lighting artefacts, but rewriting it to use a pointcloud did and here we are. 
This is now the new Hell Engine, the engine I'm writing to house a splitscreen roguelike/deathmatch survival horror game.
![Image](https://www.principiaprogrammatica.com/dump/githubthumb2.jpg)


### Controls
W: Walk Forward<br>
A: Walk Left<br>
S: Walk Backward<br>
D: Walk Right<br>
Left Mouse: Fire/Attack<br>
Space Bar:  Jump<br>
Mouse Wheel: Cycle Weapons<br>
E: Interact<br>
R: Reload<br>
Left Ctrl: Crouch<br>
F: Shotgun Melee
G: Toggle Fullscreen<br>
J: Respawn Dead Players
K: Respawn All Players
Z: Previous Render Mode<br>
X: Next Render Mode<br>
B: Cycle Debug Lines<br>
O: Reload Map<br>
V: Toggle Splitscreen Mode<br>
Y: Show Probes<br>
1-4: Switch Player Input<br>
-: Lower Camera<br>
+: Raise Camera<br>
`: Toggle Debug Text<br>
TAB: Toggle Editor<br>

### Editor Controls
F1: File Menu<br>
F2: Insert Menu<br>
Alt + Click: Rotate Camera<br>
Ctrl + Click: Pan Camera<br>
Mouse Wheel: Zoom Camera<br>
<br>

**WARNING: Editor is very much still a WIP!**

### Download

The .lib files are managed by LFS. Download via terminal:

```
git lfs install
git clone https://github.com/livinamuk/Hell2024.git
```

### Usage

Run in Release - PhysX runs like shit in Debug if you manage to get it even running...

<br>

## Features

### Client
- **Dear ImGUI (Not ImGUI)**: **✅ Implemented but need more features adding**  
  Integrated for immediate UI functionality, enabling rapid development and debugging.
  
- **Renderer**: **🔄 In Progress**  
  Building a flexible and efficient rendering pipeline to support various graphics APIs.
  
- **Sync Movement with V-Sync/FPS**: **🔄 In Progress**  
  Implementing synchronization techniques to ensure smooth movement and reduce screen tearing.
  
- **Input Handling**: **🔄 In Progress**  
  Creating a flexible input system to manage keyboard, mouse, and game controller inputs.

- **Audio**: **❌ Not Started**  
  Integrating audio systems for immersive sound design and dynamic audio effects.

- **ECS (Entity Component System)**: **❌ Not Started**  
  Planning to implement a robust ECS architecture for modular and efficient game object management.

- **Networking Client**: **❌ Not Started**  
  Developing a networking layer for online multiplayer capabilities.

- **Animation System**: **❌ Not Started**  
  Developing a system to handle character animations, blending, and transitions.

- **Physics Engine**: **❌ Not Started**  
  Implementing a physics engine for realistic collision detection and response.

- **Scripting Support**: **❌ Not Started**  
  Integrating scripting capabilities to allow for customizable game logic and behaviors (eg. Lua, C#, Javascript).

### Server
- **Server Component System**: **❌ Not Started**  
  Creating a scalable server-side architecture for managing game state and player interactions.

- **Networking Backend Server**: **❌ Not Started**  
  Setting up a reliable networking backend to handle client connections and game data.

- **Database Integration**: **❌ Not Started**  
  Implementing a database system to manage persistent game data, user accounts, and statistics.

- **Game State Management**: **❌ Not Started**  
  Developing a system for managing game states, including game sessions and player progress.

### Shared
- **Utils**: **🔄 In Progress**  
  Developing a collection of utility functions and classes to simplify common tasks.

- **Modular Architecture**: **🔄 In Progress**  
  Structuring the engine to support modular development, allowing for easy integration of plugins and extensions.

- **Asset System**: **❌ Not Started**  
  Implementing a comprehensive asset management system for efficient loading and handling of game resources.

- **Localization**: **❌ Not Started**  
  Planning to add support for multiple languages and regional settings for broader accessibility.

## Contribution
This project is currently a one-person endeavor, but I welcome contributions and collaboration! If you're interested in learning more about game engine development or would like to contribute to this game engine, please reach out to me via Discord: **@jw_uk**. Together, we can build a powerful game engine and share knowledge within the community.

## Roadmap
- Expand documentation for contributors, including setup instructions and coding guidelines.
- Establish a community forum or Discord channel for discussions, feedback, and sharing resources.
- Prioritize the implementation of the ECS and networking components to enable multiplayer support.
