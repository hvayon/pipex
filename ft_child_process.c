/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvayon <hvayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 21:54:48 by natalia           #+#    #+#             */
/*   Updated: 2022/03/12 15:39:05 by hvayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_check_comand(char **cmd1, char ***comands, \
						char **path, t_pipex **data)
{
	if (access((*comands)[0], 0) == 0)
	{
		*path = (*comands)[0];
		*comands = ft_comands_for_full_path(*cmd1, *comands);
	}
	else
	{
		*comands = NULL;
		*path = ft_check_sistem_bin(*cmd1, &(*comands), (*data)->paths);
		if (*path == NULL)
		{
			write(1, "pipex: can not find comand: ", 29);
			write(1, *cmd1, ft_strlen(*cmd1));
			write(1, "\n", 1);
			return ;
		}
	}
}

void	child_process(int pipefd[2], char *cmd1, t_pipex *data, char **envp)
{
	int		i;
	char	**comands;
	char	*path;

	i = 0;
	path = NULL;
	comands = NULL;
	comands = ft_split(cmd1, ' ');
	ft_check_comand(&cmd1, &comands, &path, &data);
	if (dup2(data->infile, STDIN_FILENO) == -1)
		perror("pipex");
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		perror("pipex");
	close(pipefd[0]);
	close(data->infile);
	execve(path, comands, envp);
}
