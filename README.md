# Hexxagon – C++ SFML Implementation
A C++ reconstruction of the classic DOS strategy game Hexxagon. This project focuses on implementing complex grid logic, board state management, and persistent data handling using the SFML (Simple and Fast Multimedia Library).

## 🚀 Key Features

Hexagonal Grid System: A custom-built 58-cell board layout with specific coordinate mapping.

Strategic Movement Mechanics: Supports two distinct move types based on distance:


Cloning: Occupying an adjacent cell creates a new piece.


Jumping: Moving two cells away relocates the original piece.


Capture Logic: Automatically converts all neighboring enemy pieces to the current player's color upon landing.

Local Multiplayer (PvP): A fully functional turn-based mode for two players.

Persistent Leaderboard: Saves and retrieves match results from a local data file (data.txt).

## 🛠️ Tech Stack
Language: C++

Graphics Library: SFML


Data Handling: Standard File I/O for score persistence 

## 🏗️ Architecture & Structure
The project follows an object-oriented approach to separate game logic from the user interface:

Board: Manages the core game loop, move validation, and win conditions.

Hexagon: Represents individual cells, handling their state (Empty, Red, or Green) and distance calculations.

Menu: Controls the application entry point and navigation between game modes.

Scores: Handles reading and displaying historical match data.

## 🧠 Technical Highlights

Distance-Based Logic: Movement is governed by Euclidean distance calculations to determine if a move is a "clone" or a "jump".


Dynamic UI Updates: Real-time score tracking and turn indicators rendered through SFML's text and shape modules.

State Management: Uses an enum class to strictly manage cell ownership and turn transitions.

## 🏃 How to Run
Ensure you have SFML installed and configured in your development environment.

Compile the source files using a C++ compiler (the project includes a main.cpp entry point).

Place the arial.ttf font file in the expected system path or update the path in the source code.

Launch the executable to open the main menu.

## ⏳ Future Improvements
Implementation of Player vs Computer (AI) mode.

Integration of a Save/Load system for ongoing matches.

Advanced map loading from external configuration files.
