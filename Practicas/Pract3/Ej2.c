#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sched.h>

int main(){
    int a;
    struct sched_param param;
    int c= sched_getparam(getpid(),&param);
    if((a=sched_getscheduler(getpid()))==-1){
        perror("SCHEDULE");
        return 0;
    }          
    if(a>=0){
       switch(a){
       case SCHED_FIFO:   
       printf("FIFO\n");
       break;
       case SCHED_RR:   
       printf("ROUNDROBIN\n");
       break;
       case SCHED_OTHER:   
       printf("por defecto\n");
       break;
       default:
       printf("unknown\n");
       }
    }
    printf("Prioridad: %d\n",param.sched_priority);
    printf(" PRioridad Maxima : %d \n",sched_get_priority_max(a));
    printf(" PRioridad Minima : %d \n",sched_get_priority_min(a));
    return 1;
}