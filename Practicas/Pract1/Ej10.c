#include <stdio.h>
#include <unistd.h>
#include <sys/types.h> 
#include <pwd.h>
int main(){
    printf("Id real:%d\n",getuid());
    printf("Id efectivo%d\n",geteuid());
    struct passwd *real;
    real=getpwuid(getuid());
    if(real==NULL){
        perror("error getpwuid");
    }
    printf("Usuario:%s\n",real->pw_name);
    printf("Home:%s\n",real->pw_dir);
    printf("Descripcion:%s\n",real->pw_gecos);
    return 1;
}