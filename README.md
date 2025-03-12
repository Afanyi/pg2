# Dungeon Crawler - Agile Project

## Table of Contents
1. [Project Overview](#project-overview)
2. [Features](#features)
3. [Technologies Used](#technologies-used)
4. [Installation](#installation)
5. [Usage](#usage)
6. [Game Mechanics](#game-mechanics)
7. [Development Roadmap](#development-roadmap)
8. [File Structure](#file-structure)
9. [Contributors](#contributors)

---

## Project Overview
The **Dungeon Crawler** is an agile-based game project developed in multiple iterations from praktikum 2 to praktikum 6 with raktikum2 and 3 terminal based nad the following GUI based. The game follows a **turn-based movement system**, where the player navigates through a dungeon filled with interactive tiles, NPCs, items, and multiple levels. Initially implemented as a **terminal-based application**, it has been upgraded to a **graphical interface using Qt**.

The project focuses on **object-oriented design**, implementing inheritance, polymorphism, data structures, Dijkstra pathfinding, and file I/O.

## Features
- **Turn-based movement system**
- **Different tile types** (Walls, Floors, Portals, Switches, Doors, Pits, Ramps, Level Changers)
- **Graphical User Interface (Qt-based)**
- **Multiple levels with procedural generation support**
- **NPCs with AI (stationary, patrol, attack behavior)**
- **Inventory system with items and equipment**
- **Combat mechanics between player and NPCs**
- **Pathfinding algorithms (BFS, Dijkstra, A*)**
- **Game state saving and loading (text support)**

## Technologies Used
- **C++** (Game Logic)
- **Qt** (Graphical User Interface)
- **STL** (Data Structures)
- **Graph Algorithms** (Pathfinding)
- **JSON and text for Modern C++** (File I/O)

## Installation
To install and run the Dungeon Crawler, follow these steps:

1. **Clone the repository:**
   ```bash
   git clone https://github.com/Afanyi/pg2
   cd pg2
   ```

2. **Install dependencies:**
   - Ensure **C++20** support
   - Install **Qt 6+**

3. **Build the project:**
   ```bash
   mkdir build && cd build
   cmake ..
   make
   ```

## Usage
- **Arrow Keys :** Move the character
- **Enter:** Interact with objects
- **Esc:** Exit the game

For GUI mode:
- **Click on buttons** for movement and interactions

## Game Mechanics
### 1. Movement & Tiles
- Characters move in a turn-based system, interacting with different **Tile** types:
  - **Floor:** Walkable tile
  - **Wall:** Non-walkable barrier
  - **Portal:** Teleports to another location
  - **Switch & Door:** Interactive elements
  - **Pit & Ramp:** Special movement restrictions
  - **Level Changer:** Moves player between levels

### 2. Combat System
- Players and NPCs engage in combat when occupying the same tile
- **Attributes:** Strength, Stamina, HP
- **NPC Behaviors:** Stationary, Guard Patrol, Attacker (follows player)

### 3. Inventory & Items
- **Weapons:** Increases strength
- **Armor:** Increases stamina & HP
- **Consumables:** Potions restore health

### 4. AI Pathfinding
- NPCs use **Breadth-First Search (BFS)** or **Dijkstra’s Algorithm** for pathfinding
- Attack NPCs track players across levels

### 5. Saving & Loading
- Game state is stored in **text format**
- Supports **manual saving/loading**

## Development Roadmap
### Completed Milestones
✅ Implemented basic movement & game loop (Terminal-based)  
✅ Introduced multiple tile types  
✅ Added GUI with Qt  
✅ Integrated AI-driven NPCs  
✅ Developed inventory system  
✅ Implemented file I/O (TEXT)  


For any issues, contact [afanyiblasius4@gmail.com] or open an issue in the repository!

