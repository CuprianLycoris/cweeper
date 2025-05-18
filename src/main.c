#include <stdlib.h>
#include <time.h>
#include "raylib.h"

typedef enum {
    TILE_CLOSE,
    TILE_OPEN,
    TILE_FLAG
} TileState;

typedef struct {
    bool isMine;
    TileState state;
} Tile;

#define GRID_SIZE 16
#define TILE_SIZE 30
#define WIDTH GRID_SIZE * TILE_SIZE
#define HEIGHT GRID_SIZE * TILE_SIZE

int main(void) {
    srand((unsigned int)time(NULL));
    InitWindow(WIDTH, HEIGHT, "cweeper");
    Tile grid[GRID_SIZE][GRID_SIZE] = {0};

    for (int i = 0; i < GRID_SIZE; i++)
        for (int j = 0; j < GRID_SIZE; j++)
            grid[i][j].state = rand() % 2;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);


        for (int i = 0; i < GRID_SIZE; i++) {
            for (int j = 0; j < GRID_SIZE; j++) {
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
                DrawRectangle(i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE, TILE_SIZE, color);
                DrawRectangleLines(i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE, TILE_SIZE, BLACK);
            }
        }
        
        
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
