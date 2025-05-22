#include "Ball.h"
#include "Paddle.h"
#include "Settings.h"
#include <raylib.h>
#include <stdio.h>

// Data Types
typedef enum {
  START,
  PLAY,
} GameState;
typedef enum {
  PLAYER_1,
  PLAYER_2,
} PlayerNumber;

// Variables
GameState gameState;
Ball ball;
Paddle paddle1 = {10, 30};
Paddle paddle2 = {V_WIDTH - 30, V_HEIGHT - 50};
RenderTexture2D vScreen;
Font font;
float dt;
int p1Score, p2Score;
Color const BACKGROUND = {40, 45, 52, 255};
bool canDrawFPS = false;

// Prototypes
void GameInit();
void GameRun();
void GetInput();
void UpdateAll();
bool hasCollided(Paddle paddle);
void DrawAll();
void ScoreDraw();
void ToggleFPS();
void DisplayFPS();
void DrawOnVScreen();
void GreetingDraw();
void DrawOnWindow();
void GameUnload();

// Main
int main(void) {
  GameInit();
  GameRun();
  GameUnload();
  return 0;
}

// Functions
void GameInit() {
  SetConfigFlags(FLAG_FULLSCREEN_MODE | FLAG_VSYNC_HINT |
                 FLAG_WINDOW_RESIZABLE);
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Pong");
  vScreen = LoadRenderTexture(V_WIDTH, V_HEIGHT);
  font = LoadFont("../assets/pong_font.ttf");
  SetTextureFilter(font.texture, TEXTURE_FILTER_POINT);
  HideCursor();
  SetTargetFPS(TARGET_FPS);
  BallReset(&ball);
  gameState = START;
}

void GameRun() {
  while (!WindowShouldClose()) {
    GetInput();
    if (gameState == PLAY) {
      UpdateAll();
    }
    DrawAll();
  }
}

void UpdateAll() {
  dt = GetFrameTime();
  BallUpdate(&ball, dt);

  if (hasCollided(paddle1)) {
    ball.left = paddle1.left + PADDLE_WIDTH;
    BallInvertXSpeed(&ball);
  } else if (hasCollided(paddle2)) {
    ball.left = paddle2.left - BALLSIZE;
    BallInvertXSpeed(&ball);
  }

  CheckBallHitBoundaries(&ball);
}

void GetInput() {
  switch (gameState) {
  case START:
    if (IsKeyPressed(KEY_ENTER)) {
      gameState = PLAY;
    }
    break;
  case PLAY:
    if (IsKeyPressed(KEY_ENTER)) {
      BallReset(&ball);
      gameState = START;
    }
    break;
  }
  if (IsKeyPressed(KEY_F)) {
    ToggleFPS();
  }
  if (IsKeyDown(KEY_W)) {
    PaddleMoveUp(&paddle1, dt);
  } else if (IsKeyDown(KEY_S)) {
    PaddleMoveDown(&paddle1, dt);
  }
  if (IsKeyDown(KEY_UP)) {
    PaddleMoveUp(&paddle2, dt);
  } else if (IsKeyDown(KEY_DOWN)) {
    PaddleMoveDown(&paddle2, dt);
  }
}

bool hasCollided(Paddle paddle) {
  return paddle.left < ball.left + BALLSIZE &&
         paddle.left + PADDLE_WIDTH > ball.left &&
         paddle.top < ball.top + BALLSIZE &&
         paddle.top + PADDLE_HEIGHT > ball.top;
}

void ToggleFPS() { canDrawFPS = !canDrawFPS; }

void DisplayFPS() {
  if (canDrawFPS) {
    DrawFPS(10, 10);
  }
}

void DrawAll() {
  DrawOnVScreen();
  DrawOnWindow();
}

void DrawOnVScreen() {
  BeginTextureMode(vScreen);
  DisplayFPS();
  ScoreDraw();
  PaddleDraw(&paddle1);
  PaddleDraw(&paddle2);
  BallDraw(&ball);
  GreetingDraw();
  EndTextureMode();
}

void ScoreDraw() {
  char buffer[MAX_SCORE_DIGITS_AMOUNT + 1]; // +1 for '\0'
  sprintf(buffer, "%d", p1Score);
  DrawText(buffer, V_WIDTH / 2 - 50, V_HEIGHT / 3, SCORE_FONTSIZE, WHITE);
  sprintf(buffer, "%d", p2Score);
  DrawText(buffer, V_WIDTH / 2 + 30, V_HEIGHT / 3, SCORE_FONTSIZE, WHITE);
}

void GreetingDraw() {
  char *greeting = "Hello Pong!";
  Vector2 textSize = MeasureTextEx(font, greeting, GREETING_FONTSIZE, 2);
  Vector2 textPosition =
      (Vector2){(V_WIDTH - textSize.x) / 2, (V_HEIGHT - textSize.y) * 0.06f};
  ClearBackground(BACKGROUND);
  DrawTextEx(font, greeting, textPosition, GREETING_FONTSIZE, 2, WHITE);
}

void DrawOnWindow() {
  BeginDrawing();
  DrawTexturePro(
      vScreen.texture,
      (Rectangle){0, 0, vScreen.texture.width, -vScreen.texture.height},
      (Rectangle){0, 0, WINDOW_WIDTH, WINDOW_HEIGHT}, (Vector2){0, 0}, 0,
      WHITE);
  EndDrawing();
}

void GameUnload() {
  UnloadRenderTexture(vScreen);
  UnloadFont(font);
  CloseWindow();
}