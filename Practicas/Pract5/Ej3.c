#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <time.h>
#include <string.h>
int main(int argc, char* argv[]){

    if(argc!=4){
        perror("error args");
        return -1;
    }

    struct addrinfo hints;
    struct addrinfo *result,*rp;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
    hints.ai_socktype = SOCK_DGRAM; /* Datagram socket */
    // hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */


    int s = getaddrinfo(argv[1], argv[2], &hints, &result);
    if (s != 0) {
        perror("error getaddrinfo()");
        return -1;
    }

    int sfd;
    for (rp = result; rp != NULL; rp = rp->ai_next) {
        sfd = socket(rp->ai_family, rp->ai_socktype,
                    rp->ai_protocol);
        if (sfd == -1)
            continue;

        if (connect(sfd, rp->ai_addr, rp->ai_addrlen) != -1)
                   break;

        
    } 


               /* No longer needed */

    char buf[100];
    struct sockaddr_storage peer_addr;
    socklen_t peer_addrlen;
    char host[NI_MAXHOST];//*
    char serv[NI_MAXSERV];//*
    char buftime[100];

    int n=0;
    while(n<1){
        peer_addrlen = sizeof(peer_addr);//*
        // char buftime[100];
        // buftime[0]='a';

        

        if(sendto(sfd,argv[3],sizeof(argv[3])+1,0,rp->ai_addr,rp->ai_addrlen)==-1){
                perror("Error al enviar con sendto");
                freeaddrinfo(result);
                return -1;
        }



        ssize_t a = recvfrom(sfd,buf,100, 0,rp->ai_addr, &rp->ai_addrlen);
        if(a>0){
            buf[a]='\0';
            if(buf[0]=='q'){
                printf("Se cerro la conexion\n");
                break;

            }
            else{
                printf("%s\n",buf);
            }

        }
        
        n++;
    }
    freeaddrinfo(result);
    close(sfd);

    return 1;
}