#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Snake {
public:
    int start, end;
    Snake(int s, int e);
};

class Ladder {
public:
    int start, end;
    Ladder(int s, int e);
};

class Board {
    public:
    unordered_map<int, int> specialMoves; // Stores snake and ladder mappings 
    Board(vector<Snake> &s, vector<Ladder> &l); // Constructor to initialize snakes and ladders
    int checkPosition(int newPosition); // Check if the new position is a snake or ladder (special move)
};

#endif