#ifndef LOGIC_H_
#define LOGIC_H_

#define N 50
#define SCREEN_WIDTH 800.0
#define SCREEN_HEIGHT 800.0
#define CELL_WIDTH (SCREEN_WIDTH / N)
#define CELL_HEIGHT (SCREEN_HEIGHT / N)
#define MOVES_PER_FRAME 1

enum AUTOMATA {
    LANGTONS_ANT,
    GAME_OF_LIFE
};

enum CELL {
    BLACK,
    WHITE
};

enum ORIENTATION {
    UP,
    RIGHT,
    DOWN,
    LEFT
};

enum MODE {
    RUNNING_MODE,
    PAUSED_MODE,
    QUIT_MODE
};

typedef struct {
    int x;
    int y;
    int dir;
} position;

typedef struct {
    int board[N][N];
    int mode;
    position ant;
} state_t;

#endif // LOGIC_H_