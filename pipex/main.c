/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvayon <hvayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 23:02:20 by natalia           #+#    #+#             */
/*   Updated: 2022/03/12 15:57:03 by hvayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_check_argc(int argc)
{
	if (argc != 5)
	{
		write(1, "not correct input\n", 19);
		return (1);
	}
	return (0);
}

int	ft_check_path(t_pipex *data)
{
	if (data->paths == NULL)
	{
		write(1, "pipex: PATH not found\n", 23);
		free(data);
		return (1);
	}
	return (0);
}

int	ft_open_fd(int argc, char **argv, t_pipex *data)
{
	data->infile = open(argv[1], O_RDONLY, 0777);
	data->outfile = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (data->outfile < 0 || data->infile < 0)
	{
		perror("pipex");
		free(data);
		return (1);
	}
	return (0);
}

void	ft_free_arg(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		free(arg[i]);
		i++;
	}
	free(arg);
}

int	main(int argc, char **argv, char **envp)
{
	int		pipefd[2];
	t_pipex	*data;

	if (ft_check_argc(argc))
		return (1);
	data = (t_pipex *)malloc(sizeof(t_pipex));
	data->paths = ft_find_path(envp);
	if (ft_check_path(data))
		return (1);
	if (ft_open_fd(argc, argv, data))
		return (1);
	pipe(pipefd);
	data->pid = fork();
	if (data->pid == 0)
		child_process(pipefd, argv[2], data, envp);
	else
		parent_process(pipefd, argv[3], data, envp);
	ft_free_arg(data->paths);
}
