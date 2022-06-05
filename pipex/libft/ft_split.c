/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvayon <hvayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 15:05:01 by hvayon            #+#    #+#             */
/*   Updated: 2022/05/24 19:44:07 by hvayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_wcount(char const *s, char c)
{
	int	flag;
	int	count;
	int	i;

	i = 0;
	count = 0;
	flag = 0;
	while (s[i] != '\0')
	{
		if ((s[i] != c) && (flag == 0))
		{
			count++;
			flag = 1;
		}
		else if (s[i] == c && flag == 1)
			flag = 0;
		i++;
	}
	return (count);
}

static char	*ft_fill_word(char const *s, char *word, int count, int *j)
{
	int	i;

	if (word)
	{	
		i = 0;
		while (i < count)
		{
			word[i] = s[*j];
			i++;
			(*j)++;
		}
		word[i] = '\0';
	}
	return (word);
}

static char	*ft_next_word(char const *s, char c, int *j)
{
	int		len;
	char	*word;
	int		tmp;

	while (s[*j] == c && s[*j])
	{
		(*j)++;
	}
	tmp = *j;
	len = 0;
	while (s[tmp] != c && s[tmp])
	{
		len++;
		tmp++;
	}
	word = (char *)malloc(sizeof(char) * (len + 1));
	if (!word)
		exit (1);
	return (ft_fill_word(s, word, len, j));
}

static char	**ft_free_malloc(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int		count;
	int		i;
	int		j;
	char	**words_arr;

	if (!s)
		return (NULL);
	count = ft_wcount(s, c);
	words_arr = (char **)malloc(sizeof(char *) * count + 1);
	if (!words_arr)
		exit (1);
	words_arr[count] = NULL;
	i = 0;
	j = 0;
	while (i < count)
	{
		words_arr[i] = ft_next_word(s, c, &j);
		if (!words_arr[i])
			return (ft_free_malloc(words_arr));
		i++;
	}
	return (words_arr);
}
