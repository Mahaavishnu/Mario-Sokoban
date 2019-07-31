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
	SDL_Rect		position;
	int				i = 0;
	int				j = 0;

	SDL_FillRect(env->screen, NULL, SDL_MapRGB(env->screen->format, 255, 255, 255));
	(wall = IMG_Load("img/mur.jpg")) == NULL ? freeSDL(env, 1) : pushObject(env, wall);
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
			}
			j++;
		}
		j = 0;
		i++;
	}

	if (SDL_UpdateWindowSurface(env->win) != 0)
		freeSDL(env, 1);
}