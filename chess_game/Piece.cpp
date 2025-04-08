#include "Piece.h"

Piece::Piece(Color c, char s) : color(c), symbol(s) {}
Piece::~Piece() {}

Color Piece::getColor() const { return color; }
char Piece::getSymbol() const { return symbol; }