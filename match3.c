#include <stdlib.h>
#include "raylib.h"
#include <time.h>
#include <stdbool.h>
#include <math.h>
#include <stdio.h>

#define BORAD_SIZE 8
#define TILE_SIZE 42
#define TILE_TYPES 5

const char tile_chars[TILE_TYPES] ={'@','#','$','&','%'};
char board[BORAD_SIZE][BORAD_SIZE];
Vector2 grid_origin;
Texture2D background;

char randon_tile(){
    return tile_chars[rand() % TILE_TYPES];
}

void init_board(){
    for(int y =0;y<BORAD_SIZE;y++){
        for (int  x=0;x<BORAD_SIZE;x++){
            board[y][x]= randon_tile();
        }
    }

    int grid_width = BORAD_SIZE * TILE_SIZE;
    int grid_height = BORAD_SIZE * TILE_SIZE;

    grid_origin = (Vector2){
        (GetScreenWidth()- grid_width) /2,
        (GetScreenHeight() - grid_height)/2

    };
}

int main(void){
    const int screen_width =800;
    const int screen_height =450;

    InitWindow(screen_width,screen_height,"Match C3");
    SetTargetFPS(60);
    srand(time(NULL));

    background= LoadTexture("assects/background.jgp");

    init_board();
    printf("Game started!\n");

    while (!WindowShouldClose){

        // Game Logic

        BeginDrawing();
        ClearBackground(BLACK);

        DrawTexturePro(
            background,(Rectangle){0,0,background.width,background.height},
            (Rectangle){0,0,GetScreenWidth(),GetScreenHeight()},
            (Vector2) {0,0},
            0.0f,
            WHITE
        );
        
        for(int y =0;y<BORAD_SIZE;y++){
        for (int  x=0;x<BORAD_SIZE;x++){
            Rectangle rect = {

                grid_origin.x + (x * TILE_SIZE),
                grid_origin.y + (y * TILE_SIZE),
                TILE_SIZE,
                TILE_SIZE

            };

            DrawRectangleLinesEx(rect,1,DARKGRAY);

            DrawTextEx(
                GetFontDefault(),
						TextFormat("%c", board[y][x]),
						(Vector2) {
							rect.x + 12,
							rect.y + 8 
						},
						20,
						1, WHITE
            );
        }
    }

        EndDrawing();

    }
UnloadTexture(background);

    CloseWindow();

    return 0;
}