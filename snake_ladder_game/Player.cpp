#include "Player.h"

Player::Player(string playerName) : name(playerName), position(1) {} // Start at position 1

void Player::move(int steps) {
    if (position+steps > 100)  return; // Cannot move beyond position 100
    position += steps;
}