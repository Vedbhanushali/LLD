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
        Player& currentPlayer = players[turn % players.size()];
        cout<<currentPlayer.name<<" Player's turn press enter to continue"<<endl;
        cin.ignore(); // Wait for user input to roll the dice
        int rolled = rollDice();
        cout<<"Rolled: "<<rolled<<endl;
        int newPosition = currentPlayer.position + rolled;
        if(newPosition > 100) {
            cout<<"You rolled too high, stay at "<<currentPlayer.position<<endl;
        } else {
            newPosition = board.checkPosition(newPosition); // Check for snakes or ladders
            currentPlayer.position = newPosition; // Update player's position
            cout<<currentPlayer.name<<" moved to "<<currentPlayer.position<<endl;
            if(currentPlayer.position == 100) {
                cout<<currentPlayer.name<<" wins!"<<endl;
                break; // End the game if a player reaches 100
            }
        }
        turn++; // Move to the next player
    }
}