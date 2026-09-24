#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

#define PERMISSION_LENGTH 11


void stat_file(char *pathname);

int main(int argc, char *argv[]) {
    
    for (int i = 1; i < argc; i++) {
        stat_file(argv[i]);
    }

    return 0;
}

void stat_file(char *pathname) {
    struct stat s;
    if (stat(pathname, &s) != 0) {
        perror(pathname);
        exit(1);
    }

    mode_t mode = s.st_mode;

    char permission[] = "-rwxrwxrwx";

    if (mode & 0x4000) {
        permission[0] = 'd';
    }

    for (int i = 1; i < PERMISSION_LENGTH - 1; i++) {
        if (!(mode & (1 << (i - 1)))) {
            permission[PERMISSION_LENGTH - i - 1] = '-';
        }
    }

    printf("%s %s\n", permission, pathname);
}