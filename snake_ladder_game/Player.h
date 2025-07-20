#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
using namespace std;

class Player {
    string name;
    int position;
    public:
        Player(string name);
        string getName() const;
        int getPosition() const;
        int move(int steps);
        void setPostion(int pos);
};
#endif