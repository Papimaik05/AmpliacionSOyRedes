#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

int main(int argc, char *argv[]){

    if (argc != 2){
        perror("BAD USAGE");
        return -1;
    }
    struct addrinfo hints;
    struct addrinfo *res;
    memset(&hints,0,sizeof(hints));
    if(getaddrinfo(argv[1],NULL,&hints,&res)){
        perror("GETADDRINFO");
        return -1;
    }


    for(struct addrinfo *rp= res;rp!=NULL;rp=rp->ai_next){
        char host[NI_MAXHOST];
        if(getnameinfo(rp->ai_addr,rp->ai_addrlen,host,sizeof(host),NULL,0,NI_NUMERICHOST)!=0){
            perror("GETNAMEINFO");
            return -1;
        }
        printf("Familia de protocolos : %d \n",rp->ai_protocol);
        printf("Tipo de socket: %d \n",rp->ai_socktype);
        printf("host=%s\n", host);
    }
    
    
    return 1;
}