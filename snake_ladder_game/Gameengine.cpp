#include "Gameengine.h"

GameEngine::GameEngine(vector<string> &playerNames, vector<Snake> &snakes, vector<Ladder> &ladders): board(snakes, ladders),turn(0) {
    // Initialize the random number generator
    srand(static_cast<unsigned int>(time(0))); //seed for random dice roll
    for(string name : playerNames) {
        players.push_back(Player(name)); 
    }
}

int GameEngine::rollDice() const {
    // Roll a dice and return a number between 1 and 6
    return (rand() % 6) + 1;
}

void GameEngine::play() {
    while(true) {
        Player& currentPlayer = players[turn];
        turn = (turn+1)%players.size();
        cout<<currentPlayer.getName()<<" Player's turn press enter to continue"<<endl;
        cin.ignore(); // Wait for user input to roll the dice
        int rolled = rollDice();
        cout<<"Rolled: "<<rolled<<endl;
        int newPosition = currentPlayer.move(rolled);
        if(newPosition > 100) {
            cout<<"You rolled too high, stay at "<<currentPlayer.getPosition()<<endl;
        } else {
            newPosition = board.checkPosition(newPosition); // Check for snakes or ladders
            currentPlayer.setPostion(newPosition);  // Update player's position
            cout<<currentPlayer.getName()<<" moved to "<<currentPlayer.getPosition()<<endl;
            if(currentPlayer.getPosition() == 100) {
                cout<<currentPlayer.getName()<<" wins!"<<endl;
                break; // End the game if a player reaches 100
            }
        }
    }
}