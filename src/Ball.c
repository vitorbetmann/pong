#include "Ball.h"

void UpdateBall(Ball *ball, float dt)
{
    ball->xPos += ball->xSpeed * dt;
    ball->yPos += ball->ySpeed * dt;
}

void DrawBall(Ball *ball)
{
    DrawRectangle(ball->xPos, ball->yPos, BALLSIZE, BALLSIZE, WHITE);
}

void ResetBall(Ball *ball, int WindowWidth, int WindowHeight)
{
    srandom(time(NULL));
    ball->xPos = (WindowWidth - BALLSIZE) / 2;
    ball->yPos = (WindowHeight - BALLSIZE) / 2;
    ball->xSpeed = random() % 2 == 0 ? -BALL_X_SPEED : BALL_X_SPEED;
    SetBallYSpeed(ball);
}

void SetBallYSpeed(Ball *ball)
{
    int speed = random() / ((double)RAND_MAX + 1) * (BALL_Y_SPEED_MAX + 1);
    ball->ySpeed = (random() % 2 == 0) ? speed : speed;
}