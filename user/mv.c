#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"

int
main(int argc, char *argv[])
{
    // Check for correct number of arguments
    if(argc != 3){
        printf("mv: requires source and destination\n");
        exit(0);
    }

    // Try to create a new link (destination)
    if(link(argv[1], argv[2]) < 0){
        printf("mv: failed to link %s to %s\n", argv[1], argv[2]);
        exit(0);
    }

    // Remove the old name (source)
    if(unlink(argv[1]) < 0){
        printf("mv: failed to unlink %s\n", argv[1]);
        exit(0);
    }

    exit(0);
}
