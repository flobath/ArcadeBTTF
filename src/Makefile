##
## EPITECH PROJECT, 2024
## ArcadeBTTF
## File description:
## Makefile
##

NAME = arcade


INCLUDE_FLAGS	=	-I./common -I./core

SRC = Main.cpp \
	  AScreen.cpp \
	  Core.cpp \
	  Libs.cpp \

OBJ = $(SRC:.cpp=.o)

CXX = g++

CXXFLAGS 	=	-std=c++20 -Wall -Wextra -fno-gnu-unique $(INCLUDE_FLAGS) -g -fPIC

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re