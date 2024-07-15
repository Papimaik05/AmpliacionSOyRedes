#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
int main(int argc,char * argv[]){
    if(argc!=3){
        perror("BAD USAGE");
        return -1;
    }   
    int pipefd[2];
    if(pipe(pipefd)==-1){
        perror("PIPE");
        return -1;
    }
    pid_t pid;
    pid=fork();
    if(pid==-1){
        perror("fork");
        return -1;
    }else if(pid==0){
        printf("PID HIJO:%d\n",getpid());
        close(pipefd[0]);
        dup2(pipefd[1],1);
        close(pipefd[1]);
        _exit(execlp(argv[1],argv[1],NULL));

    }else{
        printf("PID PADRE:%d\n",getpid());
        close(pipefd[1]);
        dup2(pipefd[0],0);
        close(pipefd[0]);
        _exit(execlp(argv[2],argv[2],NULL));

        int status;
        waitpid(-1,&status,0);

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
     return 1;
}