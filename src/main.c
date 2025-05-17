// TODO: Draw Paddles and Ball
// TODO: Line 43: Is SetTargetFPS() a good thing to use?

#include <raylib.h>

// Defines
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define V_WINDOW_WIDTH 432
#define V_WINDOW_HEIGHT 243
#define FONTSIZE 12

// Variables
RenderTexture2D vScreen;
Font font;

// Variables
RenderTexture2D vScreen;
Font font;

// Prototypes
void GameInit();
void GameRun();
void DrawAll();
void DrawOnVScreen();
void DrawOnWindow();
void GameUnload();
void GameInit();
void GameRun();
void DrawAll();
void DrawOnVScreen();
void DrawOnWindow();
void GameUnload();

int main(void)
{
    GameInit();
    GameRun();
    GameUnload();
    return 0;
}

void GameInit()
{
    SetConfigFlags(
        FLAG_FULLSCREEN_MODE |
        FLAG_VSYNC_HINT |
        FLAG_WINDOW_RESIZABLE);
    GameInit();
    GameRun();
    GameUnload();
    return 0;
}

void GameInit()
{
    SetConfigFlags(
        FLAG_FULLSCREEN_MODE |
        FLAG_VSYNC_HINT |
        FLAG_WINDOW_RESIZABLE);
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Pong");
    vScreen = LoadRenderTexture(V_WINDOW_WIDTH, V_WINDOW_HEIGHT);
    font = LoadFont("../assets/pong_font.ttf");
    SetTextureFilter(font.texture, TEXTURE_FILTER_POINT);
    SetTargetFPS(60);
}

void GameRun()
{
    while (!WindowShouldClose())
    {
        DrawAll();
    }
}

void DrawAll()
{
    DrawOnVScreen();
    DrawOnWindow();
}

void DrawOnVScreen()
{

    char *greeting = "Hello Pong!";
    Vector2 textWidth = MeasureTextEx(font, greeting, FONTSIZE, 2);
    Vector2 textPosition = (Vector2){(V_WINDOW_WIDTH - textWidth.x) / 2,
                                     (V_WINDOW_HEIGHT - textWidth.y) / 2};
    BeginTextureMode(vScreen);
    ClearBackground((Color){40, 45, 52, 255});
    DrawTextEx(font, greeting, textPosition, FONTSIZE, 2, WHITE);
    EndTextureMode();
}
DrawAll();
}
}

void DrawAll()
{
    DrawOnVScreen();
    DrawOnWindow();
}

void DrawOnVScreen()
{

    char *greeting = "Hello Pong!";
    Vector2 textWidth = MeasureTextEx(font, greeting, FONTSIZE, 2);
    Vector2 textPosition = (Vector2){(V_WINDOW_WIDTH - textWidth.x) / 2,
                                     (V_WINDOW_HEIGHT - textWidth.y) / 2};
    BeginTextureMode(vScreen);
    ClearBackground((Color){40, 45, 52, 255});
    DrawTextEx(font, greeting, textPosition, FONTSIZE, 2, WHITE);
    EndTextureMode();
}

void DrawOnWindow()
{
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
void DrawOnWindow()
{
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

void GameUnload()
{
    void GameUnload()
    {
        UnloadRenderTexture(vScreen);
        UnloadFont(font);
        UnloadFont(font);
        CloseWindow();
    }