    #include <unistd.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <sys/wait.h>
    int main(){
        pid_t aux=fork();
        if(aux==-1){
            perror("fork");
            return 0;
        }
        else if(aux==0){
             
            chdir("/tmp");
            setsid();
            printf("PID : %d \n",getpid());
            printf("PPID : %d \n",getppid());
            printf("GID : %d \n",getpgid(getpid()));
            printf("SID : %d \n",getsid(getpid()));
            char buf[100];
            printf("RUTA ACTUAL : %s \n",getcwd(buf,100));
            printf("MAX FICHEROS : %ld \n",sysconf(_SC_OPEN_MAX));
        }
        else {
            sleep(10);
            wait(NULL);
        }


        return 1;
    }