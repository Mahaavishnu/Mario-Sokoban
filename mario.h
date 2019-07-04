typedef struct 		objlist
{
	SDL_Surface		*ptr;
	struct objlist 	*next;
} 					Objlist;

void				init(SDL_Window **win, SDL_Surface **screen);