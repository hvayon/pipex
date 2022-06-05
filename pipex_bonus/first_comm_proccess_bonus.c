/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_comm_proccess_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvayon <hvayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 19:11:22 by hvayon            #+#    #+#             */
/*   Updated: 2022/05/23 20:08:29 by hvayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_error_pid(void)
{
	perror("pid error");
	exit(1);
}

void	first_comm_proccess(t_pipex *data, char *comm, char **envp, int fd)
{
	int		pipefd[2];

	pipe(pipefd);
	data->pid = fork();
	if (data->pid == -1)
		ft_error_pid();
	if (data->pid > 0)
	{
		close(pipefd[1]);
		dup2(pipefd[0], 0);
		close(pipefd[0]);
	}
	else
	{
		close(pipefd[0]);
		dup2(pipefd[1], 1);
		close(pipefd[1]);
		if (fd == 0)
			exit(1);
		else
			ft_check_command(comm, data, envp);
	}
}
