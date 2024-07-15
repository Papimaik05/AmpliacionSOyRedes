#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>  
#include <signal.h>
#include <sys/wait.h>
int pipefd[2];
void ejer1(){
   close(pipefd[0]);
   char out[2];
   sprintf(out,"%s","a\0");
   if(write(pipefd[1],out,2)==-1){
        perror("write");    
   }
   close(pipefd[1]);
}

int main(){
    if(pipe(pipefd)==-1){
        perror("pipe");
        return -1;          
    }
    pid_t pid=fork();
    char buf[500];
    if(pid==-1){
        perror("fork");
        return -1;  
    }else if(pid==0){
        close(pipefd[1]);
        if(read(pipefd[0],buf,500)==-1){
            perror("read");
            return -1;  
        }
        close(pipefd[0]);
        _exit(printf("[%d] LEIDO:%s\n",getpid(),buf));

    }else{
        printf("[%d] ",getpid());
        struct sigaction act;
        act.sa_flags=0;
        act.sa_handler=ejer1;
        sigaction(SIGUSR1,&act,NULL);
        sigset_t set;
        sigfillset(&set);
        sigdelset(&set,SIGUSR1);
        sigsuspend(&set);
        
        int status;
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

    return 1;
}