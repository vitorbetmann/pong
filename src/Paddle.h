#ifndef PADDLE_H
#define PADDLE_H
#define _DEFAULT_SOURCE

// Includes
#include "Settings.h"
#include <raylib.h>

// Defines
#define PADDLE_WIDTH 5
#define PADDLE_HEIGHT 20
#define PADDLE_SPEED 200

// Data Types
typedef struct
{
    float x;
    float y;
} Paddle;

// Prototypes
void PaddleInit(Paddle *paddle, float startingX, float startingY);
void PaddleMoveUp(Paddle *paddle, float dt);
void PaddleMoveDown(Paddle *paddle, float dt);
void PaddleDraw(Paddle *paddle);
#endif
