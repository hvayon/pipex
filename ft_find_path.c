/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natalia <natalia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 21:09:54 by natalia           #+#    #+#             */
/*   Updated: 2022/03/10 21:33:07 by natalia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_find_path_in_envp(char **envp)
{
	char	*path_envp;

	path_envp = NULL;
	while (envp != 0)
	{
		if (ft_strncmp("PATH=", *envp, 5) == 0)
		{
			path_envp = *(envp);
			path_envp = &path_envp[5];
			break ;
		}
		envp++;
	}
	return (path_envp);
}

char	**ft_find_path(char **envp)
{
	char	*path_envp;
	char	**paths;
	int		i;

	path_envp = NULL;
	paths = NULL;
	i = 0;
	path_envp = ft_find_path_in_envp(envp);
	if (path_envp == NULL)
		return (NULL);
	paths = ft_split(path_envp, ':');
	while (paths[i])
	{
		paths[i] = ft_strjoin(paths[i], "/");
		i++;
	}
	return (paths);
}

