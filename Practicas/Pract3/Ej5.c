    #include <unistd.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>

    int main(){
        printf("PID : %d \n",getpid());
        printf("PPID : %d \n",getppid());
        printf("GID : %d \n",getpgid(getpid()));
        printf("SID : %d \n",getsid(getpid()));
        char buf[100];
        printf("RUTA ACTUAL : %s \n",getcwd(buf,100));
        printf("MAX FICHEROS : %ld \n",sysconf(_SC_OPEN_MAX));
        return 1;
    }