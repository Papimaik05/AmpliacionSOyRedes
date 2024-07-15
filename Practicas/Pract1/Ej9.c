#include <stdio.h>
#include <unistd.h>
int main(){
    printf("%d\n",getuid())
    printf("%d\n",geteuid())
    return 1;
}