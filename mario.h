#ifndef MARIO_H
#define MARIO_H

#include <SDL.h>

typedef struct 		objlist
{
	SDL_Surface		*ptr;
	struct objlist 	*next;
} 					Objlist;

void				init(SDL_Window **win, SDL_Surface **screen);

#endif