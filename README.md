Match-3
=======

Match 3 Game (match3.c) This repository contains match3.c, a simple Match-3 puzzle game implemented in C using the raylib library.

About the Game Match-3 games are a popular genre of puzzle video games where players manipulate game pieces on a grid in order to make a match of three or more identical pieces. When a match is found, the pieces are removed, and new pieces typically fall into place, often leading to cascades of further matches.

match3.c provides a basic implementation of this classic game, showcasing the capabilities of raylib for game development in C.

Features (Basic) Grid-based gameplay

Swapping of adjacent game pieces

Detection and removal of matches (three or more identical pieces in a row or column)

Basic visual feedback

Prerequisites To compile and run this game, you will need:

A C compiler (e.g., GCC, Clang)

The raylib library installed on your system.

Building and Running Install raylib: If you don't have raylib installed, please follow the instructions on the official raylib GitHub page or website to set it up for your operating system.

Compile the game: Navigate to the directory containing match3.c in your terminal and compile it using a command similar to this (adjust paths as necessary for your raylib installation):

gcc match3.c -o match3 -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

\-o match3: Specifies the output executable name as match3.

\-lraylib: Links the raylib library.

\-lGL -lm -lpthread -ldl -lrt -lX11: These are common additional libraries required by raylib on Linux systems. On other OS, these might differ or not be needed.

Run the game: After successful compilation, run the executable:

./match3

Credits This game is built with the fantastic raylib library.

raylib is a simple and easy-to-use library to enjoy videogames programming. Credit to raylib for the library: [https://github.com/raysan5/raylib](https://github.com/raysan5/raylib)
