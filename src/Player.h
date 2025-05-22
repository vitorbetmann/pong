#ifndef PLAYER_H
#define PLAYER_H

#include "Paddle.h"

// Data types
typedef struct {
  Paddle paddle;
  unsigned int score;
} Player;

// Prototypes
Player NewPlayer(float left, float top);
void Score(Player *player);
#endif