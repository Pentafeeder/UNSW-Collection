#include <stdio.h>
#include <pthread.h>
#include <spawn.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_BYTES 1024

extern char **environ;


int main(int argc, char *argv[]) {

    char string[MAX_BYTES];
    
    while (scanf("%s", string) != EOF) {
        int length = strlen(string);
        string[length] = '\0';
    
        char *spawn_argv[] = {argv[1], string, NULL};

        
        pid_t spawn_pid;
        if (posix_spawn(&spawn_pid, argv[1], NULL, NULL, spawn_argv, environ) != 0) {
            perror("spawn");
            exit(1);
        }

        int exit_status;
        if (waitpid(spawn_pid, &exit_status, 0) == -1) {
            perror("waitpid");
            exit(1);
        }
    }

    return EXIT_SUCCESS;
}