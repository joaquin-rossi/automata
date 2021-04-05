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

## Available automata
* [Langton's ant](https://en.wikipedia.org/wiki/Langton%27s_ant)
* [Conway's game of life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life)
* [Brian's brain](https://en.wikipedia.org/wiki/Brian%27s_Brain)
* [Wireworld](https://en.wikipedia.org/wiki/Wireworld)

## Extra info
* Click a cell to change its value.
* Press the spacebar to toggle between paused and unpaused.
* Press the left click on a cell to alter it's value.
* Edit src/logic.h (pre-processor #defines) to change speed, size, etc.

## Demo
![Langton's ant](demo.gif)
