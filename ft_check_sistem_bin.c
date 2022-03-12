/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_sistem_bin.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natalia <natalia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 21:40:19 by natalia           #+#    #+#             */
/*   Updated: 2022/03/10 21:47:42 by natalia          ###   ########.fr       */
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

char	**ft_comands_for_full_path(char *cmd, char **comands)
{
	char	**path;
	int		i;

	path = NULL;
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
