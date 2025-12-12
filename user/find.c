#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

void find(char *currentPath, char *targetName) {

    int directoryFileDescriptor;
    struct dirent directoryEntry;
    struct stat entryInfo;


    directoryFileDescriptor = open(currentPath, 0);
    if (directoryFileDescriptor < 0) {
        fprintf(2, "find: cannot open %s\n", currentPath);
        return;
    }

    if (fstat(directoryFileDescriptor, &entryInfo) < 0) {
        fprintf(2, "find: cannot stat %s\n", currentPath);
        close(directoryFileDescriptor);
        return;
    }

    if (entryInfo.type != T_DIR) {
        close(directoryFileDescriptor);
        return;
    }

    char fullPathBuffer[512];
    char *bufferPointer;

    strcpy(fullPathBuffer, currentPath);

    bufferPointer = fullPathBuffer + strlen(fullPathBuffer);

    *bufferPointer++ = '/';

    while (read(directoryFileDescriptor, &directoryEntry, sizeof(directoryEntry)) == sizeof(directoryEntry)) {

        if (directoryEntry.inum == 0)
            continue;

        if (strcmp(directoryEntry.name, ".") == 0 || strcmp(directoryEntry.name, "..") == 0)
            continue;

        memmove(bufferPointer, directoryEntry.name, DIRSIZ);
        bufferPointer[DIRSIZ] = 0;

        if (stat(fullPathBuffer, &entryInfo) < 0) {
            printf("find: cannot stat %s\n", fullPathBuffer);
            continue;
        }

        if (entryInfo.type == T_DIR) {
            find(fullPathBuffer, targetName);
        }

        else {
            if (strcmp(directoryEntry.name, targetName) == 0) {
                printf("%s\n", fullPathBuffer);
            }
        }
    }

    close(directoryFileDescriptor);
}




int main(int argumentCount, char *arguments[]) {

    if (argumentCount != 3) {
        fprintf(2, "Usage: find <directory> <filename>\n");
        exit(1);
    }

    find(arguments[1], arguments[2]);
    exit(0);
}
