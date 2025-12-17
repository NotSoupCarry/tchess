# Tchess - A Simple Terminal Chess

<div align="center">

```
♔ ♕  TCHESS  ♛ ♚
```

A beautiful, lightweight chess game that runs entirely in your terminal.

</div>

## Features

- **Beautiful Unicode pieces** - Full chess piece symbols (♔♕♖♗♘♙)
- **Colored board** - Alternating light and dark squares
- **Full chess rules** - Valid move validation for all pieces
- **Captured pieces tracker** - See all captured pieces at the bottom
- **Responsive design** - Auto-adjusts to terminal size
- **Lightweight** - No external dependencies, pure C++

## Gameplay

Play chess directly in your terminal with a clean, intuitive interface. The game features:
- Turn-based gameplay (White/Black)
- Move validation for all chess pieces
- Captured piece tracking
- Real-time status messages

## Installation

### Quick Install

```bash
# Clone the repository
git clone https://github.com/yourusername/tchess.git
cd tchess

# Compile and run
make run
```

### Manual Compilation

```bash
g++ -std=c++11 -o tchess main.cpp board.cpp pieces.cpp display.cpp
./tchess
```

## How to Play

### Starting the Game

```bash
./tchess
```

### Making Moves

Moves are entered in algebraic notation format: `[from][to]`

**Examples:**
- `e2e4` - Move piece from e2 to e4
- `g1f3` - Move knight from g1 to f3
- `e7e5` - Move pawn from e7 to e5


## Features Breakdown

### Piece Movement
- ♙ **Pawns**: Forward movement (1 or 2 squares from start), diagonal capture
- ♖ **Rooks**: Horizontal and vertical movement
- ♘ **Knights**: L-shaped movement (can jump over pieces)
- ♗ **Bishops**: Diagonal movement
- ♕ **Queen**: Combination of rook and bishop movement
- ♔ **King**: One square in any direction

### Visual Features
- Color-coded pieces (White: bright, Black: dark)
- Alternating board squares (light gray / brown)
- Turn indicator showing current player
- Status messages for move feedback
- Captured pieces display at the bottom

## 🛠️ Makefile Commands

```bash
make          # Compile the project
make run      # Compile and run
make clean    # Remove compiled files
```


## Author

**Your Name**
- GitHub: [@NotSoupCarry](https://github.com/NotSoupCarry)


## Screenshots
<img src="/screenshots/screenshot1.png">
<img src="/screenshots/screenshot2.png">


---

<div align="center">

**Enjoy your game of chess! ♟️**

Made with ❤️ and C++

</div>
