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
void findstr();
void replacestr();

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
    else if(!(strcmp(command , "find")))
        findstr();
    else if(!(strcmp(command , "replace")))
        replacestr();
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
    char fileName[1024] = {'\0'};
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
    if(!(fp = fopen(fileName , "r")))
        printf("file doesn't exist :|\n");

    while ((get = fgetc(fp)) != EOF)
    {
        printf("%c" , get);
    }
    fclose(fp);
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
    //printf("---%s---\n" , fileName);
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

void findstr(){
    char get;
    int flagv = 0;
    char attribute[100] = {'\0'};
    char fileName[200] = {'\0'};
    char tobefound[1000] = {'\0'};
    char tobefounds[20][300] = {'\0'};
    while((get = getchar()) != 'r'){
    }
    int wordnum = 0;
    get = getchar();
    /*if( get == '\"'){
        int breakflag = 0;
        for (wordnum = 0; ; )
        {
            for (int j = 0; ; j++)
            {
                get = getchar();
                if(get == ' '){
                    wordnum++;
                    break;
                }
                else if(get == '\"'){
                    breakflag = 1;
                    break;
                }
                tobefounds[i][j] = get;
                if(get )
            }
            if(breakflag == 1)
                break; 
        }        
    }
    else*/{
        get = getchar();
        for (int i = 0; ; i++)
        {
            if(get == ' ' || get =='-')
                break;
            else
                tobefound[i] = get;
            get = getchar();
        }
        //printf("---string:%s---\n" , tobefound);
    }
    while((get = getchar()) != 'e'){
    }
    getchar();
    for (int i = 0; ; i++)
    {
        get = getchar();
        if(get == '\n')
            break;
        else if(get == ' '){
            flagv = 1;
            break;
        }
        else 
            fileName[i] = get;
    }
    //printf("---file name:%s---\n" , fileName);
    if(flagv == 1){
        getchar();
        for (int i = 0 ; ; i++)
        {
            get = getchar();
            if(get == '\n')
                break;
            else 
                attribute[i] = get;
        }
        
    }
    FILE *fp;
    char ch;
    int count = 0;
    int pos[30] , posw[30];
    int pointer = 0;
    int loop;

    if((fp = fopen(fileName, "r")) == 0){
        printf("file doesn't exist\n");
        return;
    }

    do 
    {
        char word[50] = {'\0'};
        ch = fscanf(fp, "%s", word);
        //if(tobefound[0] == '*'){
        //    word[0] = '*';
        //    for (int i = 0; i < count; i++)
        //    {
        //        /* code */
        //    }
        //    
        //}

        for (int i = 0; i < strlen(tobefound); i++)
        {
            if(tobefound[i] == '\\' && tobefound[i+1] =='*'){
                word[i] = '\\';
                word[i+1] = '*';
                //printf("tobefound:%s\n" , tobefound);
                //printf("word:%s\n" , word);
                break;
            }
            else if(tobefound[i] == '*'){
                tobefound[i+1] = '\0';
                word[i] = '*';
                word[i+1] = '\0';
                //printf("--tobefound:%s\n" , tobefound);
                //printf("word:%s\n" , word);
            }
        }
        
        if(strcmp(word, tobefound) == 0)
        {
            pos[count] = pointer; 
            posw[count] = wordnum;
            count++;
            
        }
        pointer += (strlen(word));
        pointer++;
        wordnum++;
        //printf("%s ",word);       
    } while (ch != EOF);

    if(flagv == 0){
        if(count == 0)  
            printf("-1\n");
        else
            {
            printf("'%s' starts from character number: ", tobefound);
            printf("%d ", pos[0] + 1);

            }
    }
    else if(!(strcmp(attribute , "count"))){
        printf("this text has been repeated %d times\n" , count);
    }
    else if(!(strcmp(attribute , "at"))){
        int n;
        scanf("%d" , &n);
        if(n > count)
            printf("-1\n");
        else
            printf("the %dthtime that text repeated starts from character number: %d" , n , pos[n-1] + 1 );
    }
    else if(!(strcmp(attribute , "byword"))){
        if(count == 0)
            printf("-1\n");
        else
            printf("%s starts from word number: %d\n" , tobefound ,  posw[0] + 1);
    }
    else if(!(strcmp(attribute , "all"))){
        for (int i = 0; i < count ; i++)
        {
            printf("'%s' starts from character number: ", tobefound);
            printf("%d ", pos[i] + 1);
        }
    }

    fclose(fp);
}

