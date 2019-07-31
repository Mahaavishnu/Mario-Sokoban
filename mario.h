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
	MARIO,
	MARIOTARGET = MARIO + 5
}					Box;

typedef enum 		dir
{
	DOWN,
	LEFT,
	UP,
	RIGHT
}					Dir;

typedef struct 		env
{
	Objlist 		*list;
	SDL_Window 		*win;
	SDL_Surface 	*screen;
	SDL_Event 		event;
	int 			play;
	Box 			map[12][12];
	SDL_Surface 	*surfaces[9];
	Dir 			dir;
	SDL_Rect		pos;
}					Env;

#endif