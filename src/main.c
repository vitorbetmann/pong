#include "Ball.h"
#include "Player.h"
#include "Settings.h"
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Data Types
typedef enum { START, SERVE, PLAY, PAUSE, GAMEOVER } GameState;

// Variables
Player player1, player2;
GameState gameState;
Ball ball;
RenderTexture2D vScreen;
Font font;
float dt;
bool canDrawFPS = false;
Color const BACKGROUND = {40, 45, 52, 255};
const char *const SERVING_TEXT =
    "\t\tPlayer %c's serve!\nPress Enter to serve!";
const char *const GAMEOVER_TEXT =
    "\t\t\tPlayer %c WON!\nPress Enter to restart!";
Player servingPlayer, winner;
bool hasScored;
Sound paddleHit, score, wallHit;

// Prototypes
void GameInit();
void GameRun();
void CheckChangeGameState();
void UpdateAll();
bool hasCollided(Paddle paddle);
void DrawAll();
void ScoreDraw();
void ServingDraw();
void PauseDraw();
void GameOverDraw();

void SetServingPlayer();
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
  SetRandomSeed(time(NULL));

  InitAudioDevice();
  paddleHit = LoadSound("../assets/paddle_hit.wav");
  score = LoadSound("../assets/score.wav");
  wallHit = LoadSound("../assets/wall_hit.wav");

  player1 = NewPlayer(10, 30, '1');
  player2 = NewPlayer(V_WIDTH - 30, V_HEIGHT - 50, '2');
  ball = NewBall();
  SetServingPlayer();

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
  case PAUSE:
  case SERVE:
    break;
  case PLAY:
    BallUpdate(&ball, dt);

    if (hasCollided(player1.paddle)) {
      ball.left = player1.paddle.left + PADDLE_WIDTH;
      BallInvertXSpeed(&ball);
      PlaySound(paddleHit);
    } else if (hasCollided(player2.paddle)) {
      ball.left = player2.paddle.left - BALLSIZE;
      BallInvertXSpeed(&ball);
      PlaySound(paddleHit);
    }

    hasScored = false;
    if (ball.left > V_WIDTH) {
      Score(&player1);
      hasScored = true;
      PlaySound(score);

    } else if (ball.left + BALLSIZE < 0) {
      Score(&player2);
      hasScored = true;
      PlaySound(score);
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

    break;
  case GAMEOVER:
    break;
  }
}

void CheckChangeGameState() {
  switch (gameState) {
  case START:
    if (IsKeyPressed(KEY_ENTER)) {
      gameState = SERVE;
    }
    break;
  case SERVE:
    if (IsKeyPressed(KEY_ENTER)) {
      gameState = PLAY;
    }
    break;
  case PLAY:
    if (IsKeyPressed(KEY_ENTER)) {
      gameState = PAUSE;
    }
    if (hasScored) {
      BallReset(&ball);
      SetServingPlayer();
      gameState = SERVE;
    } else {
      if (BallHitBoundaries(&ball)) {
        PlaySound(wallHit);
      }
    }

    if (player1.score == MAX_SCORE || player2.score == MAX_SCORE) {
      winner = player1.score == MAX_SCORE ? player1 : player2;
      gameState = GAMEOVER;
    }
    break;
  case PAUSE:
    if (IsKeyPressed(KEY_ENTER)) {
      gameState = PLAY;
    }
    break;
  case GAMEOVER:
    if (IsKeyPressed(KEY_ENTER)) {
      BallReset(&ball);
      BallSetXSpeedRandom(&ball);
      SetServingPlayer();
      player1.score = 0;
      player2.score = 0;
      gameState = SERVE;
    }
  }
}

void SetServingPlayer() {
  if (ball.xSpeed > 0) {
    servingPlayer = player1;
  } else {
    servingPlayer = player2;
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
  ClearBackground(BACKGROUND);
  DisplayFPS();
  ScoreDraw();
  PaddleDraw(&player1.paddle);
  PaddleDraw(&player2.paddle);
  BallDraw(&ball);
  switch (gameState) {
  case START:
    GreetingDraw();
    break;
  case SERVE:
    ServingDraw();
    break;
  case PAUSE:
    PauseDraw();
    break;
  case GAMEOVER:
    GameOverDraw();
    break;
  case PLAY:
    break;
  }
  EndTextureMode();
}

void ScoreDraw() {
  char buffer[MAX_SCORE_DIGITS_AMOUNT + 1];
  snprintf(buffer, sizeof(buffer), "%d", player1.score);
  DrawText(buffer, V_WIDTH / 2 - 50, V_HEIGHT / 3, SCORE_FONTSIZE, WHITE);
  snprintf(buffer, sizeof(buffer), "%d", player2.score);
  DrawText(buffer, V_WIDTH / 2 + 30, V_HEIGHT / 3, SCORE_FONTSIZE, WHITE);
}

void GreetingDraw() {
  char *greeting = "\t\tWelcome to Pong!\nPress Enter to begin";
  Vector2 textSize = MeasureTextEx(font, greeting, GREETING_FONTSIZE, 2);
  Vector2 textPosition =
      (Vector2){(V_WIDTH - textSize.x) / 2, (V_HEIGHT - textSize.y) * 0.06f};
  DrawTextEx(font, greeting, textPosition, GREETING_FONTSIZE, 2, WHITE);
}

void ServingDraw() {
  char buffer[strlen(SERVING_TEXT) + 1];
  snprintf(buffer, sizeof(buffer), SERVING_TEXT, servingPlayer.number);
  Vector2 textSize = MeasureTextEx(font, buffer, GREETING_FONTSIZE, 2);
  Vector2 textPosition =
      (Vector2){(V_WIDTH - textSize.x) / 2, (V_HEIGHT - textSize.y) * 0.06f};
  DrawTextEx(font, buffer, textPosition, GREETING_FONTSIZE, 2, WHITE);
}

void GameOverDraw() {
  char buffer[strlen(GAMEOVER_TEXT)];
  snprintf(buffer, sizeof(buffer), GAMEOVER_TEXT, winner.number);
  Vector2 textSize = MeasureTextEx(font, buffer, GREETING_FONTSIZE, 2);
  Vector2 textPosition =
      (Vector2){(V_WIDTH - textSize.x) / 2, (V_HEIGHT - textSize.y) * 0.06f};
  DrawTextEx(font, buffer, textPosition, GREETING_FONTSIZE, 2, WHITE);
}

void PauseDraw() {
  char *pauseText = "Game Paused";
  Vector2 textSize = MeasureTextEx(font, pauseText, GREETING_FONTSIZE, 2);
  Vector2 textPosition =
      (Vector2){(V_WIDTH - textSize.x) / 2, (V_HEIGHT - textSize.y) * 0.06f};
  DrawTextEx(font, pauseText, textPosition, GREETING_FONTSIZE, 2, WHITE);
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
  UnloadSound(paddleHit);
  UnloadSound(score);
  UnloadSound(wallHit);
  CloseAudioDevice();
  CloseWindow();
}