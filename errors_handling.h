#ifndef ERRORS_HANDLING_H
#define ERRORS_HANDLING_H

#include <SDL.h>

void			pushObject(Env *env, SDL_Surface *ptr);
void			freeSDL(Env *env, int error);

#endif