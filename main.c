/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natalia <natalia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 23:02:20 by natalia           #+#    #+#             */
/*   Updated: 2022/03/06 21:20:24 by natalia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

char    **ft_find_path(char **envp)
{
    char *path_envp;
    char **paths;
    int i;

    i = 0;
    if (envp != 0)
    {
        while(envp != 0)
        {
            if (ft_strncmp("PATH=", *envp, 5) == 0)
            {
                path_envp = *(envp);
                path_envp = &path_envp[5];
                break;
            }
            envp++;
        }
    }
    if (path_envp != 0)
        paths = ft_split(path_envp, ':');
    while(paths[i])
    {
        paths[i] = ft_strjoin(paths[i], "/");
        i++;
    }
    return(paths);
}

void ft_check_sistem_bin(char *cmd, char ***comands,
		char **envp, char **path)
{
    char *tmp;
    int i;
    char **paths;
    i = 0;

    paths = ft_find_path(envp);
    *comands = ft_split(cmd, ' ');
    while(paths && *paths)
    {
        *path = ft_strjoin(*paths, (*comands)[0]);
        if (!*path)
            exit(0);
        if (access(*path, F_OK) == 0)
            break ;
        paths++;
    }
}

void child_process(int pipefd[2], char *cmd1, t_pipex *data, char **envp)
{
    int i;
    char **comands;
    char *path;
    char **paths;
    i = 0;

    if (dup2(data->infile, STDIN_FILENO) == -1)
        printf("dup2 error");
    if (dup2(pipefd[1],STDOUT_FILENO) == -1)
        printf("dup2 error");
    close(pipefd[0]);
    close(data->infile);
    ft_check_sistem_bin(cmd1, &comands, envp, &path);
    execve(path, comands, envp);
}

void parent_process(int pipefd[2], char *cmd2, t_pipex *data, pid_t pid, char **envp)
{
    int status;
    char *buf;
    char *path;
    char **comands;


    buf = malloc(10);
    waitpid(pid, &status, 0);
    if (dup2(data->outfile, STDOUT_FILENO) == -1)
        perror("dup2 failed");
    if (dup2(pipefd[0], STDIN_FILENO) == -1)
        perror("dup2 failed");
    close(pipefd[1]);
    close(data->outfile);
    ft_check_sistem_bin(cmd2, &comands, envp, &path);
    execve(path, comands, envp);
}

int main(int argc, char **argv, char **envp)
{
    int pipefd[2];
    pid_t pid;
    t_pipex *data;
    char **path;
    
    if (argc != 5)
        return (0);
    data->infile = open(argv[1], O_RDONLY, 0777);
    data->outfile = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0777); // чтетение и запись
    if (data->outfile < 0 || data->infile < 0)
    {
        printf("Open error");
        return (0);
    }
    pipe(pipefd);
    pid = fork();
    if (!pid)
        child_process(pipefd, argv[2], data, envp);
    else
        parent_process(pipefd,argv[3], data, pid, envp);
}