#include <iostream>
#include <vector>
#include <memory>

using namespace std;

// Enum for piece colors
enum Color { WHITE, BLACK };

// Base class for all chess pieces
class Piece {
protected:
    Color color;
    char symbol;

public:
    Piece(Color c, char s) : color(c), symbol(s) {}
    virtual ~Piece() {}

    Color getColor() { return color; }
    char getSymbol() { return symbol; }

    virtual bool isValidMove(int startX, int startY, int endX, int endY) = 0; // Pure virtual function will be implemented by class which inherits this class
};

// Pawn class
class Pawn : public Piece {
public:
    Pawn(Color c) : Piece(c,'P') {}

    bool isValidMove(int startX, int startY, int endX, int endY) override {
        if (endX < 0 || endX >= 8 || endY < 0 || endY >= 8) return false; // Out of bounds
        int direction = (color == WHITE) ? -1 : 1;
        return (endX == startX) && (startY + direction == endY );
    }
};

// Rook class
class Rook : public Piece {
public:
Rook(Color c) : Piece(c,'R') {}

bool isValidMove(int startX, int startY, int endX, int endY) override {
        if (endX < 0 || endX >= 8 || endY < 0 || endY >= 8) return false; // Out of bounds
        return (startX == endX || startY == endY); // Moves in a straight line
    }
};

// Knight class
class Knight : public Piece {
    public:
    Knight(Color c) : Piece(c,'N') {}
    
    bool isValidMove(int startX, int startY, int endX, int endY) override {
        if (endX < 0 || endX >= 8 || endY < 0 || endY >= 8) return false; // Out of bounds
        return (abs(startX - endX) == 2 && abs(startY - endY) == 1) ||
        (abs(startX - endX) == 1 && abs(startY - endY) == 2);
    }
};

// Bishop class
class Bishop : public Piece {
    public:
    Bishop(Color c) : Piece(c,'B') {}
    
    bool isValidMove(int startX, int startY, int endX, int endY) override {
        if (endX < 0 || endX >= 8 || endY < 0 || endY >= 8) return false; // Out of bounds
        return abs(startX - endX) == abs(startY - endY); // Moves diagonally
        // 3,3 -> 1,5, 1,1  3-1 == 5-3 , 3-1 == 3-1
    }
};

// Queen class
class Queen : public Piece {
public:
    Queen(Color c) : Piece(c,'Q') {}

    bool isValidMove(int startX, int startY, int endX, int endY) override {
        if (endX < 0 || endX >= 8 || endY < 0 || endY >= 8) return false; // Out of bounds
        //horizontal, vertical, or diagonal moves
        return (startX == endX || startY == endY) || (abs(startX - endX) == abs(startY - endY));
    }
};

// King class
class King : public Piece {
    public:
    King(Color c) : Piece(c,'K') {}
    
    bool isValidMove(int startX, int startY, int endX, int endY) override {
        if (endX < 0 || endX >= 8 || endY < 0 || endY >= 8) return false; // Out of bounds
        return abs(startX - endX) <= 1 && abs(startY - endY) <= 1; // Moves one square in any direction
    }
};

// Chess Board
class Board {
private:
    vector<vector<shared_ptr<Piece>>> grid;

public:
    Board() {
        // Board setup white view
        //     0 1 2 3 4 5 6 7
        // --------------------->x
        // 0 | R N B Q K B N R //black
        // 1 | P P P P P P P P
        // 2 | . . . . . . . .
        // 3 | . . . . . . . .
        // 4 | . . . . . . . .
        // 5 | . . . . . . . .
        // 6 | P P P P P P P P
        // 7 | R N B Q K B N R //white
        //  \/
        //   Y
        grid.resize(8, vector<shared_ptr<Piece>>(8, nullptr));

        // Initialize pieces for both players
        for (int i = 0; i < 8; i++) {
            grid[i][1] = make_shared<Pawn>(BLACK);
            grid[i][6] = make_shared<Pawn>(WHITE);
        }

        grid[0][0] = grid[0][7] = make_shared<Rook>(BLACK);
        grid[7][0] = grid[7][7] = make_shared<Rook>(WHITE);

        grid[0][1] = grid[0][6] = make_shared<Knight>(BLACK);
        grid[7][1] = grid[7][6] = make_shared<Knight>(WHITE);

        grid[0][2] = grid[0][5] = make_shared<Bishop>(BLACK);
        grid[7][2] = grid[7][5] = make_shared<Bishop>(WHITE);

        grid[0][3] = make_shared<Queen>(BLACK);
        grid[7][3] = make_shared<Queen>(WHITE);

        grid[0][4] = make_shared<King>(BLACK);
        grid[7][4] = make_shared<King>(WHITE);
    }

    void displayBoard() {
        cout << "  a b c d e f g h" << endl;
        for (int y = 0; y < 8; y++) {
            cout << y + 1 << " ";
            for (int x = 0; x < 8; x++) {
                if (grid[y][x])
                    cout << grid[y][x]->getSymbol() << " ";
                else
                    cout << ". "; // Empty square
            }
            cout << endl;
        }
    }

    bool movePiece(int startX, int startY, int endX, int endY, Color turn) {
        if (grid[startX][startY] == NULL || grid[startX][startY]->getColor() != turn)
            return false; // No piece at start or wrong turn

        if (grid[startX][startY]->isValidMove(startX, startY, endX, endY)) {
            grid[endX][endY] = grid[startX][startY];
            grid[startX][startY] = nullptr;
            return true;
        }
        return false;
    }
};

// Chess Game
class GameEngine {
private:
    Board board;
    Color turn;

public:
    GameEngine() : turn(WHITE) {}

    void play() {
        string input;
        while (true) {
            board.displayBoard();
            cout << (turn == WHITE ? "White's turn" : "Black's turn") << " (e.g., e2 e4): ";
            cin >> input;

            if (input == "exit") break;

            int startX = input[0] - 'a', startY = input[1] - '1';
            cin >> input;
            int endX = input[0] - 'a', endY = input[1] - '1';

            if (board.movePiece(startX, startY, endX, endY, turn)) {
                turn = (turn == WHITE) ? BLACK : WHITE;
            } else {
                cout << "Invalid move! Try again." << endl;
            }
        }
    }
};

// Main function
int main() {
    GameEngine game;
    game.play();
    return 0;
}
