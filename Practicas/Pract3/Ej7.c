    #include <unistd.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <sys/wait.h>
    int main(int argc,char *argv[]){

        if(argc!=2){
            perror("BAD USAGE");
            return 0;
        }
        int a=system(argv[1]);
        if(a==-1){
            perror("ERROR SYSTEM");
            return 0;
        }
        else if (a==127){
            perror("shell could not be executed in the child process");
            return 0;
        }

        printf("SE ha ejecutado de locos");
            return 1;
        }

        // pid_t aux=fork();
        // if(aux==-1){
        //     perror("fork");
        //     return 0;
        // }
        // else if(aux==0){
             
        //     chdir("/tmp");
        //     setsid();
        //     printf("PID : %d \n",getpid());
        //     printf("PPID : %d \n",getppid());
        //     printf("GID : %d \n",getpgid(getpid()));
        //     printf("SID : %d \n",getsid(getpid()));
        //     char buf[100];
        //     printf("RUTA ACTUAL : %s \n",getcwd(buf,100));
        //     printf("MAX FICHEROS : %ld \n",sysconf(_SC_OPEN_MAX));
        // }
        // else {
        //     sleep(10);
        //     wait(NULL);
        // }


   