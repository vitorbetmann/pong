#include "Player.h"

Player NewPlayer(float left, float top) {
  Player newPlayer = {.paddle = {left, top}};
  return newPlayer;
}

void Score(Player *player) { player->score++; }