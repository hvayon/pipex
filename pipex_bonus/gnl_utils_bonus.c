/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvayon <hvayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 12:29:45 by hvayon            #+#    #+#             */
/*   Updated: 2022/05/21 16:26:40 by hvayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin_gnl(char *remainder, char *buf)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!remainder)
	{
		remainder = (char *)malloc(1 * sizeof(char));
		remainder[0] = '\0';
	}
	if (!remainder || !buf)
		return (NULL);
	str = malloc(sizeof(char) * ((ft_strlen(remainder) + ft_strlen(buf)) + 1));
	if (str == NULL)
		return (NULL);
	i = -1;
	j = 0;
	if (remainder)
		while (remainder[++i] != '\0')
			str[i] = remainder[i];
	while (buf[j] != '\0')
		str[i++] = buf[j++];
	str[ft_strlen(remainder) + ft_strlen(buf)] = '\0';
	free(remainder);
	return (str);
}

char	*ft_strchr(char *s, int c)
{
	if (s && c)
	{
		while (*s != c)
		{
			if (*s == '\0')
				return (NULL);
			s++;
		}
	}
	return (s);
}

char	*ft_get_line(char *remainder)
{
	int		i;
	char	*line;

	i = 0;
	if (!remainder[i])
		return (NULL);
	while (remainder[i] != '\n' && remainder[i])
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (remainder[i] && remainder[i] != '\n')
	{
		line[i] = remainder[i];
		i++;
	}
	if (remainder[i] == '\n')
	{
		line[i] = remainder[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_new_remainder(char *remainder)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (remainder[i] && remainder[i] != '\n')
		i++;
	if (!remainder[i])
	{
		free(remainder);
		return (NULL);
	}
	str = (char *)malloc(sizeof(char) * (ft_strlen(remainder) - i + 1));
	if (!str)
		return (NULL);
	i++;
	j = 0;
	while (remainder[i])
		str[j++] = remainder[i++];
	str[j] = '\0';
	free(remainder);
	return (str);
}
