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
    InitWindow(WIDTH, HEIGHT, "cweeper");
    Tile grid[GRID_SIZE][GRID_SIZE] = {0};

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        for (int i = 0; i < GRID_SIZE; i++){
            for (int j = 0; j < GRID_SIZE; j++)
            {
                grid[10][6].state = TILE_OPEN;
                if (grid[i][j].state == TILE_CLOSE)
                {
                DrawRectangle(i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE, TILE_SIZE, WHITE);
                }
                else if (grid[i][j].state == TILE_OPEN)
                {
                    DrawRectangle(i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE, TILE_SIZE, ORANGE);
                }
            }
        }
        
        
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
