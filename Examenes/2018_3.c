#include <netdb.h>
       #include <stdio.h>
       #include <stdlib.h>
       #include <string.h>
       #include <sys/socket.h>
       #include <sys/types.h>
       #include <unistd.h>
         #include <sys/wait.h>
       #define BUF_SIZE 500
        void handler()
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


           s = getaddrinfo(argv[1],argv[2],&hints, &result);
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

           freeaddrinfo(result);
           if(listen(sfd,5)==-1){
                perror("LISTEN");
                return -1;
           }
           while(1){
                char host[NI_MAXHOST], service[NI_MAXSERV];
                peer_addrlen = sizeof(peer_addr);
                int a=accept(sfd,(struct sockaddr *) &peer_addr, &peer_addrlen);
                s = getnameinfo((struct sockaddr *) &peer_addr,peer_addrlen, host, NI_MAXHOST,service, NI_MAXSERV, NI_NUMERICSERV);
                if (s == 0){
                    printf("Received from %s:%s\n",host, service);
                }else{
                    perror("getnameinfo");
                    return -1;
                }
                pid_t pid=fork();
                if(pid==-1){
                    perror("fork");
                    return -1;
                }else if(pid==0){
                    while((nread=recv(a,buf,BUF_SIZE,0))){
                        printf("PID :%d \n",getpid());
                        buf[nread]='\0';
                        if(send(a,buf,nread,0)==-1){
                            perror("send");
                            return -1;
                        }
                    
                    }
                    close(a);
                    
                }
            }
           
           close(sfd);

           return 1;
       }