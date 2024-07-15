#include <stdio.h>
#include <unistd.h>
#include <time.h>
int main(){
    time_t a;
    a=time(NULL);
    struct tm *b;
    b=localtime(&a);
    printf("%d\n",b->tm_year + 1900);
    return 1;
}