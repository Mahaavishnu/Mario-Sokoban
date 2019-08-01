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
	env.dir = DOWN;

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


	(env.surfaces[NOTHING] = SDL_CreateRGBSurface(SDL_SWSURFACE, 34, 34, 32, 0, 0, 0, 0)) == NULL ? freeSDL(&env, 1) : pushObject(&env, env.surfaces[NOTHING]);
	SDL_FillRect(env.surfaces[NOTHING], NULL, SDL_MapRGB(env.surfaces[NOTHING]->format, 255, 255, 255));

	(env.surfaces[WALL] = IMG_Load("img/mur.jpg")) == NULL ? freeSDL(&env, 1) : pushObject(&env, env.surfaces[WALL]);
	(env.surfaces[BOX] = IMG_Load("img/caisse.jpg")) == NULL ? freeSDL(&env, 1) : pushObject(&env, env.surfaces[BOX]);
	(env.surfaces[OK] = IMG_Load("img/caisse_ok.jpg")) == NULL ? freeSDL(&env, 1) : pushObject(&env, env.surfaces[OK]);
	(env.surfaces[TARGET] = IMG_Load("img/objectif.bmp")) == NULL ? freeSDL(&env, 1) : pushObject(&env, env.surfaces[TARGET]);
	(env.surfaces[MARIO + DOWN] = IMG_Load("img/mario_bas.gif")) == NULL ? freeSDL(&env, 1) : pushObject(&env, env.surfaces[MARIO + DOWN]);
	(env.surfaces[MARIO + LEFT] = IMG_Load("img/mario_gauche.gif")) == NULL ? freeSDL(&env, 1) : pushObject(&env, env.surfaces[MARIO + LEFT]);
	(env.surfaces[MARIO + UP] = IMG_Load("img/mario_haut.gif")) == NULL ? freeSDL(&env, 1) : pushObject(&env, env.surfaces[MARIO + UP]);
	(env.surfaces[MARIO + RIGHT] = IMG_Load("img/mario_droite.gif")) == NULL ? freeSDL(&env, 1) : pushObject(&env, env.surfaces[MARIO + RIGHT]);

	printf("avant pushObject\n");

	position.x = 0;
	position.y = 0;
	(menu = IMG_Load("img/menu.jpg")) == NULL ? freeSDL(&env, 1) : pushObject(&env, menu);
	SDL_BlitSurface(menu, NULL, env.screen, &position);

	if (SDL_UpdateWindowSurface(env.win) != 0)
		freeSDL(&env, 1);

	printf("juste avant boucle\n");

	while (42)
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
						if (env.play == 0)
						{
							if (argc != 2)
								freeSDL(&env, 2);
							open_map(&env, argv[1]);
							show_map(&env);
							env.play = 1;
							test_success(&env);
							//SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Test", "This is a test message", env.win);
						}
						break;
					/*case SDLK_2:
						if (env.play == 0)
						{

						}
						break;*/
					case SDLK_UP:
						if (env.play == 1)
							move_mario(&env);
						break;
					case SDLK_DOWN:
						if (env.play == 1)
							move_mario(&env);
						break;
					case SDLK_LEFT:
						if (env.play == 1)
							move_mario(&env);
						break;
					case SDLK_RIGHT:
						if (env.play == 1)
							move_mario(&env);
						break;
				}
				break;
		}
		//printf("dans la boucle\n");
	}

	//SDL_Delay(5000);
	//freeSDL(&env, 0);
}