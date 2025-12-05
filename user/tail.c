#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "user/user.h"

#define BUF_SIZE 2048  // enough for small xv6 files

int
main(int argc, char *argv[])
{
    int fd = 0;        // default: stdin
    int n = 10;        // default number of lines
    char buf[BUF_SIZE];
    int size = 0;

    // --- Parse arguments ---
    if(argc == 2){
        // case: tail file.txt
        fd = open(argv[1], O_RDONLY);
        if(fd < 0){
            printf("tail: cannot open %s\n", argv[1]);
            exit(1);
        }
    }
    else if(argc == 4 && strcmp(argv[1], "-n") == 0){
        // case: tail -n 5 file.txt
        n = atoi(argv[2]);
        if(n < 0) n = 10;

        fd = open(argv[3], O_RDONLY);
        if(fd < 0){
            printf("tail: cannot open %s\n", argv[3]);
            exit(1);
        }
    }
    else if(argc != 1){
        printf("Usage: tail [-n number] [file]\n");
        exit(1);
    }

    // --- Read file into buffer ---
    int r;
    while((r = read(fd, buf + size, BUF_SIZE - size)) > 0){
        size += r;
    }

    if(fd != 0)
        close(fd);

    // --- Find starting position for last n lines ---
    int lines = 0;
    for(int i = size - 1; i >= 0; i--){
        if(buf[i] == '\n'){
            lines++;
            if(lines == n + 1){
                // start after this newline
                i++;
                write(1, buf + i, size - i);
                exit(0);
            }
        }
    }

    // If file has fewer than n lines, print entire content
    write(1, buf, size);
    exit(0);
}
