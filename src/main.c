// TODO: Line 43: Is SetTargetFPS() a good thing to use?

#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

// Defines
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define V_WINDOW_WIDTH 432
#define V_WINDOW_HEIGHT 243
#define FONTSIZE 12
#define PADDLE_WIDTH 5
#define PADDLE_HEIGHT 20
#define BALLSIZE 4

// Variables
RenderTexture2D vScreen;
Font font;

// Prototypes
void GameInit();
void GameRun();
void DrawAll();
void DrawOnVScreen();
void DrawPaddle(int posX, int posY);
void DrawBall();
void DrawGreeting();
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

    BeginTextureMode(vScreen);
    DrawPaddle(10, 30);
    DrawPaddle(V_WINDOW_WIDTH - 10, V_WINDOW_HEIGHT - 50);
    DrawBall();
    DrawGreeting();
    EndTextureMode();
}

void DrawPaddle(int posX, int posY)
{
    DrawRectangle(posX, posY, PADDLE_WIDTH, PADDLE_HEIGHT, WHITE);
}

void DrawBall()
{
    DrawRectangle((V_WINDOW_WIDTH - BALLSIZE) / 2, (V_WINDOW_HEIGHT - BALLSIZE) / 2, BALLSIZE, BALLSIZE, WHITE);
}

void DrawGreeting()
{
    char *greeting = "Hello Pong!";
    Vector2 textWidth = MeasureTextEx(font, greeting, FONTSIZE, 2);
    Vector2 textPosition = (Vector2){(V_WINDOW_WIDTH - textWidth.x) / 2,
                                     (V_WINDOW_HEIGHT - textWidth.y) * 0.06f};
    ClearBackground((Color){40, 45, 52, 255});
    DrawTextEx(font, greeting, textPosition, FONTSIZE, 2, WHITE);
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
    UnloadRenderTexture(vScreen);
    UnloadFont(font);
    CloseWindow();
}