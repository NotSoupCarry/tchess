#include "pieces.h"
#include "board.h"
#include <cstdlib>
#include <cctype>

std::string getPieceSymbol(char piece) {
    switch(piece) {
        case 'K': return "♔";
        case 'Q': return "♕";
        case 'R': return "♖";
        case 'B': return "♗";
        case 'N': return "♘";
        case 'P': return "♙";
        case 'k': return "♚";
        case 'q': return "♛";
        case 'r': return "♜";
        case 'b': return "♝";
        case 'n': return "♞";
        case 'p': return "♟";
        default: return " ";
    }
}

bool isValidPawnMove(int fromRow, int fromCol, int toRow, int toCol, char piece) {
    int direction = isupper(piece) ? -1 : 1;
    int startRow = isupper(piece) ? 6 : 1;
    
    if (toCol == fromCol && toRow == fromRow + direction && chessboard[toRow][toCol] == '.') {
        return true;
    }
    
    if (fromRow == startRow && toCol == fromCol && toRow == fromRow + 2 * direction &&
        chessboard[toRow][toCol] == '.' && chessboard[fromRow + direction][fromCol] == '.') {
        return true;
    }
    
    if (abs(toCol - fromCol) == 1 && toRow == fromRow + direction && 
        chessboard[toRow][toCol] != '.' && 
        ((whiteTurn && islower(chessboard[toRow][toCol])) || 
         (!whiteTurn && isupper(chessboard[toRow][toCol])))) {
        return true;
    }
    
    return false;
}

bool isValidRookMove(int fromRow, int fromCol, int toRow, int toCol) {
    if (fromRow != toRow && fromCol != toCol) return false;
    
    int rowDir = (toRow > fromRow) ? 1 : (toRow < fromRow) ? -1 : 0;
    int colDir = (toCol > fromCol) ? 1 : (toCol < fromCol) ? -1 : 0;
    
    int r = fromRow + rowDir;
    int c = fromCol + colDir;
    
    while (r != toRow || c != toCol) {
        if (chessboard[r][c] != '.') return false;
        r += rowDir;
        c += colDir;
    }
    
    return true;
}

bool isValidKnightMove(int fromRow, int fromCol, int toRow, int toCol) {
    int rowDiff = abs(toRow - fromRow);
    int colDiff = abs(toCol - fromCol);
    return (rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2);
}

bool isValidBishopMove(int fromRow, int fromCol, int toRow, int toCol) {
    if (abs(toRow - fromRow) != abs(toCol - fromCol)) return false;
    
    int rowDir = (toRow > fromRow) ? 1 : -1;
    int colDir = (toCol > fromCol) ? 1 : -1;
    
    int r = fromRow + rowDir;
    int c = fromCol + colDir;
    
    while (r != toRow || c != toCol) {
        if (chessboard[r][c] != '.') return false;
        r += rowDir;
        c += colDir;
    }
    
    return true;
}

bool isValidQueenMove(int fromRow, int fromCol, int toRow, int toCol) {
    return isValidRookMove(fromRow, fromCol, toRow, toCol) || 
           isValidBishopMove(fromRow, fromCol, toRow, toCol);
}

bool isValidKingMove(int fromRow, int fromCol, int toRow, int toCol) {
    return abs(toRow - fromRow) <= 1 && abs(toCol - fromCol) <= 1;
}
