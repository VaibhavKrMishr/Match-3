# Match-3

**Match 3 Game (`match3.c`)**  
This repository contains `match3.c`, a simple Match-3 puzzle game implemented in C using the raylib library.

## About the Game

Match-3 games are a popular puzzle genre where players swap adjacent pieces to form lines of three or more identical pieces. Matches are removed, and new pieces fall to fill the gaps, often causing combos. This implementation uses raylib for rendering and input.

## Features

- Grid-based tile gameplay  
- Swapping adjacent tiles  
- Match detection (3+ in row or column)  
- Basic visual feedback

## Prerequisites

- C compiler (e.g., GCC or Clang)  
- raylib library installed ([Install Guide](https://github.com/raysan5/raylib))

## Building and Running

**1. Compile the game**  
Open terminal in the project folder and run:  
`gcc match3.c -o match3 -lraylib -lGL -lm -lpthread -ldl -lrt -lX11`  
⚠️ These flags are for Linux. Adjust them for Windows/macOS if needed.

**2. Run the game**  
`./match3`

## Credits
Kubbi - Up In My Jam as BGM
Built using [raylib](https://github.com/raysan5/raylib) — a simple and easy-to-use C library to enjoy videogame programming.
