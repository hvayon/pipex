/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natalia <natalia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 23:02:20 by natalia           #+#    #+#             */
/*   Updated: 2022/03/10 22:38:43 by natalia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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