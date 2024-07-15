#include <stdio.h>
#include <stdlib.h>
 #include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc ,char* argv[]){
    if(argc != 2){
        printf("ERROR DE ARGUMENTOS");
        return 0;
    }
    struct stat buf;
    if(stat(argv[1],&buf)==-1){
        perror("ERROR STAT");
        return 0;
    }
    if(S_ISREG(buf.st_mode)){

        char *hard_name = (char*) malloc(strlen(argv[1]) + 5);
        char *sym_name = (char*) malloc(strlen(argv[1]) + 4);
        strncpy(hard_name, argv[1],sizeof(argv[1]-5));
        strncpy(sym_name, argv[1],,sizeof(argv[1]-5));
       if(link(argv[1],strcat(hard_name,".hard"))==-1){
        perror("enalce fisico error");
        return 0;
       }
       if(symlink(argv[1],strcat(sym_name,".sym"))==-1){
        perror("enalce simbolico error");
        return 0;
       }
    }
    else {
        printf("NO ES UN FICHERO REGULAR");
        return 0;
    }
    return 1;
}
