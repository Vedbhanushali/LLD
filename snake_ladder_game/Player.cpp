#include "Player.h"

Player::Player(string playerName) : name(playerName), position(1) {} // Start at position 1

void Player::move(int steps) {
    position += steps;
    if (position > 100) position = 100; // Stay within board limits
}