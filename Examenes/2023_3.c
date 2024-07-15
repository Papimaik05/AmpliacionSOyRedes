#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/select.h>
#include <fcntl.h>    
#include <sys/types.h>
#include <sys/stat.h>
int main(){
    if(mkfifo("fifo1",0777)==-1){
        perror("FIFO1");
        return -1;
    }
    if(mkfifo("fifo2",0777)==-1){
        perror("FIFO1");
        return -1;        
    }
    int tub1=open("fifo1",O_RDONLY|O_NONBLOCK);
    if(tub1==-1){
        perror("open1");
        return -1;           
    }

    int tub2=open("fifo2",O_RDONLY|O_NONBLOCK);
    if(tub2==-1){
        perror("open2");
        return -1;           
    }
    fd_set set;
    int max=0;
    char buf[500];
    ssize_t nread;
    while(1){
        FD_ZERO(&set);
        FD_SET(tub1,&set);
        FD_SET(tub2,&set);
        if(tub1>tub2){
            max=tub1;
        }else{
            max=tub2;
        }
        select(max+1,&set,NULL,NULL,NULL);
        if(FD_ISSET(tub1,&set)){
            nread=read(tub1,buf,500);
            if(nread==0){
                close(tub1);
                tub1=open("fifo1",O_RDONLY|O_NONBLOCK);

            }else if(nread>0){
                buf[nread-1]='\0';
                printf("%s","LEIDO DESDE TUB 1 \n");
                printf("DATOS:%s\n",buf);
            }
        }
        if(FD_ISSET(tub2,&set)){
            nread=read(tub2,buf,500);
            if(nread==0){
                close(tub2);
                tub2=open("fifo2",O_RDONLY|O_NONBLOCK);

            }else if(nread>0){
                buf[nread-1]='\0';
                printf("%s","LEIDO DESDE TUB 2 \n");
                printf("DATOS:%s\n",buf);
            }
        }

    }
    return 1;
}