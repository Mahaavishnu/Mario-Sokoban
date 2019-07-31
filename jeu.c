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


	while (i < 12)
	{
		while (j < 12)
		{
			position.x = j * 34;
			position.y = i * 34;
			switch (env->map[i][j])
			{
				case NOTHING...TARGET:
					if (env->map[i][j] == TARGET)
						SDL_BlitSurface(env->surfaces[NOTHING], NULL, env->screen, &position);
					SDL_BlitSurface(env->surfaces[env->map[i][j]], NULL, env->screen, &position);
					break;
				case MARIO:
					env->pos.x = i;
					env->pos.y = j;
					SDL_BlitSurface(env->surfaces[NOTHING], NULL, env->screen, &position);
					SDL_BlitSurface(env->surfaces[MARIO + env->dir], NULL, env->screen, &position);
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

void			test_success(Env *env)
{
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (i < 12)
	{
		while (j < 12)
		{
			if (env->map[i][j] == TARGET)
				return;
			j++;
		}
		j = 0;
		i++;
	}
	freeSDL(env, 0);
}

void			move_mario(Env *env)
{
	switch (env->event.key.keysym.sym)
	{
		case SDLK_UP:
			env->dir = UP;
			//if (env->pos.y > 0 && env->map[])
			break;
		case SDLK_RIGHT:
			env->dir = RIGHT;
			break;
		case SDLK_DOWN:
			env->dir = DOWN;
			break;
		case SDLK_LEFT:
			env->dir = LEFT;
			break;
	}
	test_success(env);
}