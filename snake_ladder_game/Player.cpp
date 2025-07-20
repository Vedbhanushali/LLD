#include "Player.h"

Player::Player(string playerName) : name(playerName), position(1) {} // Start at position 1

int Player::move(int steps) {
    position += steps;
}

string Player::getName() const {
    return name;
}

void Player::setPostion(int pos) {
    position = pos;
}

int Player::getPosition() const {
    return position;
}