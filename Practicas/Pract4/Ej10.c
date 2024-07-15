#include<unistd.h>
#include<fcntl.h>
#include<errno.h>
#include<stdio.h>
 #include<sys/select.h>
 #include <sys/types.h>
#include <sys/stat.h>

int main(){
    int max =0;
    int tub1 = mkfifo("tub1",0777);
    int tub2 = mkfifo("tub2",0777);

    if(tub1==-1){
        perror("error tub1");
        return -1;
    }
    if(tub2==-1){
        perror("error tub2");
        return -1;
    }

    int fd1 = open("tub1",O_NONBLOCK | O_RDONLY);
    int fd2 = open("tub2",O_NONBLOCK | O_RDONLY);

    if(fd1==-1){
        perror("error fd1");
        return -1;
    }
    if(fd2==-1){
        perror("error fd2");
        return -1;
    }

    while(1){
        char buf[256];
        fd_set set;
        FD_ZERO(&set);
        FD_SET(fd1,&set);
        FD_SET(fd2,&set);

        if(fd1 > fd2){
            max = fd1;
        }
        else{
            max = fd2;
        }


        if(select(max+1, &set,NULL,NULL,NULL)==-1){
            perror("error select");
            return -1;
        }

        if(FD_ISSET(fd1,&set)){

            ssize_t a = read(fd1,buf, sizeof(buf));
            if(a==0){
                close(fd1);
                int fd1 = open("tub1",O_NONBLOCK | O_RDONLY);
                continue;
            }

            buf[a]='\0';
            printf("BUFFer de tub1: %s\n",buf);

        }

        if(FD_ISSET(fd2,&set)){

            ssize_t a = read(fd2,buf, sizeof(buf));
            if(a==0){
                close(fd2);
                int fd2 = open("tub2",O_NONBLOCK | O_RDONLY);
                continue;
            }

            buf[a]='\0';
            printf("BUffer de tub2: %s\n",buf);

        }
    }
    return 1;
}