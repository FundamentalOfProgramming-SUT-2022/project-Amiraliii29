#include <stdio.h> 
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <stdlib.h>

void createfile();
FILE *fopen_mkdir(char *path, char *mode);
void rek_mkdir(char *path);

int main(){

    char input;

    while(1){
        char command[100] = {'\0'};
    for (int i = 0; ; i++)
    {
        scanf("%c" , &input);
        if(input == '-' || input == ' ')
            break;
        else{
            command[i] = input;
        }

    }
    //printf("--%s--" , command);
    if(!(strcmp(command , "createfile")))
        createfile();
    else if(!(strcmp(command , "exit")))
        return 0;
    }
    return 0;
}

void createfile(){
    getchar();
    getchar();
    getchar();
    getchar();
    getchar();
    getchar();
    char in;
    char fileName[100] = {'\0'};
    in = getchar();
    printf("\n%c\n" , in);
    if(in == '"'){
        
        for (int i = 0; ; i++)
        {
            in = getchar();
            if(in == '"')
                break;
            else if(in == ' ')
                fileName[i] = 'A';
            else{
                fileName[i] = in;
            }                
        }
    }
    else{
        in = getchar();
        for (int i = 0; ; i++)
        {
            if(in == ' ' || in == '\n')
                break;
            else 
                fileName[i] = in;
            in = getchar();
        }
    }
    
    FILE *fp;
    fopen_mkdir(fileName , ")");

        fp = fopen(fileName , "w");
        fclose(fp);
        fp = NULL;
    return;
}

void rek_mkdir(char *path) {
    char *sep = strrchr(path, '/');
    if(sep != NULL) {
        *sep = 0;
        rek_mkdir(path);
        *sep = '/';
    }
    if(mkdir(path, 0777) && errno != EEXIST)
        printf("error while trying to create '%s'\n%m\n", path); 
}

FILE *fopen_mkdir(char *path, char *mode) {
    char *sep = strrchr(path, '/');
    if(sep) { 
        char *path0 = strdup(path);
        path0[ sep - path ] = 0;
        rek_mkdir(path0);
        free(path0);
    }
    return fopen(path,mode);
}