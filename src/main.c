#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

#include "logic.h"
#include "render.h"

int mod(int a, int b)
{
    int r = a % b;
    return r < 0 ? r + b : r;
}

int main(int argc, char **argv)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL_INIT Error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_Window *window = SDL_CreateWindow("Langton's ant",
                                          SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                          SCREEN_WIDTH, SCREEN_HEIGHT,
                                          SDL_WINDOW_SHOWN);

    if (window == NULL) {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1,
                                                SDL_RENDERER_ACCELERATED |
                                                SDL_RENDERER_PRESENTVSYNC);

    if (renderer == NULL) {
        SDL_DestroyWindow(window);
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    state_t state = {
        .ant = {
            .x = N/2,
            .y = N/2,
            .dir = LEFT
        },
        .mode = RUNNING_MODE
    };

    // INITIALIZE BOARD TO ALL WHITE
    for (int x=0; x<N; x++)
        for (int y=0; y<N; y++)
            state.board[x][y] = WHITE;

    SDL_Event event;

    while (state.mode != QUIT_MODE) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    state.mode = QUIT_MODE;
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    state.mode = RUNNING_MODE + PAUSED_MODE - state.mode;
                    break;

                default: {}
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        render(renderer, &state);
        SDL_RenderPresent(renderer);

        if (state.mode == RUNNING_MODE)
        for (int i=0; i<MOVESPERFRAME; i++) {
            int current = state.board[state.ant.x][state.ant.y];

            // TURN 90º
            switch (current) {
                case WHITE:
                    state.ant.dir = mod(state.ant.dir + 1, 4);
                    break;
                case BLACK:
                    state.ant.dir = mod(state.ant.dir - 1, 4);
                    break;

                default: {}
            }

            // FLIP THE COLOR OF THE SQUARE
            state.board[state.ant.x][state.ant.y] = BLACK + WHITE - current;

            // MOVE FORWARD ONE UNIT
            switch (state.ant.dir) {
                case UP:
                    state.ant.y = mod(state.ant.y - 1, N);
                    break;
                case RIGHT:
                    state.ant.x = mod(state.ant.x + 1, N);
                    break;
                case DOWN:
                    state.ant.y = mod(state.ant.y + 1, N);
                    break;
                case LEFT:
                    state.ant.x = mod(state.ant.x - 1, N);
                    break;
            }
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}