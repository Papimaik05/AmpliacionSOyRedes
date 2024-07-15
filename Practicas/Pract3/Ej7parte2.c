    #include <unistd.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <sys/wait.h>
    int main(int argc,char *argv[]){
    // if(argc!=2){
    //     perror("BAD USAGE");
    //     return 0;
    // }
    if(execvp(argv[1],&argv[1])==-1){ 
        perror("error system");
        return 0;
    }
    else{
        printf("El comando terminó de ejecutarse");
    }
    return 1;
    }