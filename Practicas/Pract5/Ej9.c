#include <netdb.h>
       #include <stdio.h>
       #include <stdlib.h>
       #include <string.h>
       #include <sys/socket.h>
       #include <sys/types.h>
       #include <unistd.h>
        #include <signal.h>
        #include <sys/syscall.h>
       #define BUF_SIZE 500
        void zombie(){
            wait(NULL);
        }
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

               if (bind(sfd, rp->ai_addr, rp->ai_addrlen) == 0)
                   break;                  /* Success */

               
           }
           freeaddrinfo(result);           /* No longer needed */
           if(listen(sfd,5)==-1){
                perror("listen");
                return -1;
           }
           struct sockaddr_storage  peer_addr;
           socklen_t peer_addrlen;
           int sad;
           ssize_t rec;
           struct sigaction act;
           act.sa_handler=zombie();
           act.sa_flags=0;
           emptyset(&act.sa_mask);
           sigaddset(&act.sa_maskm,SIGCHLD);
           sigaction(SIGCHLD,&act,NULL);
           while(1){
                char host[NI_MAXHOST], service[NI_MAXSERV];
                peer_addrlen = sizeof(peer_addr);
                sad=accept(sfd,(struct sockaddr *)&peer_addr,&peer_addrlen);
                if(sad==-1){
                    perror("listen");
                    return -1;
                }
                s = getnameinfo((struct sockaddr *) &peer_addr,peer_addrlen, host, NI_MAXHOST,service, NI_MAXSERV, NI_NUMERICSERV|NI_NUMERICHOST);
                if (s == 0){
                    printf("Received bytes from %s:%s\n", host, service);
                }else{
                    perror("GETNAMEINFO");
                    return -1;
                }

                pid_t pid=fork();
                if(pid==-1){
                    perror("FORK");
                    return 0;
                }else if(pid==0){
                    while((rec=recv(sad,buf,BUF_SIZE,0))>0){
                   
                    buf[rec]='\0';
                    if(buf[0]=='q' && rec==2){
                        printf("CONEXION TERMINADA \n");
                        exit(0);
                    }
                    if (send(sad, buf, rec, 0) == -1){
                        perror("SEND");
                        return -1;
                    }
                    //exit(0);
                    }
                }else{
                    close(sad);
                }

                

           }
           close(sfd);


           return 1;
       }