#include <raylib.h>

// Defines
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define TARGET_FPS 60
#define V_WIDTH 432
#define V_HEIGHT 243
#define FONTSIZE 12
#define PADDLE_WIDTH 5
#define PADDLE_HEIGHT 20
#define PADDLE_SPEED 200
#define BALLSIZE 4

// Data Types
typedef enum
{
    PLAYER_1,
    PLAYER_2,
} PlayerNumber;

// Variables
RenderTexture2D vScreen;
Font font;
float dt;
int p1Score, p2Score;
int player1Y = 30, player2Y = V_HEIGHT - 50;
const int PLAYER_1_X = 10, PLAYER_2_X = V_WIDTH - 10;

// Prototypes
void GameInit();
void GameRun();
void UpdateAll();
void UpdatePaddle(PlayerNumber playerNum);
void UpdateBall();
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

// Functions
void GameInit()
{
    SetConfigFlags(
        FLAG_FULLSCREEN_MODE |
        FLAG_VSYNC_HINT |
        FLAG_WINDOW_RESIZABLE);
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Pong");
    vScreen = LoadRenderTexture(V_WIDTH, V_HEIGHT);
    font = LoadFont("../assets/pong_font.ttf");
    SetTextureFilter(font.texture, TEXTURE_FILTER_POINT);
    SetTargetFPS(TARGET_FPS);
}

void GameRun()
{
    while (!WindowShouldClose())
    {
        UpdateAll();
        DrawAll();
    }
}

void UpdateAll()
{
    dt = GetFrameTime();
    UpdatePaddle(PLAYER_1);
    UpdatePaddle(PLAYER_2);
    UpdateBall();
}

void UpdatePaddle(PlayerNumber playerNum)
{
    switch (playerNum)
    {
    case PLAYER_1:
        if (IsKeyDown(KEY_W))
            player1Y -= PADDLE_SPEED * dt;
        else if (IsKeyDown(KEY_S))
            player1Y += PADDLE_SPEED * dt;
        return;
    case PLAYER_2:
        if (IsKeyDown(KEY_UP))
            player2Y -= PADDLE_SPEED * dt;
        else if (IsKeyDown(KEY_DOWN))
            player2Y += PADDLE_SPEED * dt;
        return;
    }
}

void UpdateBall()
{
}

void DrawAll()
{
    DrawOnVScreen();
    DrawOnWindow();
}

void DrawOnVScreen()
{
    BeginTextureMode(vScreen);
    DrawPaddle(PLAYER_1_X, player1Y);
    DrawPaddle(PLAYER_2_X, player2Y);
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
    DrawRectangle((V_WIDTH - BALLSIZE) / 2, (V_HEIGHT - BALLSIZE) / 2, BALLSIZE, BALLSIZE, WHITE);
}

void DrawGreeting()
{
    char *greeting = "Hello Pong!";
    Vector2 textWidth = MeasureTextEx(font, greeting, FONTSIZE, 2);
    Vector2 textPosition = (Vector2){(V_WIDTH - textWidth.x) / 2,
                                     (V_HEIGHT - textWidth.y) * 0.06f};
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