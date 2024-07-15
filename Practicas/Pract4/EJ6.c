#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
int main(int argc,char* argv[]){
    if(argc!=5){
        perror("BAD USAGE");
        return -1;
    }
    int pipefd[2];
    if(pipe(pipefd)==-1){
        perror("pipe");
        return -1;
    }
    pid_t aux=fork();
    if(aux==-1){
        perror("fork");
        return -1;
    }else if(aux==0){
        close(pipefd[1]);
        if(dup2(pipefd[0],0)==-1){
             perror("dup hijo");
            return -1;
        }
        close(pipefd[0]);
        execlp(argv[3],argv[3],argv[4],NULL);
    }else{
        close(pipefd[0]);
        if(dup2(pipefd[1],1)==-1){
             perror("dup padre");
            return -1;
        }
        close(pipefd[1]);
        execlp(argv[1],argv[1],argv[2],NULL);
        wait(NULL);
    }
    return 1;
}