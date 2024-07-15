#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
 #include <sys/wait.h>
int main(int argc,char* argv[]){
    if(argc < 2){
        perror("BAD USAGE");
        return 0;
    }
    pid_t aux=fork();
    if(aux==-1){
        perror("fork");
        return 0;
    }
    else if(aux==0){
        //Hijo 
        setsid();
        int fd1=open("/tmp/daemon.out",O_CREAT|O_TRUNC|O_RDWR,0777);
        int fd2=open("/tmp/daemon.err",O_CREAT|O_TRUNC|O_RDWR,0777);
        int fd3=open("/dev/null",O_CREAT|O_TRUNC|O_RDWR,0777);
        
        if(dup2(fd1,1)==-1){
            perror("fd1 error");
            return 0;
        }
        if(dup2(fd2,2)==-1){
            perror("fd2 error");
            return 0;
        }
        if(dup2(fd3,0)==-1){
            perror("fd3 error");
            return 0;
        }
        if(execvp(argv[1],&argv[1])==-1){
            perror("execvp");
            return 0;
        }

        //DEBERIAS DE CERRARLO PERO NUNCA LLEGARAS
    }
    else{
        wait(NULL);
    }
    return 1;
}
