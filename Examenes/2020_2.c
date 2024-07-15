#include <sys/types.h>
       #include <stdio.h>
       #include <stdlib.h>
       #include <unistd.h>
       #include <string.h>
       #include <sys/socket.h>
       #include <netdb.h>
       #include <time.h>
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
           char buf[BUF_SIZE],time[BUF_SIZE];

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
                perror("GETADDRINFO");
                return -1;
           }
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
                perror("GETADDRINFO");
                return -1;
           }
           while(1){
               peer_addr_len = sizeof(peer_addr);
               char host[NI_MAXHOST], service[NI_MAXSERV];
               nread = recvfrom(sfd, buf, BUF_SIZE, 0,(struct sockaddr *) &peer_addr, &peer_addr_len);
               if (nread == -1){
                    perror("recvfrom");
                    return -1;
               }         
               s = getnameinfo((struct sockaddr *) &peer_addr,peer_addr_len, host, NI_MAXHOST,service, NI_MAXSERV, NI_NUMERICSERV|NI_NUMERICHOST);
               if (s == 0){
                    printf("Received %zd bytes from %s:%s\n",nread, host, service);
               }
               else{
                    perror("getnameinfo");
                    return -1;
               }
               time_t tim=time(NULL);
               struct tm *aux=localtime(&tim);
               ssize_t b=strftime(buftime,BUF_SIZE,"%T",aux);     
               if (sendto(sfd, buftime, b, 0,(struct sockaddr *) &peer_addr,peer_addr_len) != nread){
                    perror("getnameinfo");
                    return -1;
               }
           }
           close(sfd);

        return 1;
       }