void replacestr(){
    char get;
    int flagv = 0;
    char attribute[100] = {'\0'};
    char fileName[200] = {'\0'};
    char tobefound[1000] = {'\0'};
    char toreplace[1000] = {'\0'};
    char tobefounds[20][300] = {'\0'};
    while((get = getchar()) != '1'){
    }
    get = getchar();
    /*if( get == '\"'){
        int breakflag = 0;
        for (wordnum = 0; ; )
        {
            for (int j = 0; ; j++)
            {
                get = getchar();
                if(get == ' '){
                    wordnum++;
                    break;
                }
                else if(get == '\"'){
                    breakflag = 1;
                    break;
                }
                tobefounds[i][j] = get;
                if(get )
            }
            if(breakflag == 1)
                break; 
        }        
    }
    else*/{
        get = getchar();
        for (int i = 0; ; i++)
        {
            if(get == ' ' || get =='-')
                break;
            else
                tobefound[i] = get;
            get = getchar();
        }
        printf("---string:%s---\n" , tobefound);
    }
    while((get = getchar()) != '2'){
    }
        getchar();
        get = getchar();
        for (int i = 0; ; i++)
        {
            if(get == ' ' || get =='-')
                break;
            else
                toreplace[i] = get;
            get = getchar();
        }
        printf("---string:%s---\n" , toreplace);

    while((get = getchar()) != 'e'){
    }
    getchar();
    for (int i = 0; ; i++)
    {
        get = getchar();
        if(get == '\n')
            break;
        else if(get == ' '){
            flagv = 1;
            break;
        }
        else 
            fileName[i] = get;
    }
    //printf("---file name:%s---\n" , fileName);
    if(flagv == 1){
        getchar();
        for (int i = 0 ; ; i++)
        {
            get = getchar();
            if(get == '\n')
                break;
            if(get == ' '){
                break;
            }
            else 
                attribute[i] = get;
        }
    }
    FILE *fp;
    char ch;
    int count = 0;
    int pos[30];
    int pointer = 0;
    int loop;
    char word[50] = {'\0'};
    if((fp = fopen(fileName, "r")) == 0){
        printf("file doesn't exist\n");
        return;
    }
    int wordLength[100000];
    int cc = 0;
    int fc[100] = {0};
    do 
    {

        ch = fscanf(fp, "%s", word);
        wordLength[cc] = strlen(word);
        //if(tobefound[0] == '*'){
        //    word[0] = '*';
        //    for (int i = 0; i < count; i++)
        //    {
        //        /* code */
        //    }
        //    
        //}

        for (int i = 0; i < strlen(tobefound); i++)
        {
            if(tobefound[i] == '\\' && tobefound[i+1] =='*'){
                word[i] = '\\';
                word[i+1] = '*';
                //printf("tobefound:%s\n" , tobefound);
                //printf("word:%s\n" , word);
                break;
            }
            else if(tobefound[i] == '*'){
                tobefound[i+1] = '\0';
                word[i] = '*';
                word[i+1] = '\0';
                //printf("--tobefound:%s\n" , tobefound);
                //printf("word:%s\n" , word);
            }
        }
        
        if(strcmp(word, tobefound) == 0)
        {
            pos[count] = pointer; 
            fc[count] = cc;
            //printf("%d\n" , pos[count]);
            count++;
        }
        pointer += wordLength[cc];
        cc++;
        pointer++;
        //printf("%s ",word);       
    } while (ch != EOF);

    fclose(fp);
    char string[1000000] = {'\0'};
    if((!strcmp(attribute , "all"))){
        while ((get = getchar()) != '\n')
        {
            if(get == '-'){
                printf("you cannot use both 'all' and 'at'\n");
                return;
            }
        }
        
        for (int n = 1 ; n <= count ; n++)
        { 
        char get;
        int j = 0;
        fopen(fileName , "r");
        printf("pos: %d\n" , pos[n-1]);
        for (int i = 0; i < pos[n-1] ; i++)
        {
            get = fgetc(fp);
            //printf("1:%c" , get);
            string[j] = get;
            j++;
        } 
        printf("%d - %d" , wordLength[fc[n-1]] , fc[n-1] );
        for (int i = 0; i < wordLength[fc[n-1]]; i++)
        {
            get = fgetc(fp);
            printf("%c" , get);
        }
        printf("\n");
        for (int i = 0 ;  i < strlen(toreplace); i++)
        {
            string[j] = toreplace[i];
            j++;
        }
        for (int i = 0; ; i++)
        {
            get = fgetc(fp);
            if(get == EOF)
                break;
            string[j] = get;
            j++;
        }
        //printf("%s" , string); 
        fclose(fp);
        fopen(fileName , "w");
        for (int i = 0; i < strlen(string) ; i++)
        {
            fputc(string[i] , fp);
        }
        fclose(fp);
    }
    }
    else {
        int n;
        if(!(strcmp(attribute , "at"))){
            scanf("%d" , &n);
            while ((get = getchar()) != '\n')
            {
                if(get == '-'){
                    printf("you cannot use both 'all' and 'at'\n");
                    return;
                }
            }
        
        }
        else if(flagv == 0)
            n = 1;
        //printf("n: %d\n" , n);
        //printf("count: %d\n" , count);
        if(n > count){
            printf("text has not been repeated %d times\n" , n );
            return;
        }
        char get;
        int j = 0;
        printf("pos: %d\n" , pos[n-1]);
        for (int i = 0; i < pos[n-1] ; i++)
        {
            get = fgetc(fp);
            //printf("1:%c" , get);
            string[j] = get;
            j++;
        } 
        printf("%d - %d" , wordLength[fc[n-1]] , fc[n-1] );
        for (int i = 0; i < wordLength[fc[n-1]]; i++)
        {
            get = fgetc(fp);
            printf("%c" , get);
        }
        printf("\n");
        for (int i = 0 ;  i < strlen(toreplace); i++)
        {
            string[j] = toreplace[i];
            j++;
        }
        for (int i = 0; ; i++)
        {
            get = fgetc(fp);
            if(get == EOF)
                break;
            string[j] = get;
            j++;
        }
        //printf("%s" , string); 
        fclose(fp);
        fopen(fileName , "w");
        for (int i = 0; i < strlen(string) ; i++)
        {
            fputc(string[i] , fp);
        }
        fclose(fp);
    }
}
