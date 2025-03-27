# Tetris-game
This repository is about the the working tetris game in the compiler
# Tetris Game in C++

## Overview
This project is a console-based implementation of the classic Tetris game using C++. The game includes core mechanics such as falling tetrominoes, line clearing, scoring, and game-over conditions.

## Features
- **Tetromino Pieces:** All seven standard tetrominoes (I, O, T, S, Z, J, L) are implemented.
- **Grid Representation:** The game board is a 10x20 grid.
- **Piece Movement:** Players can move pieces left, right, rotate them, and drop them.
- **Gravity:** Tetrominoes fall at a constant speed, increasing as the game progresses.
- **Collision Detection:** Prevents blocks from overlapping or moving out of bounds.
- **Line Clearing:** Removes full rows and shifts the grid downward.
- **Scoring System:** Awards points for cleared lines.
- **Game Progression:** Falling speed increases after clearing a certain number of lines.
- **Game Over Detection:** The game ends when blocks reach the top of the grid.

## Controls
- **Left Arrow (←):** Move left
- **Right Arrow (→):** Move right
- **Up Arrow (↑):** Rotate piece
- **Down Arrow (↓):** Soft drop
- **Spacebar:** Hard drop
- **Escape (ESC):** Pause or Quit

## Technical Requirements
- Written in **C++ (C++17 or later recommended)**
- Uses **Object-Oriented Programming (OOP)** principles
- Implements **real-time user input handling**
- Uses **2D arrays or vectors** for grid representation
- Efficient collision detection and game logic management

## Installation & Execution
1. Clone the repository:
   ```sh
   git clone <repository_url>
   ```
2. Navigate to the project directory:
   ```sh
   cd tetris-game
   ```
3. Compile the program:
   ```sh
   g++ -o tetris main.cpp -std=c++17
   ```
4. Run the executable:
   ```sh
   ./tetris
   ```

## Submission Requirements
- **Source Code:** Properly commented
- **Executable File:** For easy testing
- **README.md:** Explains game controls and implementation details
- **(Optional) Demo Video:** Showcasing gameplay

## References
- [Tetris - Wikipedia](https://en.wikipedia.org/wiki/Tetris)
- [Tint - Tetris Clone](https://github.com/DavidGriffith/tint)



---
This project is part of a learning exercise. Feel free to improve and extend the functionality!
