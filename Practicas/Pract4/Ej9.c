#include<stdio.h>
#include<errno.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char* argv[]){

    if(argc!=2){
        perror("Error argumenots");
        return -1;
    }
    int p = mkfifo("as5", 0777);//se puede tambien quitar esto y hacerlo desde terminal directamente
    int a = open("as5",O_WRONLY);
    if(a==-1){
        perror("Error mkfifo()");
        return -1;
    }

    if(write(a,argv[1],sizeof(argv[1]))==-1){
        perror("error write()");
        return -1;
    }

    return 1;
}
