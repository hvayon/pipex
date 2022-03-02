#include "pipex.h"

//----delete----
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//----delete----


int child_process(char *cmd1, t_pipex *data, int *pipefd, char **envp)
{
    char *tmp;
    char *cmp;
    char **path;
    int i = 0;

    path = data->cmp_path;

    if (dup2(data->infile, STDIN_FILENO) == -1)
        exit (0);
    if (dup2(pipefd[1], STDOUT_FILENO)== -1)
        perror("dup2 failed");
    

    close(pipefd[0]);
    close(data->infile);

    while(path[i])
    {
        tmp = ft_strjoin(path[i], "/");
        if (!tmp)
            return(0);
        cmp = ft_strjoin(tmp, cmd1);
        printf("%s\n", cmd1);
        if (!cmp)
            return(0);
        if (!access(cmp, 0)) //должен быть равен нулю
            return(*cmp);
        i++;
    }
    execve(cmp, &cmd1, envp);
    return EXIT_SUCCESS;
}

int parent_process(char *cmd2, t_pipex *data, int *pipefd, char **envp)
{
    int status;
    char **path;
    char *tmp;
    char *cmp;

    int i = 0;
    
    path = data->cmp_path;
    waitpid(data->pid1, &status, 0); //родитель ждет пока завершиться потомок
    if (dup2(pipefd[0], STDIN_FILENO) == -1)
        exit (0);
    if (dup2(data->outfile, STDOUT_FILENO) < 0)
        perror("dup2 failed");
    printf("Это процесс-родитель\n");
    close(pipefd[1]);
    close(data->outfile);
    while(path[i])
    {
        tmp = ft_strjoin(path[i], "/");
        if (!tmp)
            return(0);
        cmp = ft_strjoin(tmp, cmd2);
        printf("%s\n", cmp);
        if (!cmp)
            return(0);
        if (!access(cmp, 0))
            return(*cmp); //file present
        i++;
    }
    execve(cmp, &cmd2, envp);
    return EXIT_SUCCESS;
}

int main(int argc, char **argv, char **envp)
{
    int pipefd[2];
    t_pipex *data;
    data = (t_pipex *)malloc(sizeof(t_pipex));
    if (argc != 5)
        return (0);
    data->infile = open(argv[1], O_RDONLY);
    if (data->infile == -1)
        return (0);
    data->outfile = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0777); // чтетение и запись
    if (data->outfile == -1) 
        return (0);
    if (*envp == 0)
        return (0);
    if (envp != 0)
    {
        while(envp != 0)
        {
            if (ft_strncmp("PATH=", *envp, 5) == 0)
            {
                data->path = *(envp);
                break;
            }
            envp++;
        }
    }
    data->cmp_path = ft_split(data->path, ':');
    pipe(pipefd);
    data->pid1 = fork(); //определение идентификатора процесса
    if (data->pid1 < 0)
        perror("Fork: ");
    if (data->pid1 == 0) // это процесс потомок
        child_process(argv[2], data, pipefd, envp);
    else
        parent_process(argv[3], data, pipefd, envp);
    return(0);
}