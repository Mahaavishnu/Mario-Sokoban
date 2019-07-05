#ifndef ERRORS_HANDLING_H
#define ERRORS_HANDLING_H

#include <SDL.h>

void			pushObject(Objlist **list, SDL_Surface *ptr);
void			freeSDL(Objlist **list, SDL_Window *win);

#endif