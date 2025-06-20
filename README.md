# Navy

Battleship Game in C (1v1 via Unix signals)

---

## Features

- Ship map loading from file
- Real-time 1v1 gameplay via kill signals
- Display of player and enemy maps
- Turn-based input with coordinate parsing
- Hit/miss feedback and victory detection

---

## Map File Format

The ship map is defined in a simple text file (pos1, pos2, etc.) like so:

2:C1:C2

- Each line: [size]:[start]:[end]
- Only horizontal or vertical ships allowed
- Map size is 8x8 (A-H, 1-8)

---

## Build

Compile the project using:

make

Clean compiled files:

make clean      # remove .o files
make fclean     # remove .o files and binary
make re         # clean and rebuild

---

## How to Play

This game is designed for two players, each in a separate terminal.

Player 1:

make play

This runs:

./navy pos1

It will display your PID — share it with Player 2.

Player 2:

make join PID=12345

This runs:

./navy 12345 pos2

Replace 12345 with the actual PID shown by Player 1.
    
---

## Game Logic

- Players alternate turns entering coordinates (e.g. C4)
- Signals are sent to indicate shots
- Maps update with hits (x) and misses (o)
- First to sink all enemy ships wins

---

## Dependencies

- Standard C (no external libs)
- Works on Linux / macOS (POSIX signals)
