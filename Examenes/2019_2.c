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
    pid_t pid=fork();
    if(pid==-1){
        perror("BAD USAGE");
        return -1;
    }else if(pid==0){
        setsid();
        chdir("/tmp");
        printf("ID PROCESO:%d \n",getpid());
        printf("ID PROCESO PADRE:%d \n",getppid());
        printf("ID GRUPO DE PROCESOS:%d \n",getpgid(getpid()));
        printf("ID SESION:%d \n",getsid(getpid()));
        if(execvp(argv[1],&argv[1])==-1){
            perror("execvp");
            return -1;
        }
    }else{
        wait(NULL);
    }
    return 1;
}