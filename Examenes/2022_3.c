#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char * argv[]){
    if(argc!=5){
        perror("BAD USAGE");
        return -1;
    }
    int status;
    int pipefd[2];
    pipe(pipefd);
    pid_t pid;
    pid_t hijo1;
    pid_t hijo2;  
    pid=fork();
    if(pid==-1){
        perror("FORK");
        return -1;
    }else if(pid==0){
        printf("PID HIJO 1:%d \n",getpid());
        close(pipefd[0]);
        dup2(pipefd[1],1);
        close(pipefd[1]);
        _exit(execlp(argv[1],argv[1],argv[2],NULL));

    }else{
        pid_t pid2;
        pid2=fork();
        if(pid2==-1){
            perror("FORK2");
            return -1;
        }else if(pid2==0){
                printf("PID HIJO 2:%d \n",getpid());
                close(pipefd[1]);
                dup2(pipefd[0],0);
                close(pipefd[0]);
                _exit(execlp(argv[3],argv[3],argv[4],NULL));               
        }
        printf("HIJO 2:%d\n",hijo2);
        printf("HIJO 1:%d\n",hijo1);
        printf("Padre:%d\n",getpid());
        pid_t w = waitpid(-1, &status,0);
        if (w == -1) {
            perror("waitpid");
            exit(EXIT_FAILURE);
        }

        if (WIFEXITED(status)) {
            printf("exited, status=%d\n", WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("killed by signal %d\n", WTERMSIG(status));
        } else if (WIFSTOPPED(status)) {
            printf("stopped by signal %d\n", WSTOPSIG(status));
        } else if (WIFCONTINUED(status)) {
            printf("continued\n");
        }
    }
    
}