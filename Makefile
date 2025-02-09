##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## The makefile to compile the project.
##

NAME	=	game_jam

SRCS	=	$(shell find . -type f -name '*.c')

all	:	$(NAME)

$(NAME)	:
		gcc -o $(NAME) $(SRCS) -l csfml-graphics -l csfml-system -l csfml-audio -lcsfml-window -lm

clean	:
		rm -rf $(NAME)

fclean	:	clean

re	:	fclean	all
