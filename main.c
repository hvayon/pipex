/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natalia <natalia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 23:02:20 by natalia           #+#    #+#             */
/*   Updated: 2022/03/10 20:53:45 by natalia          ###   ########.fr       */
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

char    **ft_comands_for_full_path(char *cmd, char **comands)
{
    char **path;
    int i;
    
    path = NULL;
    i = 0;
    comands = ft_split(cmd, '/');
    if (!comands)
    {
        free(comands);
    }
    while (comands[i])
    {
        i++;
    }
    i--;
    comands = ft_split((comands)[i], ' ');
    return (comands);
}

char    **ft_find_path(char **envp)
{
    char *path_envp;
    char **paths;
    int i;

    i = 0;
    path_envp = NULL;
    paths = NULL;
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
    if (path_envp == NULL)
        return(NULL);
    paths = ft_split(path_envp, ':');
    while(paths[i])
    {
        paths[i] = ft_strjoin(paths[i], "/");
        i++;
    }
    return(paths);
}

char *ft_check_sistem_bin(char *cmd, char ***comands, char **paths)
{
    int i;
    char *path;
    i = 0;

    path = NULL;
    *comands = ft_split(cmd, ' ');
    while(paths && *paths)
    {
        path = ft_strjoin(*paths, (*comands)[0]);
        if (!path)
            exit(0);
        if (access(path, F_OK) == 0)
            return(path);
        paths++;
    }
    return(NULL);
}

void child_process(int pipefd[2], char *cmd1, t_pipex *data, char **envp)
{
    int i;
    char **comands;
    char *path;

    i = 0;
    path = NULL;
    comands = NULL;
    comands = ft_split(cmd1, ' ');
    
    if (access(comands[0], 0) == 0)
    {
        //free comands;
        path = comands[0];
        comands = ft_comands_for_full_path(cmd1, comands);
    }
    else
    {
        comands = NULL;
        path = ft_check_sistem_bin(cmd1, &comands, data->paths);
        if (path == NULL)
        {
            write(1, "pipex: can not find comand: ", 29);
            write(1, cmd1, ft_strlen(cmd1));
            write(1, "\n", 1);
            return ;
        }
    }
    if (dup2(data->infile, STDIN_FILENO) == -1)
        perror("pipex");
    if (dup2(pipefd[1],STDOUT_FILENO) == -1)
        perror("pipex");
    close(pipefd[0]);
    close(data->infile);
    execve(path, comands, envp);
    free(comands);
}

void parent_process(int pipefd[2], char *cmd2, t_pipex *data, pid_t pid, char **envp)
{
    int status;
    char *path;
    char **comands;

    path = NULL;
    comands = NULL;
    waitpid(pid, &status, 0);
    comands = ft_split(cmd2,' ');

    if (access(comands[0], 0) == 0)
    {
        path = comands[0];
        comands = ft_comands_for_full_path(cmd2, comands);
        
    }
    else
    {
        path = ft_check_sistem_bin(cmd2, &comands, data->paths);
        if (path == NULL)
        {
            write(1, "pipex: can not find comand: ", 29);
            write(1, cmd2, ft_strlen(cmd2));
            write(1, "\n", 1);
            return ;
        }
    }
    if (dup2(data->outfile, STDOUT_FILENO) == -1)
        perror("pipex");
    if (dup2(pipefd[0], STDIN_FILENO) == -1)
        perror("pipex");
    close(pipefd[1]);
    close(data->outfile);
    execve(path, comands, envp);
    free(comands);
}

int main(int argc, char **argv, char **envp)
{
    int pipefd[2];
    pid_t pid;
    t_pipex *data;
    
    if (argc != 5)
    {
        write(1, "not correct input\n", 19);
        return (1);
    }
    data = (t_pipex *)malloc(sizeof(t_pipex));
    data->paths = ft_find_path(envp);
    if (data->paths == NULL)
    {
        write(1, "pipex: PATH not found\n", 23);
        free(data);
        return(1);
    }
    data->infile = open(argv[1], O_RDONLY, 0777);
    data->outfile = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0777); // чтетение и запись
    if (data->outfile < 0 || data->infile < 0)
    {
        perror("pipex");
        free(data);
        return (1);
    }
    pipe(pipefd);
    pid = fork();
    if (pid == 0)
        child_process(pipefd, argv[2], data, envp);
    else
        parent_process(pipefd,argv[3], data, pid, envp);
}