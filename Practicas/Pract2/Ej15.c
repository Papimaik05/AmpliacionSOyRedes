#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <sys/types.h>
int main(int argc,char* argv[]){
    if(argc!=2){
        perror("BAD USAGE");
        return 0;
    }
    int fd=open(argv[1],O_RDWR);
    if(fd==-1){
        perror("BAD UOPEN");
        return 0;
    }
    if(lockf(fd,F_LOCK,0)){
        perror("BAD FLOCK");
        return 0;
    }
    time_t a;
    a=time(NULL);
    printf("HORA %s \n",ctime(&a));
    sleep(3);
    if(lockf(fd,F_ULOCK,0)){
        perror("BAD FLOCK");
        return 0;
    }
    sleep(10);
    time_t b;
    b=time(NULL);
    printf("HORA %s \n",ctime(&b));
    
    return 1;
}