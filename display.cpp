#include "display.h"
#include "board.h"
#include "pieces.h"
#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>
#include <cctype>

using namespace std;

void printChessboard() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    
    int total_content_height = 30;
    int top_padding = (w.ws_row - total_content_height) / 2;
    if (top_padding < 1) top_padding = 1;
    
    cout << "\033[H\033[2J\033[3J";
    
    for(int i = 0; i < top_padding; i++) cout << endl;
    
    // Titolo
    string title = "♔ ♕  TCHESS  ♛ ♚";
    int title_padding = (w.ws_col - 20) / 2;
    for(int s = 0; s < title_padding; s++) cout << " ";
    cout << "\033[1;38;5;220m" << title << "\033[0m" << endl << endl;
    
    // Indicatore turno
    string turnMsg = whiteTurn ? "White to move" : "Black to move";
    string turnColor = whiteTurn ? "\033[1;97m" : "\033[1;90m";
    int turn_padding = (w.ws_col - 15) / 2;
    for(int s = 0; s < turn_padding; s++) cout << " ";
    cout << turnColor << turnMsg << "\033[0m" << endl;
    
    // Messaggio di stato
    int status_padding = (w.ws_col - statusMessage.length()) / 2;
    for(int s = 0; s < status_padding; s++) cout << " ";
    cout << "\033[1;36m" << statusMessage << "\033[0m" << endl << endl;
    
    // Scacchiera più grande
    int board_width = 82;
    int left_padding = (w.ws_col - board_width) / 2;
    if (left_padding < 2) left_padding = 2;
    
    // Bordo superiore
    for(int s = 0; s < left_padding; s++) cout << " ";
    cout << "\033[1;37m    ╔═══════════════════════════════════════════════════════════════════════════╗\033[0m" << endl;
    
    // Scacchiera con caselle più grandi (9 spazi di larghezza, 3 righe di altezza)
    for (int i = 0; i < 8; i++) {
        // Prima riga della casella (vuota)
        for(int s = 0; s < left_padding; s++) cout << " ";
        cout << "\033[1;37m    ║\033[0m";
        
        for (int j = 0; j < 8; j++) {
            bool isLightSquare = (i + j) % 2 == 0;
            string bgColor = isLightSquare ? "\033[48;5;252m" : "\033[48;5;94m";
            cout << bgColor << "         " << "\033[0m\033[1;37m│\033[0m";
        }
        cout << "\033[1;37m║\033[0m" << endl;
        
        // Riga centrale con numero di riga e pezzo
        for(int s = 0; s < left_padding; s++) cout << " ";
        cout << "\033[1;37m  " << (8 - i) << " ║\033[0m";
        
        for (int j = 0; j < 8; j++) {
            bool isLightSquare = (i + j) % 2 == 0;
            string bgColor = isLightSquare ? "\033[48;5;252m" : "\033[48;5;94m";
            
            char piece = chessboard[i][j];
            string pieceColor;
            if (piece != '.') {
                pieceColor = isupper(piece) ? "\033[1;38;5;255m" : "\033[1;38;5;0m";
            } else {
                pieceColor = "\033[37m";
            }
            
            cout << bgColor << pieceColor << "    " << getPieceSymbol(piece) << "    " << "\033[0m";
            cout << "\033[1;37m│\033[0m";
        }
        
        cout << "\033[1;37m║\033[0m" << endl;
        
        // Terza riga della casella (vuota)
        for(int s = 0; s < left_padding; s++) cout << " ";
        cout << "\033[1;37m    ║\033[0m";
        
        for (int j = 0; j < 8; j++) {
            bool isLightSquare = (i + j) % 2 == 0;
            string bgColor = isLightSquare ? "\033[48;5;252m" : "\033[48;5;94m";
            cout << bgColor << "         " << "\033[0m\033[1;37m│\033[0m";
        }
        cout << "\033[1;37m║\033[0m" << endl;
        
        // Separatore tra righe
        if (i < 7) {
            for(int s = 0; s < left_padding; s++) cout << " ";
            cout << "\033[1;37m    ║";
            for (int j = 0; j < 8; j++) {
                cout << "─────────┼";
            }
            cout << "\b║\033[0m" << endl;
        }
    }
    
    // Bordo inferiore
    for(int s = 0; s < left_padding; s++) cout << " ";
    cout << "\033[1;37m    ╚═══════════════════════════════════════════════════════════════════════════╝\033[0m" << endl;
    
    for(int s = 0; s < left_padding; s++) cout << " ";
    cout << "\033[1;37m         a          b        c          d         e        f         g         h\033[0m" << endl << endl;
    
    // PEZZI CATTURATI
    for(int s = 0; s < left_padding; s++) cout << " ";
    cout << "\033[1;90m━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\033[0m" << endl;
    
    // Pezzi bianchi catturati
    for(int s = 0; s < left_padding; s++) cout << " ";
    cout << "\033[1;97m    Captured White: \033[0m";
    if (capturedWhite.empty()) {
        cout << "\033[2;37m(none)\033[0m";
    } else {
        for (char piece : capturedWhite) {
            cout << "\033[1;97m" << getPieceSymbol(piece) << " \033[0m";
        }
    }
    cout << endl;
    
    // Pezzi neri catturati
    for(int s = 0; s < left_padding; s++) cout << " ";
    cout << "\033[1;90m    Captured Black: \033[0m";
    if (capturedBlack.empty()) {
        cout << "\033[2;37m(none)\033[0m";
    } else {
        for (char piece : capturedBlack) {
            cout << "\033[1;90m" << getPieceSymbol(piece) << " \033[0m";
        }
    }
    cout << endl;
}

void handleResize(int sig) {
    printChessboard();
    cout << "\n  → Move: " << flush;
}
