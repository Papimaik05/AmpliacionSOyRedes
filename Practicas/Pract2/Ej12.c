 #include <fcntl.h>               
 #include <unistd.h>
 #include <stdlib.h>
#include <stdio.h>

 int main(int argc,char* argv[]){
    if(argc != 2){
        printf("ERROR DE ARGUMENTOS");
        return 0;
    }
    int fd=open(argv[1],O_WRONLY);
    if(fd==-1){
        perror("error open");
        return 0;
    }
    if(dup2(fd,1)==-1){
        perror("error dup");
        return 0;
    }
    printf("a");
    printf("b");
    printf("c");
    close(fd);
    return 1;
 }