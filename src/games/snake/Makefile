##
## EPITECH PROJECT, 2024
## B-OOP-400-NAN-4-1-arcade-florian.gaudin
## File description:
## Makefile
##


NAME	=	arcade_snake.so

CXX		=	g++

CXXFLAGS 	=	-std=c++20 -Wall -Wextra -I../../common -I../abstract -fPIC -fno-gnu-unique

SRC		=	./Snake.cpp \
            ../../TextSpriteHelper.cpp
OBJ		=	$(SRC:%.cpp=%.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(OBJ) -shared -o $(NAME) -lncurses

debug: $(OBJ)
	$(CXX) $(OBJ) -shared -o $(NAME) -lncurses -g

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:	fclean $(NAME)
