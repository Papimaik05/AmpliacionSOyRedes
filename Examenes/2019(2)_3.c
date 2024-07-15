#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc,char *argv[]){
    if(argc<1){
        perror("BAD USAGE");
        return -1;
    }
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return -1;
    }
    pid_t pid=fork();
    if(pid==-1){
        perror("BAD USAGE");
        return -1;
    }else if(pid==0){
        printf("ID PROCESO:%d \n",getpid());
        close(pipefd[0]); //  Cerramos el extremo de escritura
        dup2(pipefd[1], 1); // metes en la tuberia lo que te salga por el comando de despues
        close(pipefd[1]);
        // if(execvp(argv[2],&argv[2])==-1){
        //     perror("execvp");
        //     return -1;
        // }
        if(execlp(argv[1],argv[1],NULL)==-1){
            perror("execlp");
            return -1;
        }
    }else{
        printf("ID PROCESO:%d \n",getpid());
        close(pipefd[1]); // Cerramos el extremo de lectura
        dup2(pipefd[0], 0); // leer,
        close(pipefd[0]);
        // if(execlp(argv[1],argv[1],NULL)==-1){
        //     perror("execlp");
        //     return -1;
        // }
        if(execvp(argv[2],&argv[2])==-1){
            perror("execvp");
            return -1;
        }
        //wait(NULL);
    }

    return 1;
}

// ./1 ls wc -c