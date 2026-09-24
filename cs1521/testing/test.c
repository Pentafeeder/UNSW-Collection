/** mycopydir.c - copies everything (files and sub-directories) from dir1 to dir2
 ** dir1 and dir2 are from the command line arguments
 ** ------------------------------------------------------------
 *
 *
 */
#include    <stdio.h>
#include    <stdlib.h>
#include    <sys/types.h>
#include    <dirent.h>
#include    <sys/stat.h>
#include    <unistd.h>
#include    <string.h>
#include    <errno.h>
#include    <fcntl.h>

#define BUFFERSIZE      4096
#define COPYMODE        0644
#define    FILE_MODE        S_IRWXU

void oops(char *, char *);
int isadir(char *);
void copy_file( char *, char * );
void copy_dir(char *, char *);

int main(int ac, char *av[]) {
    struct stat st = {0};
    if (ac != 3) {
        fprintf(stderr, "Usage: %s source_directory destination_directory\n", av[0]);
        exit(1);
    }
    if (strcmp(av[1], av[2]) == 0) {
        fprintf(stderr, "Source and destination directories must be different\n");
        exit(1);
    }
    
    // Check if the destination directory exists
    printf("%d", stat(av[2], &st));
    if (stat(av[2], &st) == -1) {
        // Attempt to create the destination directory
        if (mkdir(av[2], FILE_MODE) == -1) {
            oops("Unable to create destination directory", av[2]);
        }
    }

    copy_dir(av[1], av[2]);
    return 0;
}

void copy_dir(char *dir_src, char *dir_dst) {
    DIR *dir_ptr;
    struct dirent *direntp;
    struct stat statbuf;
    char src_path[BUFFERSIZE];
    char dst_path[BUFFERSIZE];

    // Open source directory
    dir_ptr = opendir(dir_src);
    if (dir_ptr == NULL) {
        oops("Cannot open directory", dir_src);
    }

    // Make the destination directory
    if (mkdir(dir_dst, FILE_MODE) < 0 && errno != EEXIST) {
        oops("Cannot create destination directory", dir_dst);
    }

    // Iterate over each entry in the source directory
    while ((direntp = readdir(dir_ptr)) != NULL) {
        // Skip the '.' and '..' entries
        if (strcmp(direntp->d_name, ".") == 0 ||
            strcmp(direntp->d_name, "..") == 0) {
            continue;
        }

        // Build the paths for source and destination
        snprintf(src_path, sizeof(src_path), "%s/%s", dir_src, direntp->d_name);
        snprintf(dst_path, sizeof(dst_path), "%s/%s", dir_dst, direntp->d_name);

        // Check the type of the entry
        if (stat(src_path, &statbuf) == -1) {
            oops("Error reading source file", src_path);
        }

        if (S_ISDIR(statbuf.st_mode)) {
            // Entry is a directory, recurse into it
            copy_dir(src_path, dst_path);
        } else if (S_ISREG(statbuf.st_mode)) {
            // Entry is a file, copy it
            copy_file(src_path, dst_path);
        } else {
            fprintf(stderr, "Not a regular file or directory: %s\n", src_path);
        }
    }

    // Close the directory
    if (closedir(dir_ptr) < 0) {
        oops("Error closing source directory", dir_src);
    }
}

void copy_file(char *file_src, char *file_dst) {
    int in_fd = open(file_src, O_RDONLY);
    if (in_fd == -1) {
        oops("Cannot open file", file_src);
    }
    int out_fd = open(file_dst, COPYMODE);
    if (out_fd == -1) {
        oops("Cannot create file", file_dst);
    }
    
    // ... code to copy the file contents

    if (close(in_fd) == -1 || close(out_fd) == -1) {
        oops("Error closing files", "");
    }
}

void oops(char *s1, char *s2) {
    fprintf(stderr, "Error: %s ", s1);
    perror(s2);
    exit(1);
}

int isadir(char *str) {
    struct stat info;
    if (stat(str, &info) == -1) {
        return 0;
    }
    return S_ISDIR(info.st_mode);
}