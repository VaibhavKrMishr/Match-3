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
bool matched[BORAD_SIZE][BORAD_SIZE] ={0};
float fall_offset[BORAD_SIZE][BORAD_SIZE] ={0};

int score =00;

Vector2 grid_origin;
Texture2D background;
Vector2 selected_tile = {-1,-1};
float fall_speed =8.0f;
float match_delay_timer =0.0f;
const float match_delay_duration=0.3f;
Music background_music;
Sound match_sound;


typedef enum{
    State_Idle,
    State_Animating,
    state_match_delay
} TileState;

TileState tile_state;

char randon_tile(){
    return tile_chars[rand() % TILE_TYPES];
}

void swap_tiles(int x1,int y1,int x2,int y2){
    char temp = board[y1][x1];
    board[y1][x1]=board[y2][x2];
    board[y2][x2] =temp;
}

bool are_tiles_adjacent(Vector2 a, Vector2 b){
    return (abs((int)a.x - (int)b.x)+abs((int)a.y - (int)b.y))==1;
}

bool find_matches(){
    bool found = false;
    for (int y=0;y<BORAD_SIZE;y++){
        for (int x=0;x<BORAD_SIZE;x++){
            matched[y][x]=false;
        }
    }
    for (int y=0;y<BORAD_SIZE;y++){
        for (int x=0;x<BORAD_SIZE -2;x++){
            char t= board[y][x];
            if (t==board[y][x+1] &&
                t==board[y][x+2]){
                    matched[y][x] =matched[y][x+1]=matched[y][x+2]=true;
                //Update Score
                score+=10;
                found=true;
                }
        }
    }
    for (int x=0;x<BORAD_SIZE;x++){
        for (int y=0;y<BORAD_SIZE -2;y++){
            char t= board[y][x];
            if (t==board[y+1][x] &&
                t==board[y+2][x]){
                    matched[y][x] =matched[y+1][x]=matched[y+2][x]=true;
                //Update Score
                score+=10;
                found=true;
                }
        }
    }

    return found;

}

void resolve_matches(){
    for (int x=0;x<BORAD_SIZE;x++){
        int write_y=BORAD_SIZE-1;
        for(int y= BORAD_SIZE -1;y>=0;y--){
            if(!matched[y][x]){
                if(y!=write_y){
                    board[write_y][x]=board[y][x];
                    fall_offset[write_y][x]=(write_y -y) * TILE_SIZE;
                    board[y][x]=' ';
                }
                write_y--;
            }
        }

        while( write_y>=0){
            board[write_y][x]=randon_tile();
            fall_offset[write_y][x]=(write_y +1) * TILE_SIZE;
            write_y--;

        }
    }
    tile_state=State_Animating;
    
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

    if(find_matches()){
        resolve_matches();
    }
    else{
        tile_state=State_Idle;
    }
}

int main(void){
    const int screen_width =800;
    const int screen_height =450;

    InitWindow(screen_width,screen_height,"Match C3");
    SetTargetFPS(60);
    srand(time(NULL));

    InitAudioDevice();

    background= LoadTexture("assets/background.jpg");
    background_music = LoadMusicStream("assets/bgm.mp3");

    PlayMusicStream(background_music);

    init_board();
    printf("Game started!\n");
    Vector2 mouse ={0,0};

    while (!WindowShouldClose()){

        UpdateMusicStream(background_music);

        // Game Logic
        mouse = GetMousePosition();
        if (tile_state==State_Idle && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            int x = (mouse.x - grid_origin.x) / TILE_SIZE;
            int y = (mouse.y - grid_origin.y) / TILE_SIZE;
            if (x>=0 && x< BORAD_SIZE && y>= 0 && y<BORAD_SIZE){
                Vector2 current_tile =(Vector2){x,y};
                if(selected_tile.x<0){
                    selected_tile = current_tile;
                }
                else{
                    if(are_tiles_adjacent(selected_tile,current_tile)){
                        swap_tiles(selected_tile.x,selected_tile.y,current_tile.x,current_tile.y);
                                if(find_matches()){
                                    resolve_matches();
                                 }
                                 else{
                                    swap_tiles(selected_tile.x,selected_tile.y,current_tile.x,current_tile.y);
                                 }
                                 selected_tile= (Vector2){-1,-1};

                    }
                }
            }
        }
if(find_matches()){
            resolve_matches();
        }

        if(tile_state==State_Animating){
            bool still_animating =false;

        for(int y =0;y<BORAD_SIZE;y++){
            for (int x =0;x<BORAD_SIZE;x++){
                if(fall_offset[y][x]>0){
                    fall_offset[y][x]-=fall_speed;
                    if(fall_offset[y][x]<0){
                        fall_offset[y][x]=0;
                    }else{
                        still_animating=true;
                    }
                }
            }
        }
        if(!still_animating){
            tile_state=state_match_delay;
            match_delay_timer=match_delay_duration;
        }
        }
        if(tile_state==state_match_delay){
            match_delay_timer-=GetFrameTime();
            if (match_delay_timer<=0.0f){
                if(find_matches()){
                    resolve_matches();

                }
                else{
                    tile_state = State_Idle;
                }
            }
        }


        BeginDrawing();
        ClearBackground(BLACK);

        DrawTexturePro(
            background,(Rectangle){0,0,background.width,background.height},
            (Rectangle){0,0,GetScreenWidth(),GetScreenHeight()},
            (Vector2) {0,0},
            0.0f,
            WHITE
        );
        DrawRectangle(
            grid_origin.x,
            grid_origin.y,
            BORAD_SIZE * TILE_SIZE,
            BORAD_SIZE * TILE_SIZE,
            Fade(DARKGRAY,0.75f)
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

            if(board[y][x]!=' '){
            DrawTextEx(
                GetFontDefault(),
						TextFormat("%c", board[y][x]),
						(Vector2) {
							rect.x + 12,
							rect.y + 8 - fall_offset[y][x]
						},
						20,
						1, 
                        matched[y][x]?GREEN:WHITE
            );
        }
        }
    }
    // draw selected tiles
    if (selected_tile.x>=0){
        DrawRectangleLinesEx((Rectangle){
            grid_origin.x + (selected_tile.x * TILE_SIZE),
            grid_origin.y + (selected_tile.y * TILE_SIZE),
            TILE_SIZE, TILE_SIZE
        },2, YELLOW);
    }
        
        DrawText(TextFormat("Score: %d",score),20,20,24,RED);

        EndDrawing();

    }
    StopMusicStream(background_music);
    UnloadMusicStream(background_music);
    UnloadTexture(background);


    CloseAudioDevice();

    CloseWindow();

    return 0;
}