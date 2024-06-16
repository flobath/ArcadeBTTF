##
## EPITECH PROJECT, 2024
## ArcadeBTTF
## File description:
## Makefile
##

NAME	=	arcade_ncurses.so

CXX		=	g++

CXXFLAGS 	=	-std=c++20 -Wall -Wextra -I../../common -I../include -fPIC -fno-gnu-unique

SRC		=	./Ncurse.cpp \

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
