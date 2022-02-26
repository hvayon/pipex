
#ifndef PIPEX_H
# define PIPEX_H

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h> // delete
#include "libft/libft.h"

typedef	struct s_pipex
{
	char *path; //путь
	char **cmp_path; //разделены сплитом
	pid_t pid1; //идентификатор процесса
	pid_t pid2;
	int infile;
	int outfile;
}				t_pipex;

#endif