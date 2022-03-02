#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h> // for open flags
#include <time.h> // for time measurement
#include <assert.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

void my_exec(char* cmd, char** argv)
{
    int pipefd[2], f;

    if (pipe(pipefd) < 0)
        perror("pipe creation failed");

    f = fork();
    printf("%d\n", f);

    if (f == 0) {
        printf("Это процесс ребенок\n");
        if (dup2(pipefd[1], STDOUT_FILENO) < 0)
            perror("dup2 failed");
        close(pipefd[0]);

    } else {
        if (dup2(pipefd[0], STDIN_FILENO) < 0)
            perror("dup2 failed");

        close(pipefd[1]);

        if (execvp(cmd, argv) < 0)
            perror("execvp failed");
        }
}

int main(int argc, char** argv)
{
    assert(strcmp(argv[argc-1], "-"));

    int i;
    for (i = argc-1; i >= 1; i--) {
        if (!strcmp(argv[i], "-")) {
            argv[i] = NULL;
            my_exec(argv[i+1], &argv[i+1]);
            argc = i;
        }
    }

    if (execvp(argv[0], &argv[1]) == -1)
        perror("execvp failed");

    return 0;
}