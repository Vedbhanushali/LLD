#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include<iostream>
#include<vector>
#include<ctime>

#include "Board.h"
#include "Player.h"

using namespace std;
// class Player;
// class Board;
// class Snake;
// class Ladder;

class GameEngine {
    private:
        vector<Player> players;
        int turn;
        Board board; 
    public:
        GameEngine(vector<string> &playerNames,vector<Snake> &snakes,vector<Ladder> &ladders);
        int rollDice() const;
        void play();
};

#endif