#include <SDL_image.h>
#include "mario.h"
#include "errors_handling.h"

void 			open_map(Env *env)
{
	FILE		*file;
	char 		cur;
	int			i;
	int			j;

	file = fopen("level", "r");
	i = 0;
	j = 0;

	while ((cur = fgetc(file)) != EOF)
	{
		//printf("%c", cur);
		switch (cur)
		{
			case '0'...'5':
				env->map[i][j] = (int)(cur - 48);
				break;
		}
		if (j == 11)
		{
			i++;
			j = 0;
		}
		else
			j++;
	}
	/*printf("\n");
	i = 0;
	j = 0;
	while (i < 12)
	{
		while (j < 12)
		{
			printf("%d", env->map[i][j]);
			j++;
		}
		j = 0;
		i++;
	}
	printf("\n");*/
	fclose(file);
}

void			show_map(Env *env)
{
	SDL_Surface 	*wall;
	SDL_Surface 	*box;
	SDL_Surface 	*ok;
	SDL_Surface 	*target;
	SDL_Surface 	*down;
	SDL_Surface 	*left;
	SDL_Surface 	*up;
	SDL_Surface 	*right;
	SDL_Rect		position;
	int				i = 0;
	int				j = 0;

	SDL_FillRect(env->screen, NULL, SDL_MapRGB(env->screen->format, 255, 255, 255));

	(wall = IMG_Load("img/mur.jpg")) == NULL ? freeSDL(env, 1) : pushObject(env, wall);
	(box = IMG_Load("img/caisse.jpg")) == NULL ? freeSDL(env, 1) : pushObject(env, box);
	(ok = IMG_Load("img/caisse_ok.jpg")) == NULL ? freeSDL(env, 1) : pushObject(env, ok);
	(target = IMG_Load("img/objectif.bmp")) == NULL ? freeSDL(env, 1) : pushObject(env, target);
	(down = IMG_Load("img/mario_bas.gif")) == NULL ? freeSDL(env, 1) : pushObject(env, down);
	(left = IMG_Load("img/mario_gauche.gif")) == NULL ? freeSDL(env, 1) : pushObject(env, left);
	(up = IMG_Load("img/mario_haut.gif")) == NULL ? freeSDL(env, 1) : pushObject(env, up);
	(right = IMG_Load("img/mario_droite.gif")) == NULL ? freeSDL(env, 1) : pushObject(env, right);

	while (i < 12)
	{
		while (j < 12)
		{
			position.x = j * 34;
			position.y = i * 34;
			switch (env->map[i][j])
			{
				case WALL:
					SDL_BlitSurface(wall, NULL, env->screen, &position);
					break;
				case BOX:
					SDL_BlitSurface(box, NULL, env->screen, &position);
					break;
				case OK:
					SDL_BlitSurface(ok, NULL, env->screen, &position);
					break;
				case TARGET:
					SDL_BlitSurface(target, NULL, env->screen, &position);
					break;
				case MARIO:
					env->pos.x = i;
					env->pos.y = j;
					switch (env->dir)
					{
						case DOWN:
							SDL_BlitSurface(down, NULL, env->screen, &position);
							break;
						case LEFT:
							SDL_BlitSurface(left, NULL, env->screen, &position);
							break;
						case UP:
							SDL_BlitSurface(up, NULL, env->screen, &position);
							break;
						case RIGHT:
							SDL_BlitSurface(right, NULL, env->screen, &position);
							break;
					}
					break;
			}
			j++;
		}
		j = 0;
		i++;
	}

	if (SDL_UpdateWindowSurface(env->win) != 0)
		freeSDL(env, 1);
}