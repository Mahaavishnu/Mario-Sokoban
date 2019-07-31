#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include "mario.h"

void			pushObject(Env *env, SDL_Surface *ptr)
{
	Objlist		*obj;

	obj = malloc(sizeof(Objlist));
	obj->ptr = ptr;
	obj->next = env->list;
	env->list = obj;
	printf("pushObject\n");
}

void			freeSDL(Env *env, int error)
{
	Objlist 	*tmp;

	//tmp = malloc(sizeof(Objlist));
	while (env->list != NULL)
	{
		printf("début while freeSDL\n");
		tmp = (env->list)->next;
		printf("avant SDL_FreeSurface()\n");
		SDL_FreeSurface((env->list)->ptr);
		free(env->list);
		env->list = tmp;
	}
	//free(tmp);
	printf("après while freeSDL\n");
	//free(env->list);
	if (error == 1)
		fprintf(stderr, "SDL Error : %s\n", SDL_GetError());
	SDL_FreeSurface(env->screen);
	SDL_DestroyWindow(env->win);
	SDL_Quit();
	//free(env->win);
	//free(env->screen);
	//free(env);
	if (error == 1)
		exit(EXIT_FAILURE);
	else
		exit (EXIT_SUCCESS);
}