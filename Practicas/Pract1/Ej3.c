   #include <string.h>
   #include <errno.h>
   #include <stdio.h>
   #include <unistd.h>
   int main(){
    int i=0;
    while(i<255){
        printf("Codigo de error: %d \n %s \n",i,strerror(i));
        i++;
    }
    
    return 1;
   }