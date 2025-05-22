#include "Ball.h"
#include "Settings.h"
#include <raylib.h>
#include <stdlib.h>
#include <time.h>

void BallUpdate(Ball *ball, float dt) {
  ball->x += ball->xSpeed * dt;
  ball->y += ball->ySpeed * dt;
}

void BallDraw(Ball *ball) {
  DrawRectangle(ball->x, ball->y, BALLSIZE, BALLSIZE, WHITE);
}

void BallReset(Ball *ball) {
  srandom(time(NULL));
  ball->x = (V_WIDTH - BALLSIZE) / 2.0;
  ball->y = (V_HEIGHT - BALLSIZE) / 2.0;
  ball->xSpeed = random() % 2 == 0 ? -BALL_X_SPEED : BALL_X_SPEED;
  BallSetYSpeed(ball);
}

void BallSetYSpeed(Ball *ball) {
  int speed = random() / ((double)RAND_MAX + 1) * (BALL_Y_SPEED_MAX + 1);
  ball->ySpeed = (random() % 2 == 0) ? -speed : speed;
}