#ifndef RENDER_H_
#define RENDER_H_

#include "logic.h"

void render_grid(SDL_Renderer *renderer, const state_t *state);
void langtons_ant(SDL_Renderer *renderer, state_t *state);
void game_of_life(SDL_Renderer *renderer, state_t *state);
void brians_brain(SDL_Renderer *renderer, state_t *state);
void wireworld(SDL_Renderer *renderer, state_t *state);

#endif // RENDERING_H_
