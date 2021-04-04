#ifndef RENDER_H_
#define RENDER_H_

#include "logic.h"

void langtons_ant(SDL_Renderer *renderer, state_t *state);
void game_of_life(SDL_Renderer *renderer, state_t *state);

#endif // RENDERING_H_