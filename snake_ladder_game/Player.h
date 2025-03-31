#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
using namespace std;

class Player {
    public:
        string name;
        int position;
        Player(string name);
        void move(int steps);
};
#endif