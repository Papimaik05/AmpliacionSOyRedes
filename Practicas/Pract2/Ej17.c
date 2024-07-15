#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
int main(int argc,char * argv[]){
    if(argc!=2){
        perror("ERROR ARGUMENTOS");
        return 0;
    }
    DIR *a = opendir(argv[1]);
    if(a==NULL){
        perror("ERROR DIRECTORIO");
        return 0;
    }
    struct dirent *leer;
    while((leer = readdir(a)) != NULL){
        printf("Nombre de fichero : %s \n",leer->d_name);
        char *concat = (char*) malloc(strlen(argv[1]+ 40));
        strcpy(concat,argv[1]);
        strcat(concat,leer->d_name);
        struct stat buf;
        if(stat(concat,&buf)==-1){
            perror("error stat");
            return 0;
        }
        if(S_ISREG(buf.st_mode)){
            strcat(concat,"*");
            printf("RTRegular: %s \n",concat);
        }
        else if(S_ISDIR(buf.st_mode)){
            strcat(concat,"/");
            printf("DDirectorio: %s \n",concat);
        }else if(S_ISLNK(buf.st_mode)){
            char buf2[100];
            strcat(concat,"->");
            readlink(concat,buf2,100);
            strcat(concat,buf2);
            printf("Simbolico: %s \n",concat);
        }
    }
    closedir(a);
    return 1;

}