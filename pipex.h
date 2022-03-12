/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natalia <natalia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 21:08:12 by natalia           #+#    #+#             */
/*   Updated: 2022/03/10 22:10:37 by natalia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PIPEX_H
# define PIPEX_H

# include <sys/types.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "libft/libft.h"

typedef struct s_pipex
{
	char	**paths;
	int		infile;
	int		outfile;
}				t_pipex;

char    **ft_find_path(char **envp);
char	*ft_check_sistem_bin(char *cmd, char ***comands, char **paths);
char    **ft_comands_for_full_path(char *cmd, char **comands);
void	child_process(int pipefd[2], char *cmd1, t_pipex *data, char **envp);

#endif