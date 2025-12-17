#ifndef PIECES_H
#define PIECES_H

#include <string>

std::string getPieceSymbol(char piece);

bool isValidPawnMove(int fromRow, int fromCol, int toRow, int toCol, char piece);
bool isValidRookMove(int fromRow, int fromCol, int toRow, int toCol);
bool isValidKnightMove(int fromRow, int fromCol, int toRow, int toCol);
bool isValidBishopMove(int fromRow, int fromCol, int toRow, int toCol);
bool isValidQueenMove(int fromRow, int fromCol, int toRow, int toCol);
bool isValidKingMove(int fromRow, int fromCol, int toRow, int toCol);

#endif
