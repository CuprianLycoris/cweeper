#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "raylib.h"

typedef enum {
    TILE_CLOSE,
    TILE_OPEN,
    TILE_FLAG
} TileState;

typedef struct {
    bool isMine;
    int mineNbors;
    TileState state;
} Tile;

// Define game properties
#define GRID_SIZE 16
#define TILE_SIZE 30
#define WIDTH GRID_SIZE * TILE_SIZE
#define HEIGHT GRID_SIZE * TILE_SIZE
#define MINE_COUNT 40
#define off 0

// Empty the playing field
Tile grid[GRID_SIZE][GRID_SIZE] = {0};
bool firstClick = true;

bool gameLoop(void);
void drawTile(Tile* t, int posX, int posY, bool isHovered);
void updateTile(Tile* t, int posX, int posY, int mPosX, int mPosY, bool isLeftPressed, bool isRightPressed, bool isHovered);
void openTile(int i, int j);
void countNbors(void);
void generateGrid(void);

int main(void) {
    srand((unsigned int)time(NULL));
    generateGrid();
    
    bool jack = off;
    int currentJack = 0;
    float jackTimeDur = 0;
    
    InitAudioDevice();
    InitWindow(WIDTH, HEIGHT, "minecweeper");
    
    Texture2D jackTextures[2] = {0};
    jackTextures[0] = LoadTexture("./assets/jack0.png");
    jackTextures[1] = LoadTexture("./assets/jack1.png");
    Music jackMusic = LoadMusicStream("./assets/JackTheKiller.mp3");
    jackMusic.looping = true;

    SetTargetFPS(144);
    while (!WindowShouldClose()) {
        BeginDrawing();
        if (!jack){
            // In game
            if (!gameLoop()) {
                jack = true;
                PlayMusicStream(jackMusic);
            }
        } else {
            UpdateMusicStream(jackMusic);
            // Lost
            if (jackTimeDur >= 0.1f) {
                jackTimeDur = 0.0f;
                currentJack = (currentJack + 1) % 2;
            } else {
                jackTimeDur += GetFrameTime();
            }
            DrawTexturePro(jackTextures[currentJack], (Rectangle) {
                .x = 0,
                .y = 0,
                .width = jackTextures[currentJack].width,
                .height = jackTextures[currentJack].height
            }, (Rectangle) {.x = 0, .y = 0, .width = WIDTH, .height = HEIGHT}, (Vector2) {.x = 0, .y = 0}, 0, WHITE);
        }
        EndDrawing();
    }

    UnloadMusicStream(jackMusic);
    UnloadTexture(jackTextures[0]);
    UnloadTexture(jackTextures[1]);
    CloseAudioDevice();
    CloseWindow();
    return 0;
}

bool gameLoop(void) {
    ClearBackground(BLACK);
    Vector2 mPos = GetMousePosition();
    int mPosX = mPos.x;
    int mPosY = mPos.y;
    bool isLeftPressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
    bool isRightPressed = IsMouseButtonPressed(MOUSE_BUTTON_RIGHT);

    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            Tile* t = &grid[i][j];
            int posX = i * TILE_SIZE;
            int posY = j * TILE_SIZE;
            bool isHovered = mPosX >= posX && mPosX < posX + TILE_SIZE && mPosY >= posY && mPosY < posY + TILE_SIZE;
            if (isHovered && isLeftPressed) {
                while (firstClick) {
                    if (t->mineNbors == 0) {
                        firstClick = false;
                    } else {
                        generateGrid();
                    }
                }
                if (t->isMine) {
                    return false;
                } else {
                    openTile(i, j);
                }
            }
            updateTile(t, posX, posY, mPosX, mPosY, isLeftPressed, isRightPressed, isHovered);
            drawTile(t, posX, posY, isHovered);
        }
    }
    return true;
}

void updateTile(Tile* t, int posX, int posY, int mPosX, int mPosY, bool isLeftPressed, bool isRightPressed, bool isHovered) {
    
    if(isHovered) {
        if (isRightPressed){
            if (t->state == TILE_CLOSE)
                t->state = TILE_FLAG;
            else if (t->state == TILE_FLAG)
                t->state = TILE_CLOSE;
        }
    }
}

void drawTile(Tile* t, int posX, int posY, bool isHovered) {
    Color color = BLACK;
    switch (t->state) {
    case TILE_CLOSE:
        color = WHITE;
        break;
    case TILE_OPEN:
        color = ORANGE;
        break;
    case TILE_FLAG:
        color = GREEN;
        break;
    }
    #if 0 //if you want to display the mines
        if (t->isMine) {
            color = ORANGE;
        } else {
            color = WHITE;
        }

        if (isHovered) {
            color = RED;
        }
    #endif
    
     
    DrawRectangle(posX, posY, TILE_SIZE, TILE_SIZE, color);
    DrawRectangleLines(posX, posY, TILE_SIZE, TILE_SIZE, BLACK);
    if (t->mineNbors > 0) {
        char c[2];
        if (t->state == TILE_OPEN && !t->isMine) {
            sprintf(c, "%d", t->mineNbors);
            DrawText(c, posX, posY, 15, BLACK);
        }
        
    }
}

void openTile(int i, int j) {
    if (!grid[i][j].isMine) {
        grid[i][j].state = TILE_OPEN;
    }
    if (grid[i][j].mineNbors == 0 && !grid[i][j].isMine) {
        for (int k = i - 1; k < i + 2; k++)
            for (int l = j - 1; l < j + 2; l++)
                if (!(k == i && l == j))
                    if((k >= 0 && k < GRID_SIZE) && (l >= 0 && l < GRID_SIZE))
                        if (grid[k][l].state != TILE_OPEN)
                            openTile(k, l);
    }    
}

void countNbors(void) {
  for (int i = 0; i < GRID_SIZE; i++) 
        for (int j = 0; j < GRID_SIZE; j++){
            grid[i][j].mineNbors = 0;
            if(!grid[i][j].isMine) {
                for (int k = i - 1; k < i + 2; k++)
                    for (int l = j - 1; l < j + 2; l++)
                        if((k >= 0 && k < GRID_SIZE) && (l >= 0 && l < GRID_SIZE))
                            if(grid[k][l].isMine)
                                grid[i][j].mineNbors++;
            } else {
                grid[i][j].mineNbors = 1;
            }
        }
}

void generateGrid(void) {
    bool permutuationArray[GRID_SIZE * GRID_SIZE] = {0};
    for (int i = 0; i < MINE_COUNT; i++){
        permutuationArray[i] = 1;
    }
    for (unsigned int shuffle = 0; shuffle < GRID_SIZE * GRID_SIZE; shuffle++){
        int random = rand() % (GRID_SIZE * GRID_SIZE);
        int random2 = rand() % (GRID_SIZE * GRID_SIZE);
        bool tmp = 0;
        tmp = permutuationArray[random];
        permutuationArray[random] = permutuationArray[random2];
        permutuationArray[random2] = tmp;
    }

    // Prepare the game area
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++){
            grid[i][j].isMine = permutuationArray[i * GRID_SIZE + j];    
        }
    }
    countNbors();
    
}
