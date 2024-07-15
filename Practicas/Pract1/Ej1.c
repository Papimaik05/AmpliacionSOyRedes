 #include <unistd.h>
 #include <stdio.h>
 #include <errno.h>

int main() {
   setuid(0);
   if(setuid(0)==-1){
    perror("setuid");
   }
   return 1;
}
