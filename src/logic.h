#ifndef LOGIC_H_
#define LOGIC_H_

#define N 200
#define SCREEN_WIDTH 800.0
#define SCREEN_HEIGHT 800.0
#define CELL_WIDTH (SCREEN_WIDTH / N)
#define CELL_HEIGHT (SCREEN_HEIGHT / N)
#define MOVESPERFRAME 50

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
    position ant;
    int mode;
} state_t;

#endif // LOGIC_H_