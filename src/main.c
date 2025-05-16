#include "raylib.h"

int main(void)
{
    InitWindow(800, 600, "Pong Test Window");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Pong is running!", 300, 280, 20, DARKGRAY);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}