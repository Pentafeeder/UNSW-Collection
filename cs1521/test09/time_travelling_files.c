#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {


    for (int i = 1; i < argc; i++) {

        struct stat file_stat;

        stat(argv[i], &file_stat);

        struct timespec last_accessed = file_stat.st_atim;
        struct timespec last_modified = file_stat.st_mtim;

        time_t current_time = time(NULL);



        if (current_time < last_accessed.tv_sec || current_time < last_modified.tv_sec) {
            printf("%s has a timestamp that is in the future\n", argv[i]);
        }

    }
    

    return 0;
}