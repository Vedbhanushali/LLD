#ifndef PIECE_H
#define PIECE_H
#include <iostream>
using namespace std;

enum Color { WHITE, BLACK };

class Piece {
    private:
        char symbol;
        Color color; // 0 for white, 1 for black

    public:
        Piece(Color c, char s);
        virtual ~Piece() = default; // Virtual destructor for proper cleanup of derived classes
        Color getColor() const;
        char getSymbol() const;
        virtual bool isValidMove(int startX, int startY, int endX, int endY) const = 0; // Pure virtual function will be implemented by class which inherits this class
};

class Pawn : public Piece {
    public:
        Pawn(Color c) : Piece(c, 'P') {}
        bool isValidMove(int startX, int startY, int endX, int endY) const override;
};

class Rook : public Piece {
    public:
        Rook(Color c) : Piece(c, 'R') {}
        bool isValidMove(int startX, int startY, int endX, int endY) const override;
};

class Knight : public Piece {
    public:
        Knight(Color c) : Piece(c, 'N') {}
        bool isValidMove(int startX, int startY, int endX, int endY) const override;
};

class Bishop : public Piece {
    public:
        Bishop(Color c) : Piece(c, 'B') {}
        bool isValidMove(int startX, int startY, int endX, int endY) const override;
};

class Queen : public Piece {
    public:
        Queen(Color c) : Piece(c, 'Q') {}
        bool isValidMove(int startX, int startY, int endX, int endY) const override;
};

class King : public Piece {
    public:
        King(Color c) : Piece(c, 'K') {}
        bool isValidMove(int startX, int startY, int endX, int endY) const override;
};

#endif