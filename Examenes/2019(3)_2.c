#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

volatile int contint=0; 
volatile int contstp=0; 
void contar(int signal){
    if(signal==SIGINT){
        contint++;
    }else if(signal==SIGTSTP){
        contstp++;
    }
}
int main(){
    sigset_t set;
    sigfillset(&set);
    sigdelset(&set,SIGINT);
    sigdelset(&set,SIGTSTP);
    sigprocmask(SIG_BLOCK,&set,NULL);
    struct sigaction act;
    act.sa_flags=0;
    act.sa_handler=contar;
    sigaction(SIGINT,&act,NULL);
    sigaction(SIGTSTP,&act,NULL);
    while((contint+contstp)<10){
        pause();
    }
    printf("SIGINT: %d\n",contint);
    printf("SIGTSTP: %d\n",contstp);
    return 1;
}