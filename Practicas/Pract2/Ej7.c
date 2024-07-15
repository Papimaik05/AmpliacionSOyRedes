#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
int main(int argc ,char* argv[]){
    if(argc < 2){
        return 0;
    }
    umask(027);
    int fd=open(argv[1],O_CREAT,0645);
    if(fd==-1){
        perror("error open");
    }
    close(fd);
    return 1;
}
