#include <netdb.h>
       #include <stdio.h>
       #include <stdlib.h>
       #include <string.h>
       #include <sys/socket.h>
       #include <sys/types.h>
       #include <unistd.h>
       #include <sys/types.h>
       #include <pwd.h>

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
           hints.ai_socktype = SOCK_DGRAM; /* Datagram socket */
           hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
           hints.ai_protocol = 0;          /* Any protocol */

           s = getaddrinfo(argv[1], argv[2], &hints, &result);
           if (s != 0) {
                perror("getaddrinfo");
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
                perror("rp");
                return -1;
           }

           /* Read datagrams and echo them back to sender. */

           while (1) {
               char host[NI_MAXHOST], service[NI_MAXSERV];
               peer_addrlen = sizeof(peer_addr);
               nread = recvfrom(sfd, buf, BUF_SIZE, 0,(struct sockaddr *) &peer_addr, &peer_addrlen);
               if (nread == -1){
                    perror("recvfrom");
                    return -1;  
               }
               if(nread>0){
                    buf[nread-1]='\0';
                    s = getnameinfo((struct sockaddr *) &peer_addr,peer_addrlen, host, NI_MAXHOST,service, NI_MAXSERV, NI_NUMERICSERV|NI_NUMERICHOST);
                    if (s == 0){
                        printf("Received bytes from %s:%s\n", host, service);
                    }else{
                        perror("getnameinfo");
                        return -1;                
                    }
                    struct passwd *aux=getpwnam(buf);
                    
                    if(aux==NULL){
                        sprintf(buf,"%s","USER USUARIO NO ENCONTRADO");
                    }else{
                        sprintf(buf,"%s",aux->pw_dir);
                    }
                    if (sendto(sfd, buf, strlen(buf), 0, (struct sockaddr *) &peer_addr,peer_addrlen) == -1)
                    {
                            perror("sento");
                            return -1;  
                    }
               }
               
           }

           close(sfd);
           return 1;
       }