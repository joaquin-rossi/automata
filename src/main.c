#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

#include "logic.h"
#include "render.h"

void print_usage()
{
    printf("Usage: ./cellular-automata AUTOMATA\n");
    printf("       Conway's Game of Life -> gameoflife\n");
    printf("       Langton's ant -> langton\n");
}

int main(int argc, char **argv)
{
    int automata;

    if (argc < 2) {
        print_usage();
        return EXIT_FAILURE;
    }
    else if (strcmp(argv[1], "langton") == 0)
        automata = LANGTONS_ANT;
    else if (strcmp(argv[1], "gameoflife") == 0)
        automata = GAME_OF_LIFE;
    else {
        fprintf(stderr, "No such automata.\n");
        print_usage();
        return EXIT_FAILURE;
    }

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL_INIT Error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_Window *window = SDL_CreateWindow("RUNNING",
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

    state_t state = { .mode = RUNNING_MODE };

    // INIT BOARD
    switch (automata) {
        case LANGTONS_ANT:
            state.ant.x = N/2;
            state.ant.y = N/2;
            state.ant.dir = LEFT;
            break;
        
        case GAME_OF_LIFE:
            for (int x=0; x<N; x++)
                for (int y=0; y<N; y++)
                    state.board[x][y] = BLACK;

            state.board[N/2][N/2] = WHITE;
            state.board[N/2+1][N/2] = WHITE;
            state.board[N/2+2][N/2] = WHITE;
            state.board[N/2+1][N/2-2] = WHITE;
            state.board[N/2+2][N/2-1] = WHITE;
            break;
    }

    SDL_Event event;

    while (state.mode != QUIT_MODE) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    state.mode = QUIT_MODE;
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    if (automata == GAME_OF_LIFE) {
                        state.mode = PAUSED_MODE;
                        SDL_SetWindowTitle(window, "PAUSED");

                        int x = event.button.x / CELL_WIDTH;
                        int y = event.button.y / CELL_HEIGHT;

                        state.board[x][y] = BLACK + WHITE - state.board[x][y];
                    }
                    break;

                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == ' ') {
                        state.mode = RUNNING_MODE + PAUSED_MODE - state.mode;
                        SDL_SetWindowTitle(window, state.mode ? "PAUSED" : "RUNNING");
                    }
                    break;

                default: {}
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        switch (automata) {
            case LANGTONS_ANT:
                langtons_ant(renderer, &state);
                break;

            case GAME_OF_LIFE:
                game_of_life(renderer, &state);
                break;
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}