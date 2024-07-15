#include <unistd.h>
#include <stdio.h>
int main(){
    if(sysconf(_SC_ARG_MAX)==-1){
        perror("Fallo de sysconf");
    }
    printf("Longitud maxima de argumentos: %ld \n",sysconf(_SC_ARG_MAX));
    printf(" número máximo de hijos : %ld \n",sysconf(_SC_CHILD_MAX));
    printf(" número máximo de fab: %ld \n",sysconf(_SC_OPEN_MAX));
    return 1;
}