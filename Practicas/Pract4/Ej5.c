#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
char *exec_name;
void handler(){
    printf("SALVADO \n");
}
void handler_alarm(){
    printf("BORRADO \n");
    unlink(exec_name);
}

int main(int argc, char *argv[]){
    if(argc!=2){
        perror("BAD USAGE");
        return -1;
    }
    exec_name=argv[0];
    int segundos=atoi(argv[1]);
    struct sigaction act;
    act.sa_flags=0;
    act.sa_handler=handler;
    if(sigaction(SIGUSR1,&act,NULL)==-1){
        perror("sigaction");
        return -1;
    }
    struct sigaction act2;
    act2.sa_flags=0;
    act2.sa_handler=handler_alarm;
    if(sigaction(SIGALRM,&act2,NULL)==-1){
        perror("sigaction");
        return -1;
    }
    
    printf("SE BORRARA EN %d SEGUNDOS, SALVALO CON SIGUSR1 \n",segundos);
    alarm(segundos);
    
    sigset_t mask;
    sigfillset(&mask);
    sigdelset(&mask,SIGALRM);
    sigdelset(&mask,SIGUSR1);
    sigsuspend(&mask);
    return 1;
}