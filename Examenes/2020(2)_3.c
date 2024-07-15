#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
int main(int argc,char*argv[]){
    if(argc<4){
        perror("BAD USAGE");
        return -1;
    }
    int pipefd[2];
    if(pipe(pipefd)==-1){
        perror("PIPE");
        return -1; 
    }
    pid_t pid=fork();
    if(pid==-1){
        perror("FORK");
        return -1;
    }else if(pid==0){
        printf("PID :%d\n",getpid());
        close(pipefd[0]);
        dup2(pipefd[1],1);
        close(pipefd[1]);
        _exit(execlp(argv[1],argv[1],NULL));

    }else{
        printf("PID :%d\n",getpid());
        close(pipefd[1]);
        dup2(pipefd[0],0);
        close(pipefd[0]);
        int status;
        waitpid(-1, &status, 0);
        if (WIFEXITED(status)) {
                printf("Child process exited with status %d\n", WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
                printf("Child process was terminated by signal %d\n", WTERMSIG(status));
        } else if (WIFSTOPPED(status)) {
                printf("Child process was stopped by signal %d\n", WSTOPSIG(status));
        } else {
                printf("Child process terminated in an unknown way\n");
        }
        execvp(argv[2],&argv[2]);
    }

    int status;
    while (wait(&status) > 0) {
        if (WIFEXITED(status)) {
            printf("Child exited with status %d\n", WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("Child terminated by signal %d\n", WTERMSIG(status));
        }
    }
    return 1;
}