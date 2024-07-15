 #include <unistd.h>
 #include <stdio.h>
 #include <errno.h>
 #include <string.h>
int main() {
   setuid(0);
   if(setuid(0)==-1){
    printf("Codigo de error :%d\n%s\n",errno,strerror(errno));
   }
   return 1;
}