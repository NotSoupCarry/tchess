#include <iostream>
#include <csignal>
#include "board.h"
#include "display.h"

using namespace std;

int main() {
    signal(SIGWINCH, handleResize);
    cout << "\033[?1049h" << flush;
    
    initBoard();
    
    while (true) {
        printChessboard();
        cout << "\n  → Move: ";
        string input;
        if (!(cin >> input)) break; 
        if (input == "exit" || input == "quit") break;
        if (input == "help") {
            statusMessage = "Format: e2e4 (from → to) | 'exit' to exit";
            continue;
        }
        
        makeMove(input);
    }
    
    cout << "\033[?1049l" << flush;
    return 0;
}
