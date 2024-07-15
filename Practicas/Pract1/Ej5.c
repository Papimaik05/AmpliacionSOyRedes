#include <unistd.h>
#include <stdio.h>
#include <sys/utsname.h>
int main(){
    struct utsname buf;
    if(uname(&buf)==-1){
        perror("Fallo de uname");
    }
    printf("Sysname: %s\n",buf.sysname);
     printf("Nodename: %s\n",buf.nodename);
      printf("Release: %s\n",buf.release);
       printf("Version: %s\n",buf.version);
        printf("Machine: %s\n",buf.machine);
    return 1;
}
