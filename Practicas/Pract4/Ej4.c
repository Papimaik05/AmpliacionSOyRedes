#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <sys/syscall.h>
#include <sys/wait.h>

int numInt=0;
int numStp=0;

void contar(int num){
    if(num==SIGINT){
        numInt++;
    }
    else if(num==SIGTSTP){
        numStp++;
    }
}

int main(){
    
    struct sigaction act;
    act.sa_handler=contar;
    act.sa_flags=0;

    if(sigaction(SIGINT,&act,NULL)==-1){
        perror("ERROR SIGINT");
        return -1;
    }
    if(sigaction(SIGTSTP,&act,NULL)==-1){
        perror("ERROR SIGINT");
        return -1;
    }

    while((numInt+numStp)<10){
        pause();
    }

    printf("SIGINT : %d \n",numInt);
    printf("SIGTSTP : %d \n",numStp);

    return 1;
}