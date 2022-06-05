# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: natalia <natalia@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/22 23:13:38 by hvayon            #+#    #+#              #
#    Updated: 2022/02/26 19:34:05 by natalia          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

HEADER			= libft.h
NAMES			= 	ft_strncmp.c ft_split.c ft_strjoin.c \
					ft_strlen.c

OBJS			= $(NAMES:.c=.o)
D_FILES = $(patsubst %c,%d, $(NAMES))

CC				= cc
CFLAGS			= -Wall -Wextra -Werror
NAME			= libft.a

all:  $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $?

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -MD

include $(wildcard $(D_FILES))

clean:
	rm -f $(OBJS) $(BONUS_OBJS) $(D_FILES)

fclean: clean
	rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re