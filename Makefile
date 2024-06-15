##
## EPITECH PROJECT, 2024
## arcade_bootstrap
## File description:
## Makefile
##

NAME	=	./arcade

LIB_FOLDER	=	./src/lib

all: core games graphicals

core:
	make arcade -C ./src
	ln -sf ./src/arcade $(NAME)

games:

graphicals:

clean:
	make clean -C ./src

fclean: clean
	make fclean -C ./src

re: fclean all

.PHONY: all core games graphicals clean fclean re