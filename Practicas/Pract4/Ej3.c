#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <sys/syscall.h>
#include <sys/wait.h>

int main()  {
    pid_t aux=fork();
    if(aux==-1){
        perror("fork");
        return -1;
    }
    else if(aux==0){
        sigset_t set;
        if(sigemptyset(&set)==-1){
            perror("sigemptyset");
            return -1;
        }
        if(sigaddset(&set,SIGINT)==-1|| sigaddset(&set,SIGTSTP)==-1){
            perror("sigaddset");
            return -1;
        }
        if(sigprocmask(SIG_BLOCK,&set,NULL)==-1){
            perror("sigprockmask");
            return -1;
        }
        sleep(atoi(getenv("SLEEP_SECS")));
        sigset_t pend;
        if(sigpending(&pend)==-1){
            perror("pending");
            return -1;
        }
        if(sigismember(&pend,SIGINT)==-1){
            perror("member SIGINT");
            return -1;
        }else if(sigismember(&pend,SIGINT)==1){
            printf("HE RECIBIDO SIGINT \n");
        }
        if(sigismember(&pend,SIGTSTP)==-1){
            perror("member SIGTSTP");
            return -1;
        }else if (sigismember(&pend,SIGTSTP)==1){
            printf("HE RECIBIDO SIGTSTP \n");
            sigset_t unlock;
            if(sigemptyset(&unlock)==-1){
                perror("sigemptyset");
                return -1;
            }
            if(sigaddset(&unlock,SIGTSTP)==-1){
                perror("sigaddset unlock");
                return -1;
            }
            if(sigprocmask(SIG_UNBLOCK,&unlock,NULL)==-1){
                 perror("sigprockmask");
                 return -1;
            }
        }

        }
         else{
        wait(NULL);
        }
        return 1;
    }
   
    
