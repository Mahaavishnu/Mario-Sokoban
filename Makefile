SHELL=/bin/sh
CC=gcc    #Commande du compilateur
CFLAGS=-O3 -I/usr/local/include/SDL2 #Option d'optimisation du programme
LDLIBS=-lSDL2 -lSDL2_image -ljpeg #-lSDL_mixer #Linker
EXEC=mario  #Nom du programme à modifier

src = main.c errors_handling.c jeu.c editeur.c

obj = $(src:.c=.o)

all: ${EXEC}

${EXEC}: ${obj}
	${CC} $(CFLAGS) -o ${EXEC} ${obj} ${LDLIBS}

${obj}: %.o:%.c
	${CC} $(CFLAGS) -c $^

.PHONY: clean fclean re

clean:	
	rm -rf ${obj}

fclean: clean
	rm -rf ${EXEC}

re: fclean all
