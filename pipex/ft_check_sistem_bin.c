/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_sistem_bin.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvayon <hvayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 21:40:19 by natalia           #+#    #+#             */
/*   Updated: 2022/05/23 20:18:43 by hvayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_check_sistem_bin(char *cmd, char ***comands, char **paths)
{
	int		i;
	char	*path;

	i = 0;
	path = NULL;
	*comands = ft_split(cmd, ' ');
	while (paths && *paths)
	{
		path = ft_strjoin(*paths, (*comands)[0]);
		if (!path)
			exit(0);
		if (access(path, F_OK) == 0)
			return (path);
		paths++;
	}
	return (NULL);
}

char	**ft_commands_for_full_path(char *cmd, char **commands)
{
	char	**path;
	int		i;

	path = NULL;
	i = 0;
	commands = ft_split(cmd, '/');
	if (!commands)
	{
		free(commands);
	}
	while (commands[i])
	{
		i++;
	}
	i--;
	commands = ft_split((commands)[i], ' ');
	return (commands);
}
