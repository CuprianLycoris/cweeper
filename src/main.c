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

// Empty the playing field
Tile grid[GRID_SIZE][GRID_SIZE] = {0};

void gameLoop(void);
void throughArray(int i, int j, Vector2 mPos);

int main(void) {
    srand((unsigned int)time(NULL));

    InitWindow(WIDTH, HEIGHT, "cweeper");

    for (int i = 0; i < GRID_SIZE; i++)
        for (int j = 0; j < GRID_SIZE; j++)
            grid[i][j].state = rand() % 2;
            
    while (!WindowShouldClose()) {
        BeginDrawing();
        gameLoop();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}

void gameLoop(void) {
    ClearBackground(BLACK);
    Vector2 mPos = GetMousePosition();

    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            throughArray(i, j, mPos);
        }
    } 
}

void throughArray(int i, int j, Vector2 mPos) {
    Color color = BLACK;
        switch (grid[i][j].state) {
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

        int posX = i * TILE_SIZE;
        int posY = j * TILE_SIZE;
        int mPosX = mPos.x;
        int mPosY = mPos.y;

        if (mPosX >= posX && mPosX < posX + TILE_SIZE && mPosY >= posY && mPosY < posY + TILE_SIZE) {
            color = RED;
        }
        
        if(IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
            if (mPosX >= posX && mPosX < posX + TILE_SIZE && mPosY >= posY &&
                 mPosY < posY + TILE_SIZE && grid[i][j].state == TILE_CLOSE) {
                grid[i][j].state = TILE_FLAG;
        }
        }
        DrawRectangle(posX, posY, TILE_SIZE, TILE_SIZE, color);
        DrawRectangleLines(posX, posY, TILE_SIZE, TILE_SIZE, BLACK);
}