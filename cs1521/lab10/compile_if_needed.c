// compile .c files specified as command line arguments
//
// if my_program.c and other_program.c is speicified as an argument then the follow two command will be executed:
// /usr/local/bin/dcc my_program.c -o my_program
// /usr/local/bin/dcc other_program.c -o other_program

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <spawn.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define DCC_PATH "/usr/local/bin/dcc"

extern char **environ;

int main(int argc, char **argv)
{
    pid_t pid;
    
    for (int i = 1; i < argc; i++) {
        char *spawn_argv[5];

        spawn_argv[0] = DCC_PATH;
        spawn_argv[4] = NULL;
        
        int filename_len = strlen(argv[i]);
        char exec_file[filename_len - 1];
        exec_file[filename_len - 2] = '\0';

        strncpy(exec_file, argv[i], filename_len - 2);

        spawn_argv[1] = argv[i];
        spawn_argv[2] = "-o";
        spawn_argv[3] = exec_file;



        struct stat stats_c;

        if (stat(argv[i], &stats_c) != 0) {
            perror(argv[i]);
            exit(1);
        }

        struct timespec last_c_modified = stats_c.st_mtim;

        struct stat stats_exe;  
        struct timespec last_b_modified = last_c_modified;

        if (stat(spawn_argv[3], &stats_exe) == 0) {
            last_b_modified = stats_exe.st_mtim;
        } 

        

        if (last_c_modified.tv_nsec >= last_b_modified.tv_nsec) {

            if (posix_spawn(&pid, DCC_PATH, NULL, NULL, spawn_argv, environ) != 0) {
                perror("spawn");
                exit(1);
            }

            printf("running the command: \"%s %s %s %s\"\n", DCC_PATH, argv[i], spawn_argv[2], spawn_argv[3]);
            int exit_status;
            if (waitpid(pid, &exit_status, 0) == -1) {
                perror("waitpid");
                exit(1);
            }
        } else {
            printf("%s does not need compiling\n", argv[i]);
        }




        

    }
    
   

    return EXIT_SUCCESS;
}
