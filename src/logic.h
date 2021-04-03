#ifndef LOGIC_H_
#define LOGIC_H_

#define N 50
#define SCREEN_WIDTH 800.0
#define SCREEN_HEIGHT 800.0
#define CELL_WIDTH (SCREEN_WIDTH / N)
#define CELL_HEIGHT (SCREEN_HEIGHT / N)
#define MOVESPERFRAME 1

enum AUTOMATUM {
    LANGTON
};

enum CELL {
    WHITE,
    BLACK
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