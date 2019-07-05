#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include "mario.h"

void			pushObject(Objlist **list, SDL_Surface *ptr)
{
	Objlist		*obj;

	obj = malloc(sizeof(Objlist));
	obj->ptr = ptr;
	obj->next = *list;
	*list = obj;
}

void			freeSDL(Objlist **list, SDL_Window *win)
{
	Objlist 	*tmp;
	while (*list != NULL)
	{
		tmp = (*list)->next;
		SDL_FreeSurface((*list)->ptr);
		free(*list);
		*list = tmp;
	}
	free(list);
	fprintf(stderr, "SDL Error : %s\n", SDL_GetError());
	SDL_DestroyWindow(win);
	SDL_Quit();
	exit(EXIT_FAILURE);
}