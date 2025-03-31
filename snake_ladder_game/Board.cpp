#include "Board.h"

Snake::Snake(int s, int e) : start(s), end(e) {}

Ladder::Ladder(int s, int e) : start(s), end(e) {}

Board::Board(vector<Snake> &snakes,vector<Ladder> &ladders) {
    for (const auto& snake : snakes) {
        specialMoves[snake.start] = snake.end; // Store snake mapping
    }
    for (const auto& ladder : ladders) {
        specialMoves[ladder.start] = ladder.end; // Store ladder mapping
    }
}

int Board::checkPosition(int newPosition) {
    if(specialMoves.find(newPosition) != specialMoves.end()) {
        return specialMoves[newPosition]; // Move to new position if snake/ladder
    }
    return newPosition; // No special move, return the same position
}