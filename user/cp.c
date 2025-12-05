#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"

int
main(int argc, char *argv[])
{

// Must have exactly 2 arguments
if(argc != 3) {
    printf("cp: requires source and destination\n");
    exit(0);
}

//  for Opening the source file
int src = open(argv[1], O_RDONLY);//file 1 in argv[1] ,O_RDONLY just for reading
if(src < 0) { // it returns -ve when file dosent exist , no read permisssion , path invaild ..
    printf("cp: cannot open source file %s\n", argv[1]);
    exit(0);
}


// for opening the destination file
int dest = open(argv[2], O_WRONLY | O_CREATE); //file 2 in argv[1] ,O_RDONLY just for reading
if(dest < 0) { // it returns -ve when file cannot be opend , cannt be created dosent have permissions
    printf("cp: cannot open or create destination file %s\n", argv[2]);
    close(src);
    exit(0);
}

char buf[512];
int n;

while ((n = read(src, buf, sizeof(buf))) > 0) {
    write(dest, buf, n);
}
close(src);
close(dest);








  exit(0);
}
