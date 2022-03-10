# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: natalia <natalia@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/07 11:58:06 by natalia           #+#    #+#              #
#    Updated: 2022/03/07 12:00:47 by natalia          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

HEADER = pipex.h
NAME = pipex
SRC = 	main.c \

CC = cc 
FLAGS = -Wall -Wextra -Werror

DIR_LIB = libft
LIB = $(DIR_LIB)/libft.a

OBJ = $(SRC:.c=.o)
D_FILES = $(patsubst %c,%d, $(SRC) $(SRC_BONUS))

all: lib $(NAME)

lib:
	@make -C libft

$(NAME) : $(OBJ)
	$(CC) $(FLAGS) $(OBJ) $(LIB) -o $(NAME)

%.o: %.c $(HEADER) 
	$(CC) $(FLAGS) -c $< -o $@ -MD

include $(wildcard $(D_FILES))

clean:
	rm -f $(OBJ) $(D_FILES)
	make -C $(DIR_LIB) clean

fclean: clean
	rm -f $(NAME)
	make -C $(DIR_LIB) fclean

re:	fclean all

.PHONY: all clean fclean re