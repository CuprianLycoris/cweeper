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

int main(void) {
    InitWindow(800, 600, "gay sex");
    Tile grid[GRID_SIZE][GRID_SIZE] = {0};

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RED);
        
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
