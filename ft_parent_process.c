/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parent_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvayon <hvayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 14:01:47 by hvayon            #+#    #+#             */
/*   Updated: 2022/03/12 15:05:40 by hvayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	parent_process(int pipefd[2], char *cmd2, t_pipex *data, char **envp)
{
	int		status;
	char	*path;
	char	**comands;

	path = NULL;
	comands = NULL;
	waitpid(data->pid, &status, 0);
	comands = ft_split(cmd2, ' ');
	ft_check_comand(&cmd2, &comands, &path, &data);
	if (dup2(data->outfile, STDOUT_FILENO) == -1)
		perror("pipex");
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
		perror("pipex");
	close(pipefd[1]);
	close(data->outfile);
	execve(path, comands, envp);
	ft_free_arg(comands);
}
