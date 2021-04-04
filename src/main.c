#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <SDL2/SDL.h>

#include "logic.h"
#include "render.h"

void print_usage()
{
    printf("Usage: ./cellular-automata AUTOMATA\n");
    printf("       Conway's Game of Life -> gameoflife\n");
    printf("       Langton's ant -> langton\n");
    printf("       Brian's brain -> briansbrain\n");
}

int main(int argc, char **argv)
{
    int automata;
    char running_title[64] = { '\0' };
    char paused_title[64] = { '\0' };

    if (argc < 2) {
        print_usage();
        return EXIT_FAILURE;
    }
    else if (strcmp(argv[1], "langton") == 0) {
        automata = LANGTONS_ANT;
        strncat(running_title, "LANGTONS_ANT", 48);
        strncat(paused_title, "LANGTONS_ANT", 48);
    }
    else if (strcmp(argv[1], "gameoflife") == 0) {
        automata = GAME_OF_LIFE;
        strncat(running_title, "THE GAME OF LIFE", 48);
        strncat(paused_title, "THE GAME OF LIFE", 48);
    }
    else if (strcmp(argv[1], "briansbrain") == 0) {
        automata = BRIANS_BRAIN;
        strncat(running_title, "BRIAN'S BRAIN", 48);
        strncat(paused_title, "BRIAN'S BRAIN", 48);
    }
    else {
        fprintf(stderr, "No such automata.\n");
        print_usage();
        return EXIT_FAILURE;
    }

    strncat(running_title, " - RUNNING", 48);
    strncat(paused_title, " - PAUSED", 48);

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL_INIT Error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_Window *window = SDL_CreateWindow(running_title,
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
            for (int x = 0; x < N; x++)
                for (int y = 0; y < N; y++)
                    state.board[x][y] = BLACK;

            // GLIDER
            state.board[N/2][N/2] = WHITE;
            state.board[N/2+1][N/2] = WHITE;
            state.board[N/2+2][N/2] = WHITE;
            state.board[N/2+1][N/2-2] = WHITE;
            state.board[N/2+2][N/2-1] = WHITE;
            break;

        case BRIANS_BRAIN:
            for (int x = 0; x < N; x++)
                for (int y = 0; y < N; y++)
                    state.board[x][y] = BLACK;

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
                    state.mode = PAUSED_MODE;
                    SDL_SetWindowTitle(window, paused_title);

                    int x = event.button.x / CELL_WIDTH;
                    int y = event.button.y / CELL_HEIGHT;
                    switch (automata) {
                        case GAME_OF_LIFE:
                            state.board[x][y] = (state.board[x][y] + 1) % 2;
                            break;
                        case BRIANS_BRAIN:
                            state.board[x][y] = (state.board[x][y] + 1) % 3;
                    }
                    break;

                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == ' ') {
                        state.mode = RUNNING_MODE + PAUSED_MODE - state.mode;
                        SDL_SetWindowTitle(window, state.mode ? paused_title : running_title);
                    }
                    break;

                default: {}
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        render_grid(renderer, &state);

        if (state.mode == RUNNING_MODE)
            usleep((1.0 / MOVES_PER_SECOND) * 1000000);

        switch (automata) {
            case LANGTONS_ANT:
                langtons_ant(renderer, &state);
                break;

            case GAME_OF_LIFE:
                game_of_life(renderer, &state);
                break;

            case BRIANS_BRAIN:
                brians_brain(renderer, &state);
                break;
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}
