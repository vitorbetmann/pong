#include "Ball.h"
#include "Settings.h"
#include <raylib.h>
#include <stdlib.h>
#include <time.h>

void BallUpdate(Ball *ball, float dt) {
  ball->left += ball->xSpeed * dt;
  ball->top += ball->ySpeed * dt;
}

void BallDraw(Ball *ball) {
  DrawRectangle(ball->left, ball->top, BALLSIZE, BALLSIZE, WHITE);
}

void BallReset(Ball *ball) {
  BallSetYSpeedRandom(ball, false);
  ball->left = (V_WIDTH - BALLSIZE) / 2.0;
  ball->top = (V_HEIGHT - BALLSIZE) / 2.0;
  ball->xSpeed = random() % 2 == 0 ? -BALL_X_SPEED : BALL_X_SPEED;
}
void CheckBallHitBoundaries(Ball *ball) {
  if (ball->top < 0) {
    ball->top = 0;
    BallInvertYSpeed(ball);
  } else if (ball->top + BALLSIZE > V_HEIGHT) {
    ball->top = V_HEIGHT - BALLSIZE;
    BallInvertYSpeed(ball);
  }
}

void BallInvertXSpeed(Ball *ball) {
  ball->xSpeed *= -1.03;
  BallSetYSpeedRandom(ball, true);
}

void BallInvertYSpeed(Ball *ball) { ball->ySpeed *= -1; }

void BallSetYSpeedRandom(Ball *ball, bool keepDirection) {
  float ogDir = ball->ySpeed;
  srandom(time(NULL));
  int speed = random() / ((double)RAND_MAX + 1) * (BALL_Y_SPEED_MAX + 1);
  ball->ySpeed = (random() % 2 == 0) ? -speed : speed;
  if (keepDirection && ball->ySpeed * ogDir < 0) {
    ball->ySpeed *= -1;
  }
}