#include <raylib.h>

// Defines
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define V_WINDOW_WIDTH 432
#define V_WINDOW_HEIGHT 243
#define FONTSIZE 12
// Prototypes
// Variables

int main(void)
{
    SetConfigFlags(FLAG_FULLSCREEN_MODE | FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Pong");
    RenderTexture2D vScreen = LoadRenderTexture(V_WINDOW_WIDTH, V_WINDOW_HEIGHT);
    SetTargetFPS(60);
    float scale = (float)WINDOW_WIDTH / V_WINDOW_WIDTH;

    while (!WindowShouldClose())
    {
        char *greeting = "Hello Pong!";
        int textWidth = MeasureText(greeting, FONTSIZE);
        BeginTextureMode(vScreen);
        ClearBackground(BLACK);
        DrawText(greeting, (V_WINDOW_WIDTH - textWidth) / 2, (V_WINDOW_HEIGHT - FONTSIZE) / 2, FONTSIZE, WHITE);
        EndTextureMode();

        BeginDrawing();
        DrawTexturePro(
            vScreen.texture,
            (Rectangle){0, 0, vScreen.texture.width, -vScreen.texture.height},
            (Rectangle){0, 0, WINDOW_WIDTH, WINDOW_HEIGHT},
            (Vector2){0, 0},
            0,
            WHITE);
        EndDrawing();
    }

    UnloadRenderTexture(vScreen);
    CloseWindow();
    return 0;
}
