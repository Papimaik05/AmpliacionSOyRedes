 #include <sys/time.h>
 #include <stdio.h>
#include <unistd.h>
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
    printf("%ld \n",despues.tv_usec-antes.tv_usec);
    return 1;
}