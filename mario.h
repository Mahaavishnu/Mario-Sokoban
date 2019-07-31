#ifndef MARIO_H
#define MARIO_H

#include <SDL.h>

typedef struct 		objlist
{
	SDL_Surface		*ptr;
	struct objlist 	*next;
} 					Objlist;

typedef enum 		box
{
	NOTHING,
	WALL,
	BOX,
	OK,
	TARGET,
	MARIO
}					Box;

typedef struct 		env
{
	Objlist 		*list;
	SDL_Window 		*win;
	SDL_Surface 	*screen;
	SDL_Event 		event;
	int 			play;
	Box 			map[12][12];
}					Env;

#endif