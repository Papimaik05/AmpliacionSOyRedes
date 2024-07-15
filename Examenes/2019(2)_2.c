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
           ssize_t                  nread;
           socklen_t                peer_addrlen;
           struct addrinfo          hints;
           struct addrinfo          *result, *rp;
           struct sockaddr_storage  peer_addr;

           if (argc != 3) {
                perror("BAD USAGE");
                return -1;
           }

           memset(&hints, 0, sizeof(hints));
           hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
           hints.ai_socktype = SOCK_STREAM; /* Datagram socket */
           hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
           hints.ai_protocol = 0;          /* Any protocol */


           s = getaddrinfo(argv[1], argv[2], &hints, &result);
           if (s != 0) {
                perror("BAD USAGE");
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

           freeaddrinfo(result);           
           if (rp == NULL) {               
               fprintf(stderr, "Could not bind\n");
               exit(EXIT_FAILURE);
           }

           if(listen(sfd,5)==-1){
                perror("listen");
                return -1;
           }
           while(1){
               char host[NI_MAXHOST], service[NI_MAXSERV];
               peer_addrlen = sizeof(peer_addr);
               int a=accept(sfd,(struct sockaddr *) &peer_addr, &peer_addrlen);
               if(a==-1){
                    perror("accept");
                    return -1;
               }
               s = getnameinfo((struct sockaddr *) &peer_addr,peer_addrlen, host, NI_MAXHOST,service, NI_MAXSERV, NI_NUMERICSERV|NI_NUMERICHOST);
               if (s == 0){
                    printf("Received bytes from %s:%s\n",host, service);
               }else{
                    perror("getnameinfo");
                    return -1;
               }
               while((nread=recv(a, buf, BUF_SIZE, 0))){
                    buf[nread]='\0';

                    if (send(a, host, strlen(host), 0) ==-1){
                        perror("sendto");
                        return -1;
                    }
               }
               close(a);
            }
            close(sfd);
            return 1;
        }
         
       