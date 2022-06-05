/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvayon <hvayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 19:41:41 by hvayon            #+#    #+#             */
/*   Updated: 2022/05/24 20:16:48 by hvayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_make_heredoc(char **argv)
{
	char	*line;

	while (1)
	{
		ft_putstr_fd("pipe heredoc> ", STDIN_FILENO);
		line = get_next_line(0);
		if (!line)
			return (1);
		if (ft_strncmp(line, argv[2], ft_strlen(argv[2])) == 0 && \
			ft_strlen(line) == ft_strlen(argv[2]) + 1)
			break ;
		write(STDOUT_FILENO, line, ft_strlen(line));
		free(line);
	}
	return (0);
}

int	ft_open_heredoc(int argc, char **argv, t_pipex *data, int *i)
{
	data->infile = open(".here_doc", O_RDONLY, 0777);
	data->outfile = open(argv[argc - 1], O_CREAT | O_RDWR | O_APPEND, 0777);
	if (data->outfile < 0 || data->infile < 0)
	{
		perror("pipex");
		return (1);
	}
	dup2(data->infile, 0);
	dup2(data->outfile, 1);
	*i += 1;
	unlink(".here_doc");
	return (0);
}

int	ft_heredoc(int argc, char **argv, t_pipex *data, int *i)
{
	ft_make_heredoc(argv);
	ft_open_heredoc(argc, argv, data, i);
	return (0);
}
