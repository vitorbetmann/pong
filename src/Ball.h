#ifndef BALL_H
#define BALL_H

// Includes
#include <raylib.h>
#include <stdlib.h>
#include <time.h>

// Defines
#define BALLSIZE 4
#define BALL_X_SPEED 100
#define BALL_Y_SPEED_MAX 50

// Ball Struct
typedef struct
{
    float xPos;
    float yPos;
    float xSpeed;
    float ySpeed;
} Ball;

// Prototypes
void UpdateBall(Ball *ball, float dt);
void DrawBall(Ball *ball);
void ResetBall(Ball *ball, int WindowWidth, int WindowHeight);
void SetBallYSpeed(Ball *ball);
#endif