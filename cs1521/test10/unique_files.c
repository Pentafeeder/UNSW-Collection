#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define FALSE 0
#define TRUE 1

int main(int argc, char **argv)
{

    ino_t unique_inode[argc];
    int unique_found = 0;

    for (int i = 1; i < argc; i++) {
        
        struct stat file_stat;

        if (stat(argv[i], &file_stat) != 0) {
            perror(argv[i]);
            exit(1);
        }

        ino_t inode = file_stat.st_ino;

        int unique = TRUE;
        for (int j = 0; j < unique_found; j++) {
            if  (inode == unique_inode[j]) {
                unique = FALSE;
            }
        }

        if (unique == TRUE) {
            unique_inode[unique_found] = inode;
            printf("%s\n", argv[i]);
            unique_found++;
        }

    }

    return EXIT_SUCCESS;
}
