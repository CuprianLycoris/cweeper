#include <stdio.h>
#include "raylib.h"
#include "ui.h"

int main() {
    InitWindow(800, 600, "gay sex");

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RED);
        DrawText("butt sex", 10, 100, 30, WHITE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
