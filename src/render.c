#include <SDL2/SDL.h>

#include "logic.h"
#include "render.h"

int mod(int a, int b)
{
    int r = a % b;
    return r < 0 ? r + b : r;
}

const SDL_Color BLACK_CELL_COLOR = { .r = 0, .g = 0, .b = 0 };
const SDL_Color WHITE_CELL_COLOR = { .r = 255, .g = 255, .b = 255 };
const SDL_Color ANT_COLOR = { .r = 255, .g = 50, .b = 50 };

void langton(SDL_Renderer *renderer, state_t *state)
{
    // RENDER GRID
    for (int x=0; x<N; x++)
        for (int y=0; y<N; y++) {
            switch(state->board[x][y]) {
                case BLACK:
                    SDL_SetRenderDrawColor(renderer, BLACK_CELL_COLOR.r, BLACK_CELL_COLOR.g, BLACK_CELL_COLOR.b, 255);
                    SDL_Rect rect = {
                        .x = x * CELL_WIDTH,
                        .y = y * CELL_HEIGHT,
                        .w = CELL_WIDTH,
                        .h = CELL_HEIGHT
                    };

                    SDL_RenderFillRect(renderer, &rect);

                    break;
                
                default: {}
            }
        }

    // RENDER ANT
    SDL_SetRenderDrawColor(renderer, ANT_COLOR.r, ANT_COLOR.g, ANT_COLOR.b, 255);
    SDL_Rect ant_rect = {
        .x = state->ant.x * CELL_WIDTH ,
        .y = state->ant.y * CELL_HEIGHT,
        .w = CELL_WIDTH,
        .h = CELL_HEIGHT
    };

    SDL_RenderFillRect(renderer, &ant_rect);

    if (state->mode == RUNNING_MODE)
    for (int i=0; i<MOVESPERFRAME; i++) {
        int current = state->board[state->ant.x][state->ant.y];

        // TURN 90º
        switch (current) {
        case WHITE:
            state->ant.dir = mod(state->ant.dir + 1, 4);
            break;
        case BLACK:
            state->ant.dir = mod(state->ant.dir - 1, 4);
            break;

        default: {}
        }

        // FLIP THE COLOR OF THE SQUARE
        state->board[state->ant.x][state->ant.y] = BLACK + WHITE - current;

        // MOVE FORWARD ONE UNIT
        switch (state->ant.dir) {
        case UP:
            state->ant.y = mod(state->ant.y - 1, N);
            break;
        case RIGHT:
            state->ant.x = mod(state->ant.x + 1, N);
            break;
        case DOWN:
            state->ant.y = mod(state->ant.y + 1, N);
            break;
        case LEFT:
            state->ant.x = mod(state->ant.x - 1, N);
            break;
        }
    }
}