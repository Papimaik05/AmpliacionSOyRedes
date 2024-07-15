#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <time.h>

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
    printf("Major:%d\n",major(buf.st_dev));
    printf("Minor:%d\n",minor(buf.st_dev));
    printf("Inodo:%ld\n",buf.st_ino);
    if(S_ISREG(buf.st_mode)){
        printf("Es un fichero regular \n");
    }
    else if(S_ISDIR(buf.st_mode)){
        printf("Es un directorio \n");
    }
    else if (S_ISLNK(buf.st_mode)){
        printf("Es un enlace simbolico\n");
    }
     printf("Ultima hora :%s\n",ctime(&buf.st_atime));
    return 1;
}
