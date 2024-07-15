 #include <time.h>
 #include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <string.h>
int main(){
    struct timeval antes;
    struct timeval despues;
    if(gettimeofday(&antes,NULL)==-1){
        perror("error gettime");
    }
    int i=0;
    while(i<1000){
        i++;
    }
     if(gettimeofday(&despues,NULL)==-1){
        perror("error gettime");
    }
    printf("%ld \n",antes.tv_usec-despues.tv_usec);
    return 1;
}