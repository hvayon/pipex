/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvayon <hvayon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 17:43:42 by hvayon            #+#    #+#             */
/*   Updated: 2022/05/23 19:58:40 by hvayon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <sys/types.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef struct s_pipex
{
	char	**paths;
	int		infile;
	int		outfile;
	pid_t	pid;
	int		here_doc;
}				t_pipex;

char	*get_next_line(int fd);
char	*ft_strjoin_gnl(char *s1, char *s2);
size_t	ft_strlen(char *str);
char	*ft_strchr(char *s, int c);
char	*ft_read_to_remainder(int fd, char *remainder);
char	*ft_new_remainder(char *remainder);
char	*ft_get_line(char *remainder);
void	ft_putstr_fd(char *s, int ft);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
void	ft_putstr_fd(char *s, int ft);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(char const *s, char c);
char	**ft_find_path(char **envp);
void	ft_check_command(char *cmd, t_pipex *data, char **envp);
void	first_comm_proccess(t_pipex *data, char *comm, char **envp, int fd);
int		ft_heredoc(int argc, char **argv, t_pipex *data, int *i);

#endif