#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h> 
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
    if(argc < 4){
        perror("BAD USAGE");
        return -1;
    }
    int fd=open(argv[2],O_WRONLY|O_CREAT|O_TRUNC,0777);
    if(fd==-1){
        perror("open");
        return -1;       
    }
    pid_t pid=fork();
    if(pid==-1){
        perror("forrk");
        return -1;
    }else if(pid==0){
        setpriority(PRIO_PROCESS,getpid(),atoi(argv[1]));
        printf("%d \n",getpriority(PRIO_PROCESS,getpid()));
        dup2(fd,1);
        _exit(execvp(argv[3],&argv[3]));


    }else{
        int status;
        printf("EL PROCESO %d ",pid);
        waitpid(-1, &status,0);
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
    close(fd);
    return 1;
}