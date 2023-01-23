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
void insert();
void cat();
void removestr();
void copystr();
void cutstr();
void pastestr();

char clipboard[1000000];

int main(){

    printf("Welcome to sheikh vim :)\n");
    printf("please type \"exit\" to stop program\n");

    char input;

    while(1){
        char command[100] = {'\0'};
    for (int i = 0; ; i++)
    {
        input = getchar();
        if(input == '-' || input == ' ' || input == '\n')
            break;
        else
            command[i] = input;
        

    }
    //printf("--%s--" , command);
    if(!(strcmp(command , "createfile")))
        createfile();
    else if(!(strcmp(command , "exit")))
        return 0;
    else if(!(strcmp(command , "insertr")))
        insert();
    
    else if(!(strcmp(command , "cat")))
        cat();
    else if(!(strcmp(command , "removestr")))
        removestr();
    else if(!(strcmp(command , "copystr")))
        copystr();
    else if(!(strcmp(command , "cutstr")))
        cutstr();
    else if(!(strcmp(command , "pastestr")))
        pastestr();
    }

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
    if(in == '\"'){
        getchar();
        for (int i = 0; ; i++)
        {
            in = getchar();
            if(in == '\"')
                break;
            else{
                fileName[i] = in;
            }                
        }
    }
    else{
        in = getchar();
        for (int i = 0; ; i++)
        {
            if(in == '\n')
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

void insert(){
    getchar();
    getchar();
    getchar();
    getchar();
    getchar();
    getchar();
    char in;
    char fileName[100] = {'\0'};
    in = getchar();
    if(in == '\"'){
        getchar();
        for (int i = 0; ; i++)
        {
            in = getchar();
            if(in == '\"')
                break;
            else{
                fileName[i] = in;
            }                
        }
    }
    else{
        in = getchar();
        for (int i = 0; ; i++)
        {
            if(in == '-' || in == ' ')
                break;
            else 
                fileName[i] = in;
            in = getchar();
        }
    }
    //printf("---%s---\n" , fileName);
    char text[2000000];
    while (in != 'r')
    {
        in = getchar();
    }
    getchar();
    in = getchar();
    if(in == '"'){
        for (int i = 0; ; i++)
        {
            in = getchar();
            if(in == '"')
                break;
            else
                text[i] = in;
        }
    }
    else{
        for (int i = 0; ; i++)
        {
            if(in == '-')
                break;
            else
                text[i] = in ;
            in = getchar();
        }
        
    }
    //printf("--%s--\n" , text);
    do
    {
        in = getchar();
    } while (in != 's');
    int line , x;
    scanf(" %d:%d" , &line , &x);
   //printf("---%d : %d---\n" , line , x);

    FILE *file;
    if(!(file = fopen(fileName , "r")))
        printf("Bro File doesn't Exist :|\n");
    char temp[1000000];
    int line_counter = 0;
    char get , lstring[100];
    int j = 0;
    while (line_counter < line - 1)
    {
            //fscanf(file , "%[^\n]" ,lstring);
            fscanf(file , "%[^\n]%*c" , lstring);
            for (int f = 0; f < strlen(lstring); f++)
            {
                temp[j] = lstring[f];
                j++;
            }
            temp[j] = '\n';
            j++;
            //printf("1%s" , lstring);
            line_counter++;
    }
    for (int i = 0; i < x; i++)
    {
        get = fgetc(file);
        //printf("2%c" , get);
        temp[j] = get;
        j++;
    }
    for (int i = 0; i < strlen(text) ;i++)
    {
        //printf("3%c" , text[i]);
        if(text[i] == '\\'){
            if(text[i+1] == 'n'){
                temp[j] = '\n';
                i++;
                j++;
            }
            else if(text[i+1] == '\\'){
                i++;
                temp[j] = text[i];
                j++;
                i++;
                temp[j] = text[i];
                j++;
            }
            else if(text[i+1] == '\"'){
                i++; 
                temp[j] = '\"';
                j++;
                continue;
            }
        }
        else if(text[i] == '\"'){
            continue;
        }
        else{
        temp[j] = text[i];
        j++;
        }
    }
    while (get != EOF)
    {
        get = fgetc(file);
        //printf("4%c" , get);
        temp[j] = get;
        j++;
    }
    fclose(file);
    file = fopen(fileName , "w");
    for (int i = 0; i < strlen(temp); i++)
    {
        fputc(temp[i] , file);
    }
    fclose(file);
}

void cat(){
    char get;
    char fileName[1024];
    while((get = getchar()) != 'e'){
    }
    getchar();
    for (int i = 0; ; i++)
    {
        get = getchar();
        if(get == '\n')
            break;
        else 
            fileName[i] = get;
    }
    FILE *fp;
    printf("%s\n" , fileName);
    if(!(fp = fopen(fileName , "r")))
        printf("file doesn't exist :|\n");

    while ((get = fgetc(fp)) != EOF)
    {
        printf("%c" , get);
    }    
}

void removestr(){
    getchar();
    getchar();
    getchar();
    getchar();
    getchar();
    getchar();
    char in;
    char fileName[100] = {'\0'};
    in = getchar();
    if(in == '\"'){
        getchar();
        for (int i = 0; ; i++)
        {
            in = getchar();
            if(in == '\"')
                break;
            else{
                fileName[i] = in;
            }                
        }
    }
    else{
        in = getchar();
        for (int i = 0; ; i++)
        {
            if(in == '-' || in == ' ')
                break;
            else 
                fileName[i] = in;
            in = getchar();
        }
    }

    while ((in = getchar()) != 's')
    {
    }
    
    int line , x;
    scanf(" %d:%d" , &line , &x);
    while ((in = getchar()) != 'e')
    {
    }
    int size;
    scanf("%d" , &size);
    while ((in = getchar()) != '-')
    {
    }
    char direction = getchar();
    FILE *file;
    if(!(file = fopen(fileName , "r")))
        printf("Bro File doesn't Exist :|\n");  
    file = fopen(fileName , "r");
    char temp[1000000];
    int line_counter = 0;
    char get , lstring[100];
    int j = 0;

    if(direction == 'f'){
        while (line_counter < line - 1)
        {
                fscanf(file , "%[^\n]%*c" , lstring);
                for (int f = 0; f < strlen(lstring); f++)
                {
                    temp[j] = lstring[f];
                    j++;
                }
                temp[j] = '\n';
                j++;
                line_counter++;
        }
        for (int i = 0; i < x; i++)
        {
            get = fgetc(file);
            temp[j] = get;
            j++;
        }
        for (int i = 0; i < size ; i++)
        {
            get = fgetc(file);
        }
        while (get != EOF)
        {
            get = fgetc(file);
            temp[j] = get;
            j++;
        }
        fclose(file);
        file = fopen(fileName , "w");
        for (int i = 0; i < strlen(temp); i++)
        {
            fputc(temp[i] , file);
        }
        fclose(file);
    }
    else if(direction == 'b'){
        char temp1[1000000] , temp2[1000000];
        char temp3[2000000] = {'\0'}; 
        int j1 = 0;
        int line_counter = 0;
        while (line_counter < line - 1)
        {
            char lstring[100] = {'\0'};
            fscanf(file , "%[^\n]%*c" , lstring);
            for (int f = 0; f < strlen(lstring); f++)
            {
                temp1[j1] = lstring[f];
                j1++;
            }
            temp1[j1] = '\n';
            j1++;
            line_counter++;
        }
        for (int i = 0; i < x; i++)
        {
            get = fgetc(file);
            temp1[j1] = get;
            j1++;
        }
        int j2 = 0;
        get = fgetc(file);
        while (get != EOF)
        {
            temp2[j2] = get;
            j2++;
            get = fgetc(file);
        }

        int j3 = 0;
        for (int f1 = 0; f1 < strlen(temp1) - size; f1++)
        {
            temp3[j3] = temp1[f1];
            j3++;
        }
        for (int f1 = 0; f1 < strlen(temp2); f1++)
        {
            temp3[j3] = temp2[f1];
            j3++;
        }
        fclose(file);
        file = fopen(fileName , "w");        

        if ( file )
        {
            fputs(temp3,file);
            }
        else
            {
                printf("Failed to open the file\n");
                }


        fclose(file);
    }
}

void copystr(){
    getchar();
    getchar();
    getchar();
    getchar();
    getchar();
    getchar();
    char in;
    char fileName[100] = {'\0'};
    in = getchar();
    if(in == '\"'){
        getchar();
        for (int i = 0; ; i++)
        {
            in = getchar();
            if(in == '\"')
                break;
            else{
                fileName[i] = in;
            }                
        }
    }
    else{
        in = getchar();
        for (int i = 0; ; i++)
        {
            if(in == '-' || in == ' ')
                break;
            else 
                fileName[i] = in;
            in = getchar();
        }
    }

    while ((in = getchar()) != 's')
    {
    }
    
    int line , x;
    scanf(" %d:%d" , &line , &x);
    while ((in = getchar()) != 'e')
    {
    }
    int size;
    scanf("%d" , &size);
    while ((in = getchar()) != '-')
    {
    }
    char direction = getchar();
    FILE *file;
    if(!(file = fopen(fileName , "r")))
        printf("Bro File doesn't Exist :|\n");  
    file = fopen(fileName , "r");
    char temp[1000000];
    int line_counter = 0;
    char get , lstring[100];
    int j = 0;
    if(direction == 'f'){
        while (line_counter < line - 1)
        {
                fscanf(file , "%[^\n]%*c" , lstring);
                for (int f = 0; f < strlen(lstring); f++)
                {
                    temp[j] = lstring[f];
                    j++;
                }
                temp[j] = '\n';
                j++;
                line_counter++;
        }
        for (int i = 0; i < x; i++)
        {
            get = fgetc(file);
            temp[j] = get;
            j++;
        }
        for (int i = 0; i < 1000000 ; i++)
        {
            clipboard[i] = '\0';
        }
        for (int i = 0; i < size ; i++)
        {
            get = fgetc(file);
            clipboard[i] = get;
        }
        fclose(file);
        printf("%s\n" , clipboard);
    }
    else if(direction == 'b'){
        char temp1[1000000] , temp2[1000000];
        int j1 = 0;
        int line_counter = 0;
        while (line_counter < line - 1)
        {
            char lstring[100] = {'\0'};
            fscanf(file , "%[^\n]%*c" , lstring);
            for (int f = 0; f < strlen(lstring); f++)
            {
                temp1[j1] = lstring[f];
                j1++;
            }
            temp1[j1] = '\n';
            j1++;
            line_counter++;
        }
        for (int i = 0; i < x; i++)
        {
            get = fgetc(file);
            temp1[j1] = get;
            j1++;
        }
        int j2 = 0;
        get = fgetc(file);
        while (get != EOF)
        {
            temp2[j2] = get;
            j2++;
            get = fgetc(file);
        }

        int j3 = 0;
        for (int i = 0; i < 1000000; i++)
        {
            clipboard[i] = '\0';
        }
        for (int f1 = strlen(temp1) - size ; f1 < strlen(temp1) ; f1++)
        {
            clipboard[j3] = temp1[f1];
            j3++;
        }
        fclose(file);
    }
}

void cutstr(){
    getchar();
    getchar();
    getchar();
    getchar();
    getchar();
    getchar();
    char in;
    char fileName[100] = {'\0'};
    in = getchar();
    if(in == '\"'){
        getchar();
        for (int i = 0; ; i++)
        {
            in = getchar();
            if(in == '\"')
                break;
            else{
                fileName[i] = in;
            }                
        }
    }
    else{
        in = getchar();
        for (int i = 0; ; i++)
        {
            if(in == '-' || in == ' ')
                break;
            else 
                fileName[i] = in;
            in = getchar();
        }
    }

    while ((in = getchar()) != 's')
    {
    }
    
    int line , x;
    scanf(" %d:%d" , &line , &x);
    while ((in = getchar()) != 'e')
    {
    }
    int size;
    scanf("%d" , &size);
    while ((in = getchar()) != '-')
    {
    }
    char direction = getchar();
    FILE *file;
    if(!(file = fopen(fileName , "r")))
        printf("Bro File doesn't Exist :|\n");  
    file = fopen(fileName , "r");
    char temp[1000000];
    int line_counter = 0;
    char get , lstring[100];
    int j = 0;
    if(direction == 'f'){
        while (line_counter < line - 1)
        {
                fscanf(file , "%[^\n]%*c" , lstring);
                for (int f = 0; f < strlen(lstring); f++)
                {
                    temp[j] = lstring[f];
                    j++;
                }
                temp[j] = '\n';
                j++;
                line_counter++;
        }
        for (int i = 0; i < x; i++)
        {
            get = fgetc(file);
            temp[j] = get;
            j++;
        }
        for (int i = 0; i < 1000000 ; i++)
        {
            clipboard[i] = '\0';
        }
        for (int i = 0; i < size ; i++)
        {
            get = fgetc(file);
            clipboard[i] = get;
        }
        while ((get = fgetc(file)) != EOF)
        {
            temp[j] = get;
            j++;
        }
        fclose(file);
        file = fopen(fileName , "w");
        for (int i = 0; i < strlen(temp) ; i++)
        {
            fputc(temp[i] , file);
        }
        fclose(file);
    }
    else if(direction == 'b'){
        char temp1[1000000] , temp2[1000000];
        char temp3[2000000] = {'\0'};
        int j1 = 0;
        int line_counter = 0;
        while (line_counter < line - 1)
        {
            char lstring[100] = {'\0'};
            fscanf(file , "%[^\n]%*c" , lstring);
            for (int f = 0; f < strlen(lstring); f++)
            {
                temp1[j1] = lstring[f];
                j1++;
            }
            temp1[j1] = '\n';
            j1++;
            line_counter++;
        }
        for (int i = 0; i < x; i++)
        {
            get = fgetc(file);
            temp1[j1] = get;
            j1++;
        }
        int j2 = 0;
        get = fgetc(file);
        while (get != EOF)
        {
            temp2[j2] = get;
            j2++;
            get = fgetc(file);
        }

        int j3 = 0;
        for (int i = 0; i < strlen(temp1) - size ; i++)
        {
            temp3[j3] = temp1[i];
            j3++;
        }
        int j4 = 0;
        for (int i = 0; i < 1000000 ; i++)
        {
            clipboard[i] = '\0';
        }
        
        for (int f1 = strlen(temp1) - size ; f1 < strlen(temp1) ; f1++)
        {
            clipboard[j4] = temp1[f1];
            j4++;
        }
        for (int i = 0; i < strlen(temp2); i++)
        {
            temp3[j3] = temp2[i];
            j3++;
        }
        fclose(file);
        file = fopen(fileName , "w");
        for (int i = 0; i < strlen(temp3); i++)
        {
            fputc(temp3[i] , file);
        }
        fclose(file);
    }
}

void pastestr(){
    char in;
    while ((in = getchar()) != 'e')
    {
    }
    char fileName[100] = {'\0'};
    in = getchar();
    if(in == '\"'){
        getchar();
        for (int i = 0; ; i++)
        {
            in = getchar();
            if(in == '\"')
                break;
            else{
                fileName[i] = in;
            }                
        }
    }
    else{
        in = getchar();
        for (int i = 0; ; i++)
        {
            if(in == '-' || in == ' ')
                break;
            else 
                fileName[i] = in;
            in = getchar();
        }
    }
    printf("---%s---\n" , fileName);
    do
    {
        in = getchar();
    } while (in != 's');
    int line , x;
    scanf(" %d:%d" , &line , &x);
   printf("---%d : %d---\n" , line , x);

    FILE *file;
    if(!(file = fopen(fileName , "r")))
        printf("Bro File doesn't Exist :|\n");
    char temp[1000000];
    int line_counter = 0;
    char get , lstring[100];
    int j = 0;
    while (line_counter < line - 1)
    {
            //fscanf(file , "%[^\n]" ,lstring);
            fscanf(file , "%[^\n]%*c" , lstring);
            for (int f = 0; f < strlen(lstring); f++)
            {
                temp[j] = lstring[f];
                j++;
            }
            temp[j] = '\n';
            j++;
            //printf("1%s" , lstring);
            line_counter++;
    }
    for (int i = 0; i < x; i++)
    {
        get = fgetc(file);
        //printf("2%c" , get);
        temp[j] = get;
        j++;
    }
    for (int i = 0; i < strlen(clipboard) ; i++)
    {
        temp[j] = clipboard[i];
        j++;
    }
    while (get != EOF)
    {
        get = fgetc(file);
        //printf("4%c" , get);
        temp[j] = get;
        j++;
    }
    fclose(file);
    file = fopen(fileName , "w");
    for (int i = 0; i < strlen(temp); i++)
    {
        fputc(temp[i] , file);
    }
    fclose(file);
}