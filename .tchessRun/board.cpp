#include "board.h"
#include "pieces.h"
#include <cctype>
#include <cstdlib>

char chessboard[8][8];
bool whiteTurn = true;
std::string statusMessage = "Insert your move (e.g. e2e4) or 'help' for help";
std::vector<char> capturedWhite;
std::vector<char> capturedBlack;

void initBoard() {
    char initialBoard[8][8] = {
        {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
        {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
        {'.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.'},
        {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
        {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}
    };
    
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            chessboard[i][j] = initialBoard[i][j];
        }
    }
    
    capturedWhite.clear();
    capturedBlack.clear();
}

bool parseMove(std::string move, int &fromRow, int &fromCol, int &toRow, int &toCol) {
    if (move.length() != 4) return false;
    
    fromCol = move[0] - 'a';
    fromRow = 8 - (move[1] - '0');
    toCol = move[2] - 'a';
    toRow = 8 - (move[3] - '0');
    
    if (fromCol < 0 || fromCol > 7 || fromRow < 0 || fromRow > 7 ||
        toCol < 0 || toCol > 7 || toRow < 0 || toRow > 7) {
        return false;
    }
    
    return true;
}

bool isCurrentPlayerPiece(char piece) {
    if (piece == '.') return false;
    if (whiteTurn && isupper(piece)) return true;
    if (!whiteTurn && islower(piece)) return true;
    return false;
}

bool isValidMove(int fromRow, int fromCol, int toRow, int toCol) {
    char piece = chessboard[fromRow][fromCol];
    char target = chessboard[toRow][toCol];
    
    if (target != '.' && isCurrentPlayerPiece(target)) return false;
    
    char lowerPiece = tolower(piece);
    
    switch(lowerPiece) {
        case 'p': return isValidPawnMove(fromRow, fromCol, toRow, toCol, piece);
        case 'r': return isValidRookMove(fromRow, fromCol, toRow, toCol);
        case 'n': return isValidKnightMove(fromRow, fromCol, toRow, toCol);
        case 'b': return isValidBishopMove(fromRow, fromCol, toRow, toCol);
        case 'q': return isValidQueenMove(fromRow, fromCol, toRow, toCol);
        case 'k': return isValidKingMove(fromRow, fromCol, toRow, toCol);
        default: return false;
    }
}

bool makeMove(std::string move) {
    int fromRow, fromCol, toRow, toCol;
    
    if (!parseMove(move, fromRow, fromCol, toRow, toCol)) {
        statusMessage = "Invalid Format. 'help' for commands";
        return false;
    }
    
    char piece = chessboard[fromRow][fromCol];
    
    if (piece == '.') {
        statusMessage = "No piece to move";
        return false;
    }
    
    if (!isCurrentPlayerPiece(piece)) {
        statusMessage = "You can only move your color pieces";
        return false;
    }
    
    if (!isValidMove(fromRow, fromCol, toRow, toCol)) {
        statusMessage = "Invalid move";
        return false;
    }
    
    char captured = chessboard[toRow][toCol];
    chessboard[toRow][toCol] = piece;
    chessboard[fromRow][fromCol] = '.';
    
    // Aggiungi pezzo catturato alla lista appropriata
    if (captured != '.') {
        if (isupper(captured)) {
            capturedWhite.push_back(captured);
        } else {
            capturedBlack.push_back(captured);
        }
        statusMessage = "Yoink!";
    } else {
        statusMessage = "Move done correctly";
    }
    
    whiteTurn = !whiteTurn;
    
    return true;
}
