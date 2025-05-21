#ifndef BALL_H
#define BALL_H

// Includes
#include "Settings.h"
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
    float x;
    float y;
    float xSpeed;
    float ySpeed;
} Ball;

// Prototypes
void BallUpdate(Ball *ball, float dt);
void BallDraw(Ball *ball);
void BallReset(Ball *ball);
void BallSetYSpeed(Ball *ball);
#endif