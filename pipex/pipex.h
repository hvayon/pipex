/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvayon <hvayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 21:08:12 by natalia           #+#    #+#             */
/*   Updated: 2022/05/23 20:15:45 by hvayon           ###   ########.fr       */
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
	pid_t	pid;
}				t_pipex;

char	**ft_find_path(char **envp);
char	*ft_check_sistem_bin(char *cmd, char ***commands, char **paths);
char	**ft_commands_for_full_path(char *cmd, char **commands);
void	child_process(int pipefd[2], char *cmd1, t_pipex *data, char **envp);
void	parent_process(int pipefd[2], char *cmd2, t_pipex *data, char **envp);
void	ft_free_arg(char **arg);
void	ft_check_command(char **cmd1, char ***commands, \
						char **path, t_pipex **data);

#endif