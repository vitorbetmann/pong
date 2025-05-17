#include <raylib.h>
#include <stdio.h>
#include <inttypes.h>

int main(void)
{
    const int WINDOW_WIDTH = 1280;
    const int WINDOW_HEIGHT = 720;

    SetConfigFlags(FLAG_FULLSCREEN_MODE | FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_HIGHDPI);
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Pong");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        char *greeting = "Hello Pong!";
        ClearBackground(BLACK);
        DrawText(greeting, (WINDOW_WIDTH - TextLength(greeting)) / 2, WINDOW_HEIGHT / 2, 12, WHITE);
        EndDrawing();
    }
}
