#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include "mario.h"
#include "errors_handling.h"
#include "jeu.h"

int					main(int argc, char *argv[])
{
	Env 			env;
	SDL_Surface 	*menu;
	SDL_Rect		position;

	//env = malloc(sizeof(env));
	env.list = malloc(sizeof(Objlist));
	//env.win = malloc(sizeof(SDL_Window));
	//env.screen = malloc(sizeof(SDL_Surface));
	env.play = 0;

	printf("avant init\n");

	if (SDL_Init(SDL_INIT_VIDEO) == -1)
	{
		fprintf(stderr, "SDL_Init Error : %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	env.win = SDL_CreateWindow("Mario Sokoban", 100, 100, 34*12, 34*12, SDL_WINDOW_SHOWN);
	if (env.win == NULL)
	{
		fprintf(stderr, "SDL_CreateWindow Error : %s\n", SDL_GetError());
		SDL_Quit();
		exit(EXIT_FAILURE);
	}
	env.screen = SDL_GetWindowSurface(env.win);
	if (env.screen == NULL)
	{
		fprintf(stderr, "SDL_GetWindowSurface Error : %s\n", SDL_GetError());
		SDL_DestroyWindow(env.win);
		SDL_Quit();
		exit(EXIT_FAILURE);
	}
	env.list = NULL;


	printf("avant pushObject\n");

	position.x = 0;
	position.y = 0;
	(menu = IMG_Load("img/menu.jpg")) == NULL ? freeSDL(&env, 1) : pushObject(&env, menu);
	SDL_BlitSurface(menu, NULL, env.screen, &position);

	if (SDL_UpdateWindowSurface(env.win) != 0)
		freeSDL(&env, 1);

	printf("juste avant boucle\n");

	while (env.play != -1)
	{
		SDL_WaitEvent(&(env.event));
		switch ((env.event).type)
		{
			case SDL_QUIT:
				freeSDL(&env, 0);
				break;
			case SDL_KEYDOWN:
				switch (env.event.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						freeSDL(&env, 0);
						break;
					case SDLK_1:
						if (env.play != 1)
						{
							open_map(&env);
							show_map(&env);
							env.play = 1;
						}
						break;
					case SDLK_UP:
						position.y--;
						break;
					case SDLK_DOWN:
						position.y++;
						break;
					case SDLK_RIGHT:
						position.x++;
						break;
					case SDLK_LEFT:
						position.x--;
						break;
				}
				break;
		}
		//printf("dans la boucle\n");
	}

	//SDL_Delay(5000);
	//freeSDL(&env, 0);
}