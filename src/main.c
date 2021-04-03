#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

#include "logic.h"
#include "render.h"

int main(int argc, char **argv)
{
    int automatum;

    if (argc < 2)
        automatum = LANGTON;
    else if (strcmp(argv[1], "langton") == 0)
        automatum = LANGTON;
    else {
        fprintf(stderr, "No such automatum\n");
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

    // INIT BOARD
    switch (automatum) {
        case LANGTON:
            state_t state = {
                .ant = {
                    .x = N/2,
                    .y = N/2,
                    .dir = LEFT
                },
                .mode = RUNNING_MODE
            };

            for (int x=0; x<N; x++)
                for (int y=0; y<N; y++)
                    state.board[x][y] = WHITE;
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
                    state.mode = RUNNING_MODE + PAUSED_MODE - state.mode;
                    SDL_SetWindowTitle(window, state.mode ? "PAUSED" : "RUNNING");
                    break;

                default: {}
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        switch (automatum) {
            case LANGTON:
                langton(renderer, &state);
                break;
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}