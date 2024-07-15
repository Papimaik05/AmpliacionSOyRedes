#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

int main(int argc, char *argv[]){
    if(argc!=2){
        perror("BAD USAGE");
        return -1;
    }
    DIR *d=opendir(argv[1]);
    if(d==NULL){
        perror("OPENDIR");
        return -1;
    }

    struct dirent *aux;
    while((aux=readdir(d))!=NULL){
        printf("NOMBRE FICHERO:%s\n",aux->d_name);
        struct stat auxstat;
        char auxchar[500];
        sprintf(auxchar,"%s%s",argv[1],aux->d_name);
        if(stat(auxchar,&auxstat)!=-1){
            printf("UID PROP:%s\n",auxstat.st_uid);
            printf("INODO:%s\n",auxstat.st_ino);
            printf("TAMAÑO:%s\n",auxstat.st_size);
        }else{
            perror("OPENDIR");
            return -1;
        }
    }
    closedir(d);
    return 1;
}