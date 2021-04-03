#include <SDL2/SDL.h>

#include "logic.h"
#include "render.h"

const SDL_Color BLACK_CELL_COLOR = { .r = 0, .g = 0, .b = 0 };
const SDL_Color WHITE_CELL_COLOR = { .r = 255, .g = 255, .b = 255 };
const SDL_Color ANT_COLOR = { .r = 255, .g = 50, .b = 50 };

void render(SDL_Renderer *renderer, const state_t *state)
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
}