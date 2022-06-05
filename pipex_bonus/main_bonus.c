/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvayon <hvayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 14:40:56 by hvayon            #+#    #+#             */
/*   Updated: 2022/05/24 19:34:11 by hvayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_check_path(t_pipex *data)
{
	if (data->paths == NULL)
	{
		write(2, "pipex: PATH not found\n", 23);
		return (1);
	}
	return (0);
}

int	ft_open_fd(int argc, char **argv, t_pipex *data, int flag)
{
	if (flag == 1)
	{
		data->infile = open(".here_doc", O_CREAT | O_RDWR | O_APPEND, 0777);
		dup2(data->infile, 1);
	}
	if (flag == 0)
	{
		data->infile = open(argv[1], O_RDONLY, 0777);
		data->outfile = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0777);
		dup2(data->infile, 0);
		dup2(data->outfile, 1);
	}
	if (data->outfile < 0 || data->infile < 0)
	{
		perror("pipex");
		exit(126);
	}
	return (0);
}

int	ft_check_pid_status(t_pipex *data)
{
	pid_t	value;
	int		status;
	int		m;

	value = 0;
	while (value != -1)
	{
		value = waitpid(-1, &status, 0);
		if (value == data->pid)
			m = status;
	}
	return (WEXITSTATUS(m));
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*data;
	int		i;

	if (argc < 5)
		return (1);
	data = (t_pipex *)malloc(sizeof(t_pipex));
	data->paths = ft_find_path(envp);
	data->here_doc = 0;
	if (ft_check_path(data))
		return (1);
	if (ft_strncmp(argv[1], "here_doc", 8) == 0 && ft_strlen(argv[1]) == 8)
		data->here_doc = 1;
	if (ft_open_fd(argc, argv, data, data->here_doc))
		return (1);
	i = 2;
	if (data->here_doc == 1)
		ft_heredoc(argc, argv, data, &i);
	first_comm_proccess(data, argv[i++], envp, data->infile);
	while (i < argc - 2)
		first_comm_proccess(data, argv[i++], envp, 1);
	ft_check_command(argv[i], data, envp);
	ft_check_pid_status(data);
	exit(0);
}
