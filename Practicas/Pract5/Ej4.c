#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <time.h>
#include <string.h>
#include <sys/select.h>

int main(int argc, char* argv[]){

    if(argc!=3){
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

        if (bind(sfd, rp->ai_addr, rp->ai_addrlen) == 0)
            break;                  /* Success */

        // close(sfd);
    } 

    
     

    freeaddrinfo(result);           /* No longer needed */

    char buf[100];
    struct sockaddr_storage peer_addr;
    socklen_t peer_addrlen;
    char host[NI_MAXHOST];//*
    char serv[NI_MAXSERV];//*
    char buftime[100];
    char bufterm[100];
    fd_set set;
    
    
    while(1){
        peer_addrlen = sizeof(peer_addr);//*
        // char buftime[100];
        // buftime[0]='a';
        FD_ZERO(&set);  
        FD_SET(sfd,&set);
        FD_SET(0,&set);
        if(select(sfd+1,&set,NULL,NULL,NULL)==-1){
                perror("SELECT");
                return -1;
        }
        if(FD_ISSET(0,&set)){
            ssize_t r=read(0,bufterm, 100);
            
            if(r>0){
                printf("Received %zd bytes from terminal\n",r);
                bufterm[r]='\0';
                time_t t = time(NULL);
                struct tm *aux= localtime(&t);
                ssize_t b=0;
                if(bufterm[0]=='t'){
                    b = strftime(bufterm,100,"%H",aux);
                    printf("Hora: %s\n",bufterm);
                }
                else if(bufterm[0]=='d'){
                    b=strftime(bufterm,100,"%F",aux);
                    printf("Fecha: %s\n",bufterm);
                    
                }
                else if(bufterm[0]=='q'){
                    printf("VOy a cerrar\n");
                    break;
                }
                else{
                    printf("No se que quieres que haga\n");
                }
            }
        }
        else if(FD_ISSET(sfd,&set)){
            ssize_t a = recvfrom(sfd,buf,100, 0,(struct sockaddr *)&peer_addr, &peer_addrlen);
            if(a>0){
                buf[a]='\0';
                int s = getnameinfo((struct sockaddr *) &peer_addr,peer_addrlen, host, NI_MAXHOST,serv, NI_MAXSERV, NI_NUMERICHOST|NI_NUMERICSERV);
                if (s == 0){
                    printf("Received %zd bytes from %s:%s\n",a, host, serv);
                }
                time_t t = time(NULL);
                struct tm *aux= localtime(&t);
                ssize_t b=0;
                if(buf[0]=='t'){
                    b = strftime(buftime,100,"%H",aux);
                    printf("Hora: %s\n",buftime);
                }
                else if(buf[0]=='d'){
                    b=strftime(buftime,100,"%F",aux);
                    printf("Fecha: %s\n",buftime);
                    
                }
                else if(buf[0]=='q'){
                    printf("VOy a cerrar\n");
                    break;
                }
                else{
                    printf("No se que quieres que haga\n");
                }

                if(sendto(sfd, buftime,b,0,(struct sockaddr *) &peer_addr,peer_addrlen)==-1){
                    perror("Error al enviar con sendto");
                    return -1;
                }
            }
        
        }

    }

    close(sfd);



    return 1;
}