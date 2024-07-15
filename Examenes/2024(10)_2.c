#include <sys/types.h>
       #include <stdio.h>
       #include <stdlib.h>
       #include <unistd.h>
       #include <fcntl.h> 
       #include <string.h>
       #include <sys/socket.h>
       #include <netdb.h>

       #define BUF_SIZE 500

       int
       main(int argc, char *argv[])
       {
           struct addrinfo hints;
           struct addrinfo *result, *rp;
           int sfd, s;
           struct sockaddr_storage peer_addr;
           socklen_t peer_addr_len;
           ssize_t nread;
           char buf[BUF_SIZE],out[BUF_SIZE];

           if (argc != 3) {
                perror("BAD USAGE");
                return -1;
           }

           memset(&hints, 0, sizeof(hints));
           hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
           hints.ai_socktype = SOCK_DGRAM; /* Datagram socket */
           hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
           hints.ai_protocol = 0;          /* Any protocol */

           s = getaddrinfo(argv[1], argv[2], &hints, &result);
            if (s != 0) {
                perror("getaddrinfo");
                return -1;
           }

           /* getaddrinfo() returns a list of address structures.
              Try each address until we successfully bind(2).
              If socket(2) (or bind(2)) fails, we (close the socket
              and) try the next address. */

           for (rp = result; rp != NULL; rp = rp->ai_next) {
               sfd = socket(rp->ai_family, rp->ai_socktype,
                       rp->ai_protocol);
               if (sfd == -1)
                   continue;

               if (bind(sfd, rp->ai_addr, rp->ai_addrlen) == 0)
                   break;                  /* Success */


           }

           freeaddrinfo(result);           /* No longer needed */

           if (rp == NULL) {               /* No address succeeded */
                perror("BAD USAGE");
                return -1;
           }
           /* Read datagrams and echo them back to sender */
           while (1) {
               peer_addr_len = sizeof(peer_addr);
               nread = recvfrom(sfd, buf, BUF_SIZE, 0,(struct sockaddr *) &peer_addr, &peer_addr_len);
               if (nread == -1){
                perror("getaddrinfo");
                return -1;            
               }else if(nread>0){
                    buf[nread-1]='\0';
                    char host[NI_MAXHOST], service[NI_MAXSERV];
                    s = getnameinfo((struct sockaddr *) &peer_addr,peer_addr_len, host, NI_MAXHOST,service, NI_MAXSERV, NI_NUMERICSERV|NI_NUMERICHOST);
                    if (s == 0){
                            printf("Received from %s:%s\n",host, service);
                    }else{
                            perror("getnameinfo");
                            return -1;               
                    }
                    if(access(buf,F_OK)==0){
                        sprintf(out,"%s","SI EXISTE \0");
                    }else{
                        sprintf(out,"%s","NO EXISTE \0");        
                    }
                    if (sendto(sfd, out, strlen(out), 0,(struct sockaddr *) &peer_addr,peer_addr_len) == -1){
                            perror("sendto");
                            return -1; 
                    }

               }

           }
           close(sfd);
           return 1;
       }


