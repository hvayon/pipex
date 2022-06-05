# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hvayon <hvayon@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/15 15:26:54 by hvayon            #+#    #+#              #
#    Updated: 2022/05/24 19:37:28 by hvayon           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	pipex
HEAD	=	pipex_bonus.h
CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -MMD
SRC		=	main_bonus.c gnl_bonus.c gnl_utils_bonus.c \
			pipex_utils_bonus.c ft_find_path_bonus.c \
			ft_split_pipex_bonus.c first_comm_proccess_bonus.c \
			ft_check_command_bonus.c ft_heredoc_bonus.c \

OBJ		=	$(SRC:%.c=%.o)
D_FILES =	$(SRC:%.c=%.d)
RM		=	rm -f
all: $(NAME)
$(NAME): $(OBJ)
			$(CC) $(CFLAGS) $(OBJ) -o $@
%.o:	%.c
		$(CC) $(CFLAGS) -I $(HEAD) -c $< -o $@

include $(wildcard $(D_FILES))

clean:
	@$(RM) $(OBJ) $(D_FILES)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus