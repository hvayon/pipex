#include "pipex.h"

//----delete----
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
//----delete----

int child_process(char *cmd1, t_pipex *data, int pipefd[2])
{
    char *tmp;
    char *cmd;
    int check;
    int check2;

    if (dup2(data->infile, 0) == -1)
        return (0);
    check2 = dup2(pipefd[1], 0);   
    close(pipefd[0]);
    close(data->infile);
    if (check < 0 || check2 < 0) 
        exit (0);
    
    //cmd = make_cmd;
    //написать функцию, в которой проверяем, что нам не дали путь целиком
    while(data->cmp_path)
    {
        tmp = ft_strjoin(*(data->cmp_path), "/"); //проверка на ошибку
        if (!tmp)
            free(tmp);
            return(0);
        cmd = ft_strjoin(tmp, cmd1);
        if (!cmd)
            free(tmp);
            return(0);
        if (!access(cmd, 0))
            return (0);
    }
    printf("Это процесс-потомок\n");
    return EXIT_SUCCESS;
}

int parent_process(char *cmd1, t_pipex *data, int pipefd[2])
{
    int status;
    
    waitpid(data->pid1, &status, 0);
    printf("Это процесс-родитель\n");
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
    data->outfile = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644); // чтетение и запись
    if (data->outfile == -1) 
        return (0);
    if (*envp == 0)
        return (0);
    if (envp != 0)
    {
        while(*envp != NULL)
        {
            //printf("%s\n", *envp); // печать окружения
            if (ft_strncmp("PATH=", *envp, 5) == 0)
            {
                data->path = *(envp);
                data->path = &(data->path[6]);
                //printf("Найденный PATH = %s\n", data->path);
                break;
            }
            envp++;
        }
    }
    data->cmp_path = ft_split(data->path, ':');
    printf("Результат работы split = %s\n", data->cmp_path[1]);
    
    pipe(pipefd);

    data->pid1 = fork(); //определение идентификатора процесса
    printf("pid1 - %d\n", data->pid1);
    if (data->pid1 < 0)
        perror("Fork: ");
    if (data->pid1 == 0) // это процесс потомок
    {
        child_process(argv[2], data, pipefd);
    }
    else
        parent_process(argv[2], data, pipefd);
}