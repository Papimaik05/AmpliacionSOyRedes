
       #include <netdb.h>
       #include <stdio.h>
       #include <errno.h>       
       #include <stdlib.h>
       #include <string.h>
       #include <sys/socket.h>
       #include <sys/types.h>
       #include <unistd.h>
       #include <sys/resource.h>

       #define BUF_SIZE 500

       int
       main(int argc, char *argv[])
       {
           int                      sfd, s;
           char                     buf[BUF_SIZE],out[BUF_SIZE];
           ssize_t                  nread;
           socklen_t                peer_addrlen;
           struct addrinfo          hints;
           struct addrinfo          *result, *rp;
           struct sockaddr_storage  peer_addr;

           if (argc != 3) {
                perror("GETADDRINFO");
                return -1;
           }

           memset(&hints, 0, sizeof(hints));
           hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
           hints.ai_socktype = SOCK_STREAM; /* Datagram socket */
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

           if(listen(sfd,5)==-1){
                perror("listen");
                return -1; 
           }

           while (1) {
               char host[NI_MAXHOST], service[NI_MAXSERV];
               peer_addrlen = sizeof(peer_addr);
               int a=accept(sfd,(struct sockaddr *) &peer_addr, &peer_addrlen);
               if(a==-1){
                    perror("accept");
                    return -1;                 
               }
               s = getnameinfo((struct sockaddr *) &peer_addr,peer_addrlen, host, NI_MAXHOST,service, NI_MAXSERV, NI_NUMERICSERV|NI_NUMERICHOST);
               if (s == 0){
                    printf("Received bytes from %s:%s\n",host,service);
               }
               else{
                    perror("GETNAMEINFO");
                    return -1;                
               }
               while(nread=recv(a, buf, BUF_SIZE, 0)){
                    buf[nread-1]='\0';
                    if(atoi(buf)==0){
                        perror("ESO SON LETRASSSS");
                        
                    }else{
                        errno=0;
                        int p=getpriority(PRIO_PROCESS,atoi(buf));
                        if(p==-1 && errno==ESRCH){
                            perror("ESO NO ES UN PID VALIDO");
                        
                        }else{
                            printf("PID : %s con nice: %d \n",buf,p);
                            sprintf(out,"%d",p);
                            if (send(a, out,strlen(out), 0) == -1){
                                perror("GETNAMEINFO");
                                return -1; 
                            }
                        }
                    }
                    
                    
               }       
              
           }
           close(sfd);
           return 1;
       }