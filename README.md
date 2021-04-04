# Celullar Automata
Implementation of different celullar automata with SDL2 in C. Developed and tested on Linux, I have no idea how to (if it can be done at all) run it on other operating systems.

## Dependencies
* GCC
* GNU Make
* SDL2

## Running
* `git clone https://github.com/joaquin-rossi/celullar-automata`
* `cd celullar-automata`
* `make`
* `./bin/main`

## Extra info
* Click a cell to change its value.
* Press the spacebar to toggle between paused and unpaused.
* Edit src/logic.h (pre-processor #defines) to change speed, size, etc.

## Demo
![Langton's ant](demo.gif)