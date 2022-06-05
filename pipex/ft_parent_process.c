/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parent_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvayon <hvayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 14:01:47 by hvayon            #+#    #+#             */
/*   Updated: 2022/05/23 20:22:33 by hvayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	parent_process(int pipefd[2], char *cmd2, t_pipex *data, char **envp)
{
	int		status;
	char	*path;
	char	**commands;

	path = NULL;
	commands = NULL;
	commands = ft_split(cmd2, ' ');
	ft_check_command(&cmd2, &commands, &path, &data);
	if (dup2(data->outfile, STDOUT_FILENO) == -1)
		perror("pipex");
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
		perror("pipex");
	close(pipefd[1]);
	close(data->outfile);
	execve(path, commands, envp);
	waitpid(data->pid, &status, 0);
	ft_free_arg(commands);
}
