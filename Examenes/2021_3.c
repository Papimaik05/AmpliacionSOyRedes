#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> 
#include <sys/select.h>
int main(){

    if(mkfifo("tub1",0777)==-1){
        perror("MKFIFO");
        return -1;
    }
    int tub1=open("tub1",O_RDONLY|O_NONBLOCK);
    if(tub1==-1){
        perror("open");
        return -1;        
    }
    fd_set set;
    char buf[512];
    ssize_t nread;
    struct timeval tv;
    while(1){
        tv.tv_sec = 5;
        tv.tv_usec = 0;
        FD_ZERO(&set);
        FD_SET(0,&set);
        FD_SET(tub1,&set);
        int s=select(tub1+1,&set,NULL,NULL,&tv);
        if(s==-1){
            perror("SELECT\n");
            return -1;
        }else if(s==0){
            printf("NO SE RECIBIO NADA \n");
            break;
        }
        if(FD_ISSET(tub1,&set)){
            nread=read(tub1,buf,512);
            buf[nread]='\0';
            if(nread==0){
                close(tub1);
                tub1=open("tub1",O_RDONLY|O_NONBLOCK);
            }else if(nread>0){
                printf("LEIDO DE TUBERIA:%s\n",buf);
            }
        }
        if(FD_ISSET(0,&set)){
            nread=read(0,buf,512);
            buf[nread]='\0';
            if(nread>0){
                printf("LEIDO DE TERMINAL:%s\n",buf);
            }
        }


    }

    return 1;
}