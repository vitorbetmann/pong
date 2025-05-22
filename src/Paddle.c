#include "Paddle.h"
#include "Settings.h"
#include <raylib.h>

void PaddleMoveUp(Paddle *paddle, float dt) {
  int newPos = paddle->y - PADDLE_SPEED * dt;
  paddle->y = newPos < 0 ? 0 : newPos;
}

void PaddleMoveDown(Paddle *paddle, float dt) {
  int newPos = paddle->y + PADDLE_SPEED * dt;
  int lowerWindowLimit = V_HEIGHT - PADDLE_HEIGHT;
  paddle->y = newPos > lowerWindowLimit ? lowerWindowLimit : newPos;
}

void PaddleDraw(Paddle *paddle) {
  DrawRectangle(paddle->x, paddle->y, PADDLE_WIDTH, PADDLE_HEIGHT, WHITE);
}