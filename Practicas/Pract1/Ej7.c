#include <unistd.h>
#include <stdio.h>
int main(){
    if(pathconf("/",_PC_LINK_MAX)==-1){
        perror("Fallo de pathconf");
    }
    printf("numero maximo enlaces: %ld \n",pathconf("/",_PC_LINK_MAX));
    printf(" tamaño maximo de ruta : %ld \n",pathconf("/",_PC_PATH_MAX));
    printf(" nombre fichero: %ld \n",pathconf("/",_PC_NAME_MAX));
    return 1;
}