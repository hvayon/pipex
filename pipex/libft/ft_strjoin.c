/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvayon <hvayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 19:28:07 by hvayon            #+#    #+#             */
/*   Updated: 2022/05/24 19:46:27 by hvayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
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
		exit (1);
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
