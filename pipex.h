
#ifndef PIPEX_H
# define PIPEX_H

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h> // delete
#include "libft/libft.h"

typedef	struct s_pipex
{
	char **paths;

	int infile;
	int outfile;
}				t_pipex;

#endif