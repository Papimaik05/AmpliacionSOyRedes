#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
int main(int argc,char* argv[]){
    // if(argc<=5){
    //     perror("BAD USAGE");
    //     return -1;
    // }
    int p_h[2];
    int h_p[2];
    if(pipe(p_h)==-1){
        perror("pipe");
        return -1;
    }
    if(pipe(h_p)==-1){
        perror("pipe");
        return -1;
    }
    pid_t aux=fork();
    if(aux==-1){
        perror("fork");
        return -1;
    }else if(aux==0){
        close(p_h[1]);
        close(h_p[0]);

        int n=0;
        char buf[100];
        char buf_salida[2];
        buf_salida[0]='l';
        buf_salida[1]='\0';

        while(n<10){
            ssize_t bytes_leidos=read(p_h[0],&buf,100);
            if(bytes_leidos < 0){
                 perror("read hijo");
                return -1;
            }
            buf[bytes_leidos]='\0';
            printf("BUF LECTURA HIJO : %s \n",buf);
            if(write(1,&buf,bytes_leidos+1)<0){
                 perror("write hijo");
                return -1;
            }
            sleep(1);
            if(write(h_p[1],&buf_salida,2)<0){
             perror("write hijo");
            return -1;
            }
            n++;
            printf("CONTADOR ELES : %d \n",n);
        }
        buf_salida[0]='q';
        if(write(h_p[1],&buf_salida,2)<0){
             perror("write hijo");
            return -1;
        }
        close(p_h[0]);
        close(h_p[1]);
    }else{
        close(p_h[0]);
        close(h_p[1]);
        char buf[100];
        char buf_fin[100];
        do{
            ssize_t bytes_leidos=read(0,&buf,100);
            if(bytes_leidos < 0){
                perror("read padre");
                return -1;
            }
            buf[bytes_leidos]='\0';
            
            if(write(p_h[1],&buf,bytes_leidos+1)<0){
                perror("write padre");
                return -1;
            }
            read(h_p[0],&buf_fin,100);
            printf("BUF LECTURA PADRE : %s \n",buf_fin);

        }while(buf_fin[0]!='q');
        printf("BUF LECTURA PADRE FINAL : %s \n",buf_fin);
        close(p_h[1]);
        close(h_p[0]);
    }
    return 1;
}