#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/select.h>

int main(){
    if(mkfifo("tub1",0777)==-1){
        perror("MKFIFO1");
        return -1;
    }
    if(mkfifo("tub2",0777)==-1){
        perror("MKFIFO2");
        return -1;
    }
    int tub1=open("tub1",O_RDONLY|O_NONBLOCK);
    if(tub1==-1){
        perror("OPEN1");
        return -1;
    }
    int tub2=open("tub2",O_RDONLY|O_NONBLOCK);
    if(tub2==-1){
        perror("OPEN2");
        return -1;
    }
    fd_set set;
    // FD_ZERO(&set);
    // FD_SET(tub1,&set);
    // FD_SET(tub2,&set);
    int max=0;
    ssize_t nread;
    char buf[512];
    while(1){
        FD_ZERO(&set);
        FD_SET(tub1,&set);
        FD_SET(tub2,&set);
        if(tub1>tub2){
            max=tub1;
        }else{
            max=tub2;
        } 
        if(select(max+1,&set,NULL,NULL,NULL)==-1){
            perror("select");
            return -1;        
        }
        if(FD_ISSET(tub1,&set)){
            nread=read(tub1,buf,512);
            if(nread==0){
                close(tub1);
                //FD_CLR(tub1,&set);
                tub1=open("tub1",O_RDONLY|O_NONBLOCK);
                //FD_SET(tub1,&set);
            }else{
                printf("LEIDO DE TUB1 \n");
                buf[nread]='\0';
                printf("DATOS LEIDOS:%s \n",buf);
            }
            
        }
        if(FD_ISSET(tub2,&set)){
            nread=read(tub2,buf,512);
            if(nread==0){
                close(tub2);
                //FD_CLR(tub2,&set);
                tub2=open("tub2",O_RDONLY|O_NONBLOCK);
                //FD_SET(tub2,&set);
            }else{
                printf("LEIDO DE TUB2\n");
                buf[nread]='\0';
                printf("DATOS LEIDOS:%s \n",buf);
            }
            
        }
       
    }
    
    return 1;
}