#include <netdb.h>
       #include <stdio.h>
       #include <stdlib.h>
       #include <string.h>
       #include <sys/socket.h>
       #include <sys/types.h>
       #include <unistd.h>

       #define BUF_SIZE 500

       int
       main(int argc, char *argv[])
       {
           int                      sfd, s;
           char                     buf[BUF_SIZE];
           struct addrinfo          hints;
           struct addrinfo          *result, *rp;
           

           if (argc != 3) {
                perror("BAD USAGE");
                return -1;
           }

           memset(&hints, 0, sizeof(hints));
           hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
           hints.ai_socktype = SOCK_STREAM; /* Datagram socket */
           hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */


           s = getaddrinfo(argv[1], argv[2], &hints, &result);
           if (s != 0) {
                perror("GETADDTINFO");
                return -1;
           }

           for (rp = result; rp != NULL; rp = rp->ai_next) {
               sfd = socket(rp->ai_family, rp->ai_socktype,
                            rp->ai_protocol);
               if (sfd == -1)
                   continue;

               if (connect(sfd, rp->ai_addr, rp->ai_addrlen) == 0)
                   break;                  /* Success */
               
               
           }
           //freeaddrinfo(result);           /* No longer needed */
           struct sockaddr_storage  peer_addr;
           socklen_t peer_addrlen;
           int sad;
           ssize_t rec;
           while(1){
                char host[NI_MAXHOST], service[NI_MAXSERV],buf_in[BUF_SIZE];
                peer_addrlen = sizeof(peer_addr);
                ssize_t a=read(0,buf_in,BUF_SIZE);
                if(a>0){
                    buf_in[a]='\0';
                    if (send(sfd, buf_in, a, 0) == -1){
                        perror("SEND");
                        return -1;
                    }

                    if(buf_in[0]=='q' && a==2){
                        printf("CONEXION TERMINADA \n");
                        return 1;

                    }
                    rec=recv(sfd,buf,BUF_SIZE,0);
                    buf[rec]='\0';
                    printf("RESPUESTA SERVIDOR : %s\n",buf);

                }

           }
           freeaddrinfo(result);
           close(sfd);


           return 1;
       }