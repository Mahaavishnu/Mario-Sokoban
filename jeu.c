#include <SDL_image.h>
#include "mario.h"
#include "errors_handling.h"

void 			open_map(Env *env, char *filename)
{
	FILE		*file;
	char 		cur;
	int			i;
	int			j;

	file = fopen(filename, "r");
	i = 0;
	j = 0;

	while ((cur = fgetc(file)) != EOF)
	{
		//printf("%c", cur);
		switch (cur)
		{
			case '0' ... '5':
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
			//printf("%d", env->map[i][j]);
			position.x = j * 34;
			position.y = i * 34;
			switch (env->map[i][j])
			{
				case NOTHING ... TARGET:
					if (env->map[i][j] == TARGET)
						SDL_BlitSurface(env->surfaces[NOTHING], NULL, env->screen, &position);
					SDL_BlitSurface(env->surfaces[env->map[i][j]], NULL, env->screen, &position);
					break;
				case MARIO ... MARIOTARGET:
					env->pos.x = i;
					env->pos.y = j;
					SDL_BlitSurface(env->surfaces[NOTHING], NULL, env->screen, &position);
					if (env->map[i][j] == MARIOTARGET)
						SDL_BlitSurface(env->surfaces[TARGET], NULL, env->screen, &position);
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
			if (env->map[i][j] == TARGET || env->map[i][j] == MARIOTARGET)
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
	int			x;
	int			y;
	printf("inside move_mario\n");
	switch (env->event.key.keysym.sym)
	{
		case SDLK_UP:
			printf("case KEY UP\n");
			env->dir = UP;
			x = env->pos.x;
			y = env->pos.y;
			if (x - 1 >= 0)
			{
				switch (env->map[x-1][y])
				{
					case WALL:
						break;
					case NOTHING:
						printf("case x - 1 >= 0 KEY UP\n");
						env->map[x][y] = ((env->map[x][y] == MARIO) ? NOTHING : TARGET);
						env->map[x-1][y] = MARIO;
						break;
					case TARGET:
						env->map[x][y] = ((env->map[x][y] == MARIO) ? NOTHING : TARGET);
						env->map[x-1][y] = MARIOTARGET;
						break;
					case BOX:
						if (x - 2 >= 0)
						{
							switch (env->map[x-2][y])
							{
								case NOTHING:
									env->map[x-2][y] = BOX;
									env->map[x-1][y] = MARIO;
									env->map[x][y] = ((env->map[x][y] == MARIO) ? NOTHING : TARGET);
									break;
								case TARGET:
									env->map[x-2][y] = OK;
									env->map[x-1][y] = MARIO;
									env->map[x][y] = ((env->map[x][y] == MARIO) ? NOTHING : TARGET);
									break;
								default:
									break;
							}
						}
						break;
					case OK:
						if (x - 2 >= 0)
						{
							switch(env->map[x-2][y])
							{
								case NOTHING:
									env->map[x-2][y] = BOX;
									env->map[x-1][y] = MARIOTARGET;
									env->map[x][y] = ((env->map[x][y] == MARIO) ? NOTHING : TARGET);
									break;
								case TARGET:
									env->map[x-2][y] = OK;
									env->map[x-1][y] = MARIOTARGET;
									env->map[x][y] = ((env->map[x][y] == MARIO) ? NOTHING : TARGET);
									break; 
								default:
									break;
							}
						}
						break;
				}
			}
			break;
		case SDLK_RIGHT:
			env->dir = RIGHT;
			x = env->pos.x;
			y = env->pos.y;
			if (y + 1 < 12)
			{
				switch (env->map[x][y+1])
				{
					case WALL:
						break;
					case NOTHING:
						env->map[x][y] = ((env->map[x][y] == MARIO) ? NOTHING : TARGET);
						env->map[x][y+1] = MARIO;
						break;
					case TARGET:
						env->map[x][y] = ((env->map[x][y] == MARIO) ? NOTHING : TARGET);
						env->map[x][y+1] = MARIOTARGET;
						break;
					case BOX:
						if (y + 2 < 12)
						{
							switch (env->map[x][y+2])
							{
								case NOTHING:
									env->map[x][y+2] = BOX;
									env->map[x][y+1] = MARIO;
									env->map[x][y] = ((env->map[x][y] == MARIO) ? NOTHING : TARGET);
									break;
								case TARGET:
									env->map[x][y+2] = OK;
									env->map[x][y+1] = MARIO;
									env->map[x][y] = ((env->map[x][y] == MARIO) ? NOTHING : TARGET);
									break;
								default:
									break;
							}
						}
						break;
					case OK:
						if (y + 2 < 12)
						{
							switch(env->map[x][y+2])
							{
								case NOTHING:
									env->map[x][y+2] = BOX;
									env->map[x][y+1] = MARIOTARGET;
									env->map[x][y] = ((env->map[x][y] == MARIO) ? NOTHING : TARGET);
									break;
								case TARGET:
									env->map[x][y+2] = OK;
									env->map[x][y+1] = MARIOTARGET;
									env->map[x][y] = ((env->map[x][y] == MARIO) ? NOTHING : TARGET);
									break; 
								default:
									break;
							}
						}
						break;
				}
			}
			break;
		case SDLK_DOWN:
			env->dir = DOWN;
			x = env->pos.x;
			y = env->pos.y;
			if (x + 1 < 12)
			{
				switch (env->map[x+1][y])
				{
					case WALL:
						break;
					case NOTHING:
						env->map[x][y] = ((env->map[x][y] == MARIO) ? NOTHING : TARGET);
						env->map[x+1][y] = MARIO;
						break;
					case TARGET:
						env->map[x][y] = ((env->map[x][y] == MARIO) ? NOTHING : TARGET);
						env->map[x+1][y] = MARIOTARGET;
						break;
					case BOX:
						if (x + 2 < 12)
						{
							switch (env->map[x+2][y])
							{
								case NOTHING:
									env->map[x+2][y] = BOX;
									env->map[x+1][y] = MARIO;
									env->map[x][y] = ((env->map[x][y] == MARIO) ? NOTHING : TARGET);
									break;
								case TARGET:
									env->map[x+2][y] = OK;
									env->map[x+1][y] = MARIO;
									env->map[x][y] = ((env->map[x][y] == MARIO) ? NOTHING : TARGET);
									break;
								default:
									break;
							}
						}
						break;
					case OK:
						if (x + 2 < 12)
						{
							switch(env->map[x+2][y])
							{
								case NOTHING:
									env->map[x+2][y] = BOX;
									env->map[x+1][y] = MARIOTARGET;
									env->map[x][y] = ((env->map[x][y] == MARIO) ? NOTHING : TARGET);
									break;
								case TARGET:
									env->map[x+2][y] = OK;
									env->map[x+1][y] = MARIOTARGET;
									env->map[x][y] = ((env->map[x][y] == MARIO) ? NOTHING : TARGET);
									break; 
								default:
									break;
							}
						}
						break;
				}
			}
			break;
		case SDLK_LEFT:
			env->dir = LEFT;
			x = env->pos.x;
			y = env->pos.y;
			if (y - 1 >= 0)
			{
				switch (env->map[x][y-1])
				{
					case WALL:
						break;
					case NOTHING:
						env->map[x][y] = ((env->map[x][y] == MARIO) ? NOTHING : TARGET);
						env->map[x][y-1] = MARIO;
						break;
					case TARGET:
						env->map[x][y] = ((env->map[x][y] == MARIO) ? NOTHING : TARGET);
						env->map[x][y-1] = MARIOTARGET;
						break;
					case BOX:
						if (y - 2 >= 0)
						{
							switch (env->map[x][y-2])
							{
								case NOTHING:
									env->map[x][y-2] = BOX;
									env->map[x][y-1] = MARIO;
									env->map[x][y] = ((env->map[x][y] == MARIO) ? NOTHING : TARGET);
									break;
								case TARGET:
									env->map[x][y-2] = OK;
									env->map[x][y-1] = MARIO;
									env->map[x][y] = ((env->map[x][y] == MARIO) ? NOTHING : TARGET);
									break;
								default:
									break;
							}
						}
						break;
					case OK:
						if (y - 2 >= 0)
						{
							switch(env->map[x][y-2])
							{
								case NOTHING:
									env->map[x][y-2] = BOX;
									env->map[x][y-1] = MARIOTARGET;
									env->map[x][y] = ((env->map[x][y] == MARIO) ? NOTHING : TARGET);
									break;
								case TARGET:
									env->map[x][y-2] = OK;
									env->map[x][y-1] = MARIOTARGET;
									env->map[x][y] = ((env->map[x][y] == MARIO) ? NOTHING : TARGET);
									break; 
								default:
									break;
							}
						}
						break;
				}
			}
			break;
	}
	show_map(env);
	test_success(env);
}