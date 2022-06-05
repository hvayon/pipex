# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hvayon <hvayon@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/07 11:58:06 by natalia           #+#    #+#              #
#    Updated: 2022/03/12 15:36:45 by hvayon           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

HEADER = pipex.h
NAME = pipex
SRC = 	main.c ft_find_path.c \
		ft_check_sistem_bin.c \
		ft_child_process.c \
		ft_parent_process.c \

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