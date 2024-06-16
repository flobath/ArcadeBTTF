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
	make -C ./src/games/snake
	ln -sf ./src/games/snake/arcade_snake.so $(LIB_FOLDER)/arcade_snake.so

graphicals:
	make -C ./src/graphical/ncurse
	ln -sf ./src/graphical/ncurse/arcade_ncurses.so $(LIB_FOLDER)/arcade_ncurses.so

clean:
	make clean -C ./src
	make clean -C ./src/games/snake
	make clean -C ./src/graphical/ncurse
	rm -f $(NAME)
	rm -f $(LIB_FOLDER)/arcade_snake.so
	rm -f $(LIB_FOLDER)/arcade_ncurses.so

fclean: clean
	make fclean -C ./src
	make fclean -C ./src/games/snake
	make fclean -C ./src/graphical/ncurse

re: fclean all

.PHONY: all core games graphicals clean fclean re