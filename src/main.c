#include "Ball.h"
#include "Player.h"
#include "Settings.h"
#include <raylib.h>
#include <stdio.h>

// Data Types
typedef enum {
  START,
  PLAY,
  SERVE,
} GameState;

// Variables
Player player1, player2;
GameState gameState;
Ball ball;
RenderTexture2D vScreen;
Font font;
float dt;
bool canDrawFPS = false;
Color const BACKGROUND = {40, 45, 52, 255};

// Prototypes
void GameInit();
void GameRun();
void CheckChangeGameState();
void UpdateAll();
bool hasCollided(Paddle paddle);
void DrawAll();
void ScoreDraw();
void CheckToggleFPS();
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

  player1 = NewPlayer(10, 30);
  player2 = NewPlayer(V_WIDTH - 30, V_HEIGHT - 50);
  BallReset(&ball);
  gameState = START;
}

void GameRun() {
  while (!WindowShouldClose()) {
    CheckChangeGameState();
    UpdateAll();
    DrawAll();
  }
}

void UpdateAll() {
  dt = GetFrameTime();
  CheckToggleFPS();

  switch (gameState) {
  case START:
    break;
  case PLAY:
    BallUpdate(&ball, dt);

    if (hasCollided(player1.paddle)) {
      ball.left = player1.paddle.left + PADDLE_WIDTH;
      BallInvertXSpeed(&ball);
    } else if (hasCollided(player2.paddle)) {
      ball.left = player2.paddle.left - BALLSIZE;
      BallInvertXSpeed(&ball);
    }

    if (ball.left > V_WIDTH) {
      Score(&player1);
      BallReset(&ball);
    } else if (ball.left + BALLSIZE < 0) {
      Score(&player2);
      BallReset(&ball);
    }

    CheckBallHitBoundaries(&ball);

    break;
  case SERVE:
    break;
  }

  if (IsKeyDown(KEY_W)) {
    PaddleMoveUp(&player1.paddle, dt);
  } else if (IsKeyDown(KEY_S)) {
    PaddleMoveDown(&player1.paddle, dt);
  }
  if (IsKeyDown(KEY_UP)) {
    PaddleMoveUp(&player2.paddle, dt);
  } else if (IsKeyDown(KEY_DOWN)) {
    PaddleMoveDown(&player2.paddle, dt);
  }
}

void CheckChangeGameState() {
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
  case SERVE:
    break;
  }
}

bool hasCollided(Paddle paddle) {
  return paddle.left < ball.left + BALLSIZE &&
         paddle.left + PADDLE_WIDTH > ball.left &&
         paddle.top < ball.top + BALLSIZE &&
         paddle.top + PADDLE_HEIGHT > ball.top;
}

void CheckToggleFPS() {
  if (IsKeyPressed(KEY_F)) {
    canDrawFPS = !canDrawFPS;
  }
}

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
  PaddleDraw(&player1.paddle);
  PaddleDraw(&player2.paddle);
  BallDraw(&ball);
  GreetingDraw();
  EndTextureMode();
}

void ScoreDraw() {
  char buffer[MAX_SCORE_DIGITS_AMOUNT + 1]; // +1 for '\0'
  sprintf(buffer, "%d", player1.score);
  DrawText(buffer, V_WIDTH / 2 - 50, V_HEIGHT / 3, SCORE_FONTSIZE, WHITE);
  sprintf(buffer, "%d", player2.score);
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