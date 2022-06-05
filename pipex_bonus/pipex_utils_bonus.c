/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvayon <hvayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 17:46:01 by hvayon            #+#    #+#             */
/*   Updated: 2022/05/24 19:43:14 by hvayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int			n;
	size_t		h;

	if (!(*needle))
		return ((char *)haystack);
	if (len == 0)
		return (NULL);
	h = 0;
	while (haystack[h] && h < len)
	{
		n = 0;
		if (haystack[h] == needle[n])
		{
			while (n + h < len && haystack[n + h] == needle[n])
			{
				n++;
				if (!needle[n])
					return ((char *)&haystack[h]);
			}
		}
		h++;
	}
	return (NULL);
}

void	ft_putstr_fd(char *s, int ft)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i] != '\0')
	{
		write(ft, &s[i], 1);
		i++;
	}
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	l1;
	size_t	l2;
	char	*new;

	if (!s1 || !s2)
		return (NULL);
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	new = (char *)malloc(sizeof(char) * (l1 + l2 + 1));
	if (!new)
		exit(1);
	i = -1;
	while (++i < l1)
		new[i] = s1[i];
	i = 0;
	while (l2--)
	{
		new[l1 + i] = s2[i];
		i++;
	}
	new[l1 + i] = '\0';
	return (new);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] && s2[i] && i < n - 1 && s1[i] == s2[i])
		i++;
	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
}
