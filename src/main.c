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
void drawTile(Tile* t, int posX, int posY, bool isHovered);
void updateTile(Tile* t, int posX, int posY, int mPosX, int mPosY, bool isLeftPressed, bool isRightPressed, bool isHovered);
void countNbors(void);

int main(void) {
    srand((unsigned int)time(NULL));

    InitWindow(WIDTH, HEIGHT, "minecweeper");

    // Prepare the game area
    for (int i = 0; i < GRID_SIZE; i++)
        for (int j = 0; j < GRID_SIZE; j++)
            grid[i][j].isMine = rand() % 2;
            
    countNbors();

            
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
            updateTile(t, posX, posY, mPosX, mPosY, isLeftPressed, isRightPressed, isHovered);
            drawTile(t, posX, posY, isHovered);
        }
    } 
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

    if (isHovered) {
        color = RED;
    }
        
    DrawRectangle(posX, posY, TILE_SIZE, TILE_SIZE, color);
    DrawRectangleLines(posX, posY, TILE_SIZE, TILE_SIZE, BLACK);
    char c[2];
    if (t->state == TILE_OPEN && !t->isMine) {
        sprintf(c, "%d", t->mineNbors);
        DrawText(c, posX, posY, 15, BLACK);
    }
}

void countNbors(void) {
  for (int i = 0; i < GRID_SIZE; i++) 
        for (int j = 0; j < GRID_SIZE; j++) 
            if(!grid[i][j].isMine)
                for (int k = i - 1; k < i + 2; k++)
                    for (int l = j - 1; l < j + 2; l++)
                        if((k >= 0 && k < GRID_SIZE) && (l >= 0 && l < GRID_SIZE))
                            if(grid[k][l].isMine)
                                grid[i][j].mineNbors++;
}
