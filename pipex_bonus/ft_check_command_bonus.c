/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_command_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvayon <hvayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 19:19:10 by hvayon            #+#    #+#             */
/*   Updated: 2022/05/24 19:05:53 by hvayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_error_cmd(char *cmd)
{		
	write(2, "pipex: can not find command: ", 29);
	write(2, cmd, ft_strlen(cmd));
	write(2, "\n", 1);
	exit(127);
}

void	ft_error_path(char *cmd)
{
	write(2, "pipex: can not find command: ", 29);
	write(2, cmd, ft_strlen(cmd));
	write(2, "\n", 1);
	exit(127);
}

char	*ft_check_sistem_bin(char *cmd, char **comands, t_pipex *data)
{
	int		i;
	char	*path;

	i = 0;
	path = NULL;
	comands = ft_split(cmd, ' ');
	while (data->paths[i])
	{
		path = ft_strjoin(data->paths[i], (comands)[0]);
		if (!path)
			exit(0);
		if (access(path, F_OK) == 0)
			return (path);
		i++;
	}
	return (path);
}

char	**ft_comands_for_full_path(char *cmd, char **comands)
{
	int		i;

	i = 0;
	comands = ft_split(cmd, '/');
	if (!comands)
	{
		free(comands);
	}
	while (comands[i])
	{
		i++;
	}
	i--;
	comands = ft_split((comands)[i], ' ');
	return (comands);
}

void	ft_check_command(char *cmd, t_pipex *data, char **envp)
{
	char	*path;
	char	**commands;
	int		res;

	commands = NULL;
	commands = ft_split(cmd, ' ');
	if (access(commands[0], 0) == 0)
	{
		path = commands[0];
		commands = ft_comands_for_full_path(cmd, commands);
	}
	else
		path = ft_check_sistem_bin(cmd, commands, data);
	if (path == NULL)
		ft_error_path(cmd);
	res = execve(path, commands, envp);
	if (res == -1)
		ft_error_cmd(cmd);
}
