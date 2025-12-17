#ifndef BOARD_H
#define BOARD_H

#include <string>
#include <vector>

extern char chessboard[8][8];
extern bool whiteTurn;
extern std::string statusMessage;
extern std::vector<char> capturedWhite;
extern std::vector<char> capturedBlack;

void initBoard();
bool parseMove(std::string move, int &fromRow, int &fromCol, int &toRow, int &toCol);
bool isCurrentPlayerPiece(char piece);
bool isValidMove(int fromRow, int fromCol, int toRow, int toCol);
bool makeMove(std::string move);

#endif
