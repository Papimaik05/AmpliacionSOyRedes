#include <stdio.h>
#include <unistd.h>
#include <time.h>
int main(){
    char buf[100];
    time_t a;
    a=time(NULL);
    struct tm *b;
    b=localtime(&a);
    strftime(buf,100,"%a %b %d %T %y",b)
    printf("%s\n",buf)
    return 1;
}