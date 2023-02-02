#include <stdio.h>
#include <dirent.h>
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
void grep();
void autoindent();
void compare();
void tree(char * , int , int);
void undo();

char clipboard[1000000];
int callcounter = 0;

int main(){

    printf("Welcome to sheikh vim :)\n");
    printf("please type \"exit\" to stop program\n");
    FILE *hidden;
    hidden = fopen(".hidden.txt" , "w");
    fclose(hidden);

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
    else if(!(strcmp(command , "insertstr")))
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
    else if(!(strcmp(command , "grep")))
        grep();
    else if(!(strcmp(command , "auto")))
        autoindent();
    else if(!(strcmp(command , "compare")))
        compare();
    else if(!(strcmp(command , "undo")))
        undo();
    else if(!(strcmp(command , "tree"))){
        tree("." , 0 , 0);
        callcounter = 1;
    }
    }

}

void createfile(){
    char get;
    while((get = getchar()) != 'e'){
    }
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
    if(fp == fopen(fileName , "r")){
        printf("file already exists");
        fclose(fp);
        return;
    }
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

    file = fopen(fileName , "r");
    FILE *hidden;
    hidden = fopen(".hidden.txt" , "w");
    char c;
    while((c = fgetc(file)) != EOF){
        fputc(c , hidden);
    }
    fclose(file);
    fclose(hidden);
    
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

        file = fopen(fileName , "r");
        FILE *hidden;
        hidden = fopen(".hidden.txt" , "w");
        char c;
        while((c = fgetc(file)) != EOF){
            fputc(c , hidden);
        }
        fclose(file);
        fclose(hidden);

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


        file = fopen(fileName , "r");
        FILE *hidden;
        hidden = fopen(".hidden.txt" , "w");
        char c;
        while((c = fgetc(file)) != EOF){
            fputc(c , hidden);
        }
        fclose(file);
        fclose(hidden);

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

        file = fopen(fileName , "r");
        FILE *hidden;
        hidden = fopen(".hidden.txt" , "w");
        char c;
        while((c = fgetc(file)) != EOF){
            fputc(c , hidden);
        }
        fclose(file);
        fclose(hidden);

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

        file = fopen(fileName , "r");
        FILE *hidden;
        hidden = fopen(".hidden.txt" , "w");
        char c;
        while((c = fgetc(file)) != EOF){
            fputc(c , hidden);
        }
        fclose(file);
        fclose(hidden);

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

    file = fopen(fileName , "r");
    FILE *hidden;
    hidden = fopen(".hidden.txt" , "w");
    char c;
    while((c = fgetc(file)) != EOF){
        fputc(c , hidden);
    }
    fclose(file);
    fclose(hidden);

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
    int qoutflag = 0;
    int wordnum = 0;
    while((get = getchar()) != 'r'){
    }
    int wordnumber;
    get = getchar();
    if( get == '\"'){
        int breakflag = 0; 
        qoutflag = 1;
        for (wordnumber = 0 ; ; )
        {
            for (int j = 0; ; j++)
            {
                get = getchar();
                if(get == ' '){
                    wordnumber++;
                    break;
                }
                else if(get == '\"'){
                    wordnumber++;
                    breakflag = 1;
                    break;
                }
                //printf("%c" , get);
                tobefounds[wordnumber][j] = get;
            }
            if(breakflag == 1)
                break; 
        }  
        //printf("%d" , wordnum); 
    }
    else {
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
            if(get == '\n' || get == ' ')
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
    /// with qoutation:
    if(qoutflag == 1){
        int posMemory[300] = {0};
        int n;
        int textRepeatitionCounter[100] = {0};
        int atFlag = 0;
        int allFlag = 0;
        int wordlength2[100] ={0};
        int posMemoryWord[100] = {0};
        int fc = 0;
        if(!(strcmp(attribute , "at"))){
            scanf("%d" , &n);
            atFlag = 1;
        }
        else if(!(strcmp(attribute , "count")) )
            n = -1;
        else if(!(strcmp(attribute , "all"))){
            n = -1;
            allFlag = 1;
        }
        else 
            n = 1;
        //printf("wordnum: %d\n" , wordnumber);
        for (int wc = 0 ; wc < wordnumber; wc++)
        {
            posMemory[wc] = -100;
            int foundedNum = 0;
            int pointer = 0;
            fclose(fp);
            fp = fopen(fileName , "r");
            int fj = 0;
            for ( fj = 0; fj < strlen(tobefounds[wc]); fj++)
            {
                tobefound[fj] = tobefounds[wc][fj];
            }
            tobefound[fj] = '\0';
            //printf("tobefound:%s\n" , tobefound);
            int wordlength[100] = {0};
            int cc = 0;
            do 
            {
                char word[50] = {'\0'};
                ch = fscanf(fp, "%s", word);
                wordlength[cc] = strlen(word);
                int fl = 0;
                if(tobefound[0] == '*'){
                    int m ;
                    //printf("to be found: %s\n" , tobefound);
                    for (int j = 0; j < wordlength[cc]; j++)
                    {
                        if(word[j] == tobefound[1] && word[j+1] == tobefound[2]){
                            m = j;
                            fl = 1;
                        }
                    }
                    if(fl == 0){
                        pointer += wordlength[cc];
                        cc++;
                        pointer++;
                        continue;
                    }
                    int mf = 1;
                    word[0] = '*';
                    for (int k =  m ; k < wordlength[cc]; k++)
                    {
                        word[mf] = word[k];
                        mf++;
                    }
                    word[mf] = '\0';
                    //printf("word: %s\n" , word);
                }
                else{
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
                }
                //printf("--tobefound:%s\n" , tobefound);
                //printf("word:%s\n" , word);
                
                if(strcmp(word, tobefound) == 0)
                {
                    foundedNum++;
                    posMemory[wc] = pointer;
                    posMemoryWord[wc] = cc;
                    wordlength2[fc] = wordlength[cc];
                    fc++;
                    if(foundedNum == n){
                        break;
                    }
                }
                pointer += wordlength[cc];
                pointer++;
                cc++;
                //printf("%s ",word);       
            } while (ch != EOF);
            //printf("%d - %d\n" , pos[wc] , wc);
            textRepeatitionCounter[wc] = foundedNum;
            if(foundedNum < n){
                printf("text has not been repeated %d times" , n);
                return;
            }
        }
        if(flagv == 0 || atFlag == 1){
            for (int i = 1 ; i < wordnumber; i++)
            {
                //printf("%d %d" , posMemory[i] , posMemory[i-1]);
                if(posMemory[i] != (posMemory[i-1] + wordlength2[i-1]) +1 ){
                    printf("text not found in file\n");
                    return;
                }
            }

            printf("text starts from character number: %d\n" , posMemory[0] + 1);
        }
        else if (!(strcmp(attribute , "byword")))
        {
            for (int i = 1 ; i < wordnumber; i++)
            {
                //printf("%d %d" , posMemoryWord[i] , posMemoryWord[i-1]);
                if(posMemoryWord[i] != (posMemoryWord[i-1] + 1)  ){
                    printf("text not found in file\n");
                    return;
                }
            }

            printf("text starts from word number: %d\n" , posMemoryWord[0] + 1);
        }
        else if(!(strcmp(attribute , "count"))){
            int min = 10000000;
            for (int i = 0; i < wordnumber; i++)
            {
                if(textRepeatitionCounter[i] < min)
                    min = textRepeatitionCounter[i];
            }
            printf("text has been repeated %d times\n", min);
        }
        else if(allFlag == 1){
            int min = 10000000;
            int posMemory[100] = {0};
            for (int i = 0; i < wordnumber; i++)
            {
                if(textRepeatitionCounter[i] < min)
                    min = textRepeatitionCounter[i];
            }
            //printf("min: %d\n" , min);
            for (int n = 1 ; n <= min ; n++)
            {
                int textRepeatitionCounter[100] = {0};
                int wordlength2[100] = {0};
                for (int wc = 0 ; wc < wordnumber; wc++)
                {
                    posMemory[wc] = -100;
                    int foundedNum = 0;
                    int pointer = 0;
                    fclose(fp);
                    fp = fopen(fileName , "r");
                    int fj = 0;
                    for ( fj = 0; fj < strlen(tobefounds[wc]); fj++)
                    {
                        tobefound[fj] = tobefounds[wc][fj];
                    }
                    tobefound[fj] = '\0';
                    //printf("tobefound:%s\n" , tobefound);
                    int wordlength[100] = {0};
                    int cc = 0;
                    do 
                    {
                        char word[50] = {'\0'};
                        ch = fscanf(fp, "%s", word);
                        wordlength[cc] = strlen(word);
                        int fl = 0;
                        if(tobefound[0] == '*'){
                            int m ;
                            //printf("to be found: %s\n" , tobefound);
                            for (int j = 0; j < wordlength[cc]; j++)
                            {
                                if(word[j] == tobefound[1] && word[j+1] == tobefound[2]){
                                    m = j;
                                    fl = 1;
                                }
                            }
                            if(fl == 0){
                                pointer += wordlength[cc];
                                cc++;
                                pointer++;
                                continue;
                            }
                            int mf = 1;
                            word[0] = '*';
                            for (int k =  m ; k < wordlength[cc]; k++)
                            {
                                word[mf] = word[k];
                                mf++;
                            }
                            word[mf] = '\0';
                            //printf("word: %s\n" , word);
                        }
                        else{
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
                        }
                        //printf("--tobefound:%s\n" , tobefound);
                        //printf("word:%s\n" , word);
                        
                        if(strcmp(word, tobefound) == 0)
                        {
                            foundedNum++;
                            posMemory[wc] = pointer;
                            posMemoryWord[wc] = cc;
                            wordlength2[wc] = wordlength[cc];
                            fc++;
                            if(foundedNum == n){
                                break;
                            }
                        }
                        pointer += wordlength[cc];
                        pointer++;
                        cc++;
                        //printf("%s ",word);       
                    } while (ch != EOF);
                    //printf("%d - %d\n" , posMemory[wc] , wc);
                    textRepeatitionCounter[wc] = foundedNum;
                    if(foundedNum < n){
                        printf("text has not been repeated %d times" , n);
                        return;
                    }

                }
                    for (int i = 1 ; i < wordnumber; i++)
                    {
                        //printf("%d %d\n" , posMemory[i] , posMemory[i-1]);
                        //printf("wordlength: %d\n" , wordlength2[i-1]);
                        if(posMemory[i] != (posMemory[i-1] + wordlength2[i-1]) +1 ){
                            printf("text not found in file\n");
                            return;
                        }
                    }

                    printf("text starts from character number: %d\n" , posMemory[0] + 1);
                
            }
            
        }

        fclose(fp);
    }
    else {
    int wordLength[100000];
    int cc = 0;
    int fc[100] = {0};
    do 
    {
        char word[50] = {'\0'};
        ch = fscanf(fp, "%s", word);
        wordLength[cc] = strlen(word);
        if(tobefound[0] == '*'){
            int m ;
            int fl = 0 ;
            //printf("to be found: %s\n" , tobefound);
            for (int j = 0; j < strlen(word); j++)
            {
                if(word[j] == tobefound[1] && word[j+1] == tobefound[2]){
                    m = j;
                    fl = 1;
                }
            }
            if(fl == 0){
                pointer += wordLength[cc];
                cc++;
                pointer++;
                continue;
            }
            int mf = 1;
            word[0] = '*';
            for (int k =  m ; k < strlen(word); k++)
            {
                word[mf] = word[k];
                mf++;
            }
            word[mf] = '\0';
            //printf("word: %s\n" , word);
        }

        else{
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
        }
        //printf("tobefound:%s\n" , tobefound);
        //printf("word:%s\n" , word);
        if(strcmp(word, tobefound) == 0)
        {
            posw[count] = cc;
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

    if(flagv == 0){
        if(count == 0)  
            printf("-1\n");
        else
            {
            printf("'%s' starts from character number: ", tobefound);
            printf("%d\n", pos[0] + 1);

            }
    }
    else if(!(strcmp(attribute , "count"))){
        printf("this text has been repeated %d times\n" , count);
    }
    else if(!(strcmp(attribute , "at"))){
        int n;
        scanf("%d" , &n);
        printf("n: %d\n" , n);
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
}

void replacestr(){
    char get;
    int flagv = 0;
    int qoutflag = 0 , qoutflag2 = 0;
    char attribute[100] = {'\0'};
    char fileName[200] = {'\0'};
    char tobefound[1000] = {'\0'};
    char toreplace[1000] = {'\0'};
    char tobefounds[20][300] = {'\0'};
    char toreplaces[20][300] = {'\0'};
    int wordnumFO , wordnumRE;
    while((get = getchar()) != '1'){
    }
    get = getchar();
    if( get == '\"'){
        int breakflag = 0;
        qoutflag = 1;
        for (wordnumFO = 0 ; ; )
        {
            for (int j = 0; ; j++)
            {
                get = getchar();
                if(get == ' '){
                    wordnumFO++;
                    break;
                }
                else if(get == '\"'){
                    wordnumFO++;
                    breakflag = 1;
                    break;
                }
                tobefounds[wordnumFO][j] = get;
            }
            if(breakflag == 1)
                break; 
        } 
        //printf("wordnumFO: %d\n" , wordnumFO);
    }
    
    else {
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
    //str  2
    while((get = getchar()) != '2'){
    }
    get = getchar();
    if( get == '\"'){
        int breakflag = 0;
        qoutflag2 = 1;
        for (wordnumRE = 0; ; )
        {
            for (int j = 0; ; j++)
            {
                get = getchar();
                if(get == ' '){
                    wordnumRE++;
                    break;
                }
                else if(get == '\"'){
                    breakflag = 1;
                    wordnumRE++;
                    break;
                }
                toreplaces[wordnumRE][j] = get;
            }
            if(breakflag == 1)
                break; 
        }  
    }
    else {
        get = getchar();
        for (int i = 0; ; i++)
        {
            if(get == ' ' || get =='-')
                break;
            else
                toreplace[i] = get;
            get = getchar();
        }
    
        //printf("---string:%s---\n" , toreplace);
    }
    //filename:
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
    int n;
    int pointer = 0;
    int atFlag = 0;
    int allFlag = 0;
    int loop;
    char word[50] = {'\0'};
    if((fp = fopen(fileName, "r")) == 0){
        printf("file doesn't exist\n");
        return;
    }
    int wordLength[100000];
    int cc = 0;
    int fc[100] = {0};

    /// with qoutation:
    if(qoutflag == 1){
        int posMemory[300] = {0};
        int wordlength2[100] ={0};
        int wordlength[100] = {0};

        if(!(strcmp(attribute , "at"))){
            atFlag = 1;
            scanf("%d" , &n);
        }
        else if(!(strcmp(attribute , "all")))
            allFlag = 1;
        else 
            n = 1;
        int fc = 0;
        //printf("wordnum: %d\n" , wordnumber);
        if(allFlag == 0){
        int wordlength3[100] = {0};
        for (int wc = 0 ; wc < wordnumFO ; wc++)
        {
            posMemory[wc] = -100;
            int foundedNum = 0;
            int pointer = 0;
            fclose(fp);
            fp = fopen(fileName , "r");
            int fj = 0;
            for ( fj = 0; fj < strlen(tobefounds[wc]); fj++)
            {
                tobefound[fj] = tobefounds[wc][fj];
            }
            tobefound[fj] = '\0';
            //printf("tobefound:%s\n" , tobefound);
            do 
            {
                char word[50] = {'\0'};
                ch = fscanf(fp, "%s", word);
                wordlength[cc] = strlen(word);
                int fl = 0;
                if(tobefound[0] == '*'){
                    int m ;
                    //printf("to be found: %s\n" , tobefound);
                    for (int j = 0; j < wordlength[cc]; j++)
                    {
                        if(word[j] == tobefound[1] && word[j+1] == tobefound[2]){
                            m = j;
                            fl = 1;
                        }
                    }
                    if(fl == 0){
                        pointer += wordlength[cc];
                        cc++;
                        pointer++;
                        continue;
                    }
                    int mf = 1;
                    word[0] = '*';
                    for (int k =  m ; k < wordlength[cc]; k++)
                    {
                        word[mf] = word[k];
                        mf++;
                    }
                    word[mf] = '\0';
                    //printf("word: %s\n" , word);
                }
                else{
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
                }
                //printf("--tobefound:%s\n" , tobefound);
                //printf("word:%s\n" , word);
                
                if(strcmp(word, tobefound) == 0)
                {
                    foundedNum++;
                    posMemory[wc] = pointer;
                    wordlength2[fc] = wordlength[cc];
                    wordlength3[wc] = wordlength[cc];
                    fc++;
                    if(foundedNum == n){
                        break;
                    }
                }
                pointer += wordlength[cc];
                pointer++;
                cc++;
                //printf("%s ",word);       
            } while (ch != EOF);
        }

        for (int i = 1 ; i < wordnumFO; i++)
        {
            //printf("%d %d" , posMemory[i] , posMemory[i-1]);
            if(posMemory[i] != (posMemory[i-1] + wordlength2[i-1]) +1 ){
                printf("text not found in file\n");
                return;
            }
        }
        fclose(fp);
        char string[200000] = {'\0'};
        fp = fopen(fileName , "r");
        int ff = 0;
        for (int i = 0; i < posMemory[0] ; i++)
        {
            get = fgetc(fp);
            string[ff] =  get;
            ff++;
        }
        for (int i = 0; i < wordnumFO; i++)
        {
            for (int  j = 0;  j < wordlength3[i] ; j++)
            {
                get = fgetc(fp);
            }
            get = fgetc(fp);
        }
        if(qoutflag2 == 0){
            for (int i = 0; i < strlen(toreplace) ; i++)
            {
                string[ff] = toreplace[i];
                ff++;
            }
        }
        else{
            for (int i = 0; i < wordnumRE ; i++)
            {
                for (int j = 0; j < strlen(toreplaces[i]); j++)
                {
                    string[ff] = toreplaces[i][j];
                    ff++;
                }
                string[ff] = ' ';
                ff++;
            }
        }
        while ((get = fgetc(fp)) != EOF)
        {
            string[ff] = get;
            ff++;
        }
        fclose(fp);

        fp = fopen(fileName , "r");
        FILE *hidden;
        hidden = fopen(".hidden.txt" , "w");
        char c;
        while((c = fgetc(fp)) != EOF){
            fputc(c , hidden);
        }
        fclose(fp);
        fclose(hidden);

        fp = fopen(fileName , "w");
        for (int i = 0; i < strlen(string) ; i++)
        {
            fputc(string[i] , fp);
        }
        
        fclose(fp);
        }
        // all attribute with qoutation
        else{
            int textRepeatitionCounter[100] = {0};
            for (int wc = 0 ; wc < wordnumFO; wc++)
            {
                posMemory[wc] = -100;
                int foundedNum = 0;
                int pointer = 0;
                fclose(fp);
                fp = fopen(fileName , "r");
                int fj = 0;
                for ( fj = 0; fj < strlen(tobefounds[wc]); fj++)
                {
                    tobefound[fj] = tobefounds[wc][fj];
                }
                tobefound[fj] = '\0';
                //printf("tobefound:%s\n" , tobefound);
                int wordlength[100] = {0};
                int cc = 0;
                do 
                {
                    char word[50] = {'\0'};
                    ch = fscanf(fp, "%s", word);
                    wordlength[cc] = strlen(word);
                    int fl = 0;
                    if(tobefound[0] == '*'){
                        int m ;
                        //printf("to be found: %s\n" , tobefound);
                        for (int j = 0; j < wordlength[cc]; j++)
                        {
                            if(word[j] == tobefound[1] && word[j+1] == tobefound[2]){
                                m = j;
                                fl = 1;
                            }
                        }
                        if(fl == 0){
                            pointer += wordlength[cc];
                            cc++;
                            pointer++;
                            continue;
                        }
                        int mf = 1;
                        word[0] = '*';
                        for (int k =  m ; k < wordlength[cc]; k++)
                        {
                            word[mf] = word[k];
                            mf++;
                        }
                        word[mf] = '\0';
                        //printf("word: %s\n" , word);
                    }
                    else{
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
                    }
                    //printf("--tobefound:%s\n" , tobefound);
                    //printf("word:%s\n" , word);
                    
                    if(strcmp(word, tobefound) == 0)
                    {
                        foundedNum++;
                        posMemory[wc] = pointer;
                        wordlength2[fc] = wordlength[cc];
                        fc++;
                        if(foundedNum == n){
                            break;
                        }
                    }
                    pointer += wordlength[cc];
                    pointer++;
                    cc++;
                    //printf("%s ",word);       
                } while (ch != EOF);
                //printf("%d - %d\n" , pos[wc] , wc);
                textRepeatitionCounter[wc] = foundedNum;
                if(foundedNum < n){
                    printf("text has not been repeated %d times" , n);
                    return;
                }
            }
            int min = 10000000;
            for (int i = 0; i < wordnumFO; i++)
            {
                if(textRepeatitionCounter[i] < min)
                    min = textRepeatitionCounter[i];
            }
            for (int n = 1; n <= min ; n++)
            {
            for (int wc = 0 ; wc < wordnumFO ; wc++)
            {
                int cc = 0;
                posMemory[wc] = -100;
                int foundedNum = 0;
                int pointer = 0;
                fclose(fp);
                fp = fopen(fileName , "r");
                int fj = 0;
                for ( fj = 0; fj < strlen(tobefounds[wc]); fj++)
                {
                    tobefound[fj] = tobefounds[wc][fj];
                }
                tobefound[fj] = '\0';
                //printf("tobefound:%s\n" , tobefound);
                do 
                {
                    char word[50] = {'\0'};
                    ch = fscanf(fp, "%s", word);
                    wordlength[cc] = strlen(word);
                    int fl = 0;
                    if(tobefound[0] == '*'){
                        int m ;
                        //printf("to be found: %s\n" , tobefound);
                        for (int j = 0; j < wordlength[cc]; j++)
                        {
                            if(word[j] == tobefound[1] && word[j+1] == tobefound[2]){
                                m = j;
                                fl = 1;
                            }
                        }
                        if(fl == 0){
                            pointer += wordlength[cc];
                            cc++;
                            pointer++;
                            continue;
                        }
                        int mf = 1;
                        word[0] = '*';
                        for (int k =  m ; k < wordlength[cc]; k++)
                        {
                            word[mf] = word[k];
                            mf++;
                        }
                        word[mf] = '\0';
                        //printf("word: %s\n" , word);
                    }
                    else{
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
                    }
                    //printf("--tobefound:%s\n" , tobefound);
                    //printf("word:%s\n" , word);
                    
                    if(strcmp(word, tobefound) == 0)
                    {
                        foundedNum++;
                        posMemory[wc] = pointer;
                        wordlength2[wc] = wordlength[cc];
                        if(foundedNum == n){
                            break;
                        }
                    }
                    pointer += wordlength[cc];
                    pointer++;
                    cc++;
                    //printf("%s ",word);       
                } while (ch != EOF);
            }

            for (int i = 1 ; i < wordnumFO; i++)
            {
                //printf("%d %d" , posMemory[i] , posMemory[i-1]);
                if(posMemory[i] != (posMemory[i-1] + wordlength2[i-1]) +1 ){
                    printf("text not found in file\n");
                    return;
                }
            }
            fclose(fp);
            char string[200000] = {'\0'};
            fp = fopen(fileName , "r");
            int ff = 0;
            for (int i = 0; i < posMemory[0] ; i++)
            {
                get = fgetc(fp);
                string[ff] =  get;
                ff++;
            }
            for (int i = 0; i < wordnumFO; i++)
            {
                for (int  j = 0;  j < wordlength2[i]; j++)
                {
                    get = fgetc(fp);
                }
                if(i != wordnumFO - 1)
                    get = fgetc(fp);
            }
            if(qoutflag2 == 0){
                for (int i = 0; i < strlen(toreplace) ; i++)
                {
                    string[ff] = toreplace[i];
                    ff++;
                }
            }
            else{
                for (int i = 0; i < wordnumRE ; i++)
                {
                    for (int j = 0; j < strlen(toreplaces[i]); j++)
                    {
                        string[ff] = toreplaces[i][j];
                        ff++;
                    }
                    if(i != wordnumRE - 1){
                    string[ff] = ' ';
                    ff++;
                    }
                }
            }
            while ((get = fgetc(fp)) != EOF)
            {
                string[ff] = get;
                ff++;
            }
            fclose(fp);

            fp = fopen(fileName , "r");
            FILE *hidden;
            hidden = fopen(".hidden.txt" , "w");
            char c;
            while((c = fgetc(fp)) != EOF){
                fputc(c , hidden);
            }
            fclose(fp);
            fclose(hidden);

            fp = fopen(fileName , "w");
            for (int i = 0; i < strlen(string) ; i++)
            {
                fputc(string[i] , fp);
            }
            
            fclose(fp);
                
            }
            


        }
    }

    else {
    do 
    {

        ch = fscanf(fp, "%s", word);
        wordLength[cc] = strlen(word);
        if(tobefound[0] == '*'){
            int m ;
            int fl = 0 ;
            //printf("to be found: %s\n" , tobefound);
            for (int j = 0; j < strlen(word); j++)
            {
                if(word[j] == tobefound[1] && word[j+1] == tobefound[2]){
                    m = j;
                    fl = 1;
                }
            }
            if(fl == 0){
                pointer += wordLength[cc];
                cc++;
                pointer++;
                continue;
            }
            int mf = 1;
            word[0] = '*';
            for (int k =  m ; k < strlen(word); k++)
            {
                word[mf] = word[k];
                mf++;
            }
            word[mf] = '\0';
            //printf("word: %s\n" , word);
        }

        else{
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
        }
        //printf("tobefound:%s\n" , tobefound);
        //printf("word:%s\n" , word);
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
        
        for (int f = 1 ; f <= count ; f++)
        { 
        char get;
        int j = 0;
        char string[1000000] = {'\0'};
        fp = fopen(fileName , "r");
        //printf("pos: %d\n" , pos[f-1]);
        for (int i = 0; i < pos[f-1] - ((wordLength[fc[f-1]] - strlen(toreplace)) * (f-1)); i++)
        {
            get = fgetc(fp);
            //printf("1:%c" , get);
            string[j] = get;
            j++;
        } 
        //printf("%d - %d" , wordLength[fc[f-1]] , fc[f-1] );
        for (int i = 0; i < wordLength[fc[f-1]]; i++)
        {
            get = fgetc(fp);
            //printf("%c" , get);
        }
        //printf("\n");
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

        fp = fopen(fileName , "r");
        FILE *hidden;
        hidden = fopen(".hidden.txt" , "w");
        char c;
        while((c = fgetc(fp)) != EOF){
            fputc(c , hidden);
        }
        fclose(fp);
        fclose(hidden);

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
        fp = fopen(fileName , "r");
        int j = 0;
        //printf("pos: %d\n" , pos[n-1]);
        for (int i = 0; i < pos[n-1] ; i++)
        {
            get = fgetc(fp);
            //printf("1:%c" , get);
            string[j] = get;
            j++;
        } 
        //printf("%d - %d" , wordLength[fc[n-1]] , fc[n-1] );
        for (int i = 0; i < wordLength[fc[n-1]]; i++)
        {
            get = fgetc(fp);
            //printf("%c" , get);
        }
        //printf("\n");
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

        fp = fopen(fileName , "r");
        FILE *hidden;
        hidden = fopen(".hidden.txt" , "w");
        char c;
        while((c = fgetc(fp)) != EOF){
            fputc(c , hidden);
        }
        fclose(fp);
        fclose(hidden);

        fopen(fileName , "w"); 
        for (int i = 0; i < strlen(string) ; i++)
        {
            fputc(string[i] , fp);
        }
        fclose(fp);
    }
    }
    printf("text replaced successfully\n");
}

void grep(){
    char get;
    char fileName[200] = {'\0'};
    char pattern[1000] = {'\0'};
    int cop = 0;
    int lop = 0;
    int endflag = 0 ;
    int copCounter = 0;
    while((get = getchar()) != '-'){
    }
    get = getchar();
    if(get == 'c')
        cop = 1;
    else if(get == 'l')
        lop = 1;
    while((get = getchar()) != '\"'){
    }
    for(int i  = 0; ; i++){
        get = getchar();
        if(get == '\"')
            break;
        pattern[i] = get;
    }
    //printf("---pattern:%s\n" , pattern);
    while((get = getchar()) != 's'){
    }
    getchar();
    while(1){
            get = getchar();
        for (int i = 0; ; i++)
        {
            if(get == ' ')
                break;
            else if(get == '\n'){
                endflag = 1;
                break;
            }
            fileName[i] = get;
            get = getchar();
        }
        //printf("\n---file name:%s\n" , fileName);
        FILE *fp;
        char temp[10000] = {'\0'};
        fp = fopen(fileName,"r");
        while(!feof(fp))
        {
            fgets(temp,1000,fp);
            if(strstr(temp,pattern)!= NULL){
                if(cop == 1)
                    copCounter++;
                else if(lop == 1)
                    printf("%s\n" , fileName);
                else
                    printf("%s: %s",fileName ,temp);
            }
        }
        fclose(fp);
        if(endflag == 1){
            if(cop == 1)
                printf("%d\n" , copCounter);
            return;
        }
    }
}

void autoindent(){
    char get ;
    int flag = 0;
    char fileName[100] = {'\0'};
    char string[100000] = {'\0'};
    while ((get = getchar()) != '/')
    {
    }
    for (int i = 0; ; i++)
    {
        get = getchar();
        if(get == '\n')
            break;
            fileName[i] = get;
    }
    //printf("%s" , fileName);
    FILE *fp;
    fp = fopen(fileName , "r");

    for (int i = 0; ; i++)
    {
        get = fgetc(fp);
       //printf("1:%c" , get);
       if(string[i-1] == '\n' && get != '}'){
        for (int j = 0; j < flag * 4; j++)
        {
            string[i] = ' ';
            i++;
        }
       }
        if(get == EOF) 
            break;
        else if(get == '{'){
            flag++;
            //printf("{ detected\n");
            if(i > 0 && string[i-1] != ' ' && string[i-1] != '\n'){
                string[i] = ' '; i++;
            }
            string[i] = '{'; i++;
            string[i] = '\n'; //i++;
            //string[i] = ' '; i++;
            //string[i] = ' '; i++;
            //string[i] = ' '; i++;
            //string[i] = ' ';
            //printf("2:%s\n" , string);
        }
        else if(get == '}'){
            flag--;
            //printf("} detected\n");
            if(string[i-1] == '\n'){
            }
            else if( string[i-1] == ' ' && string[i-2] == ' ' && string[i-3] == ' ' && string[i-4] == ' '){
                if(flag == 0){
                    string[i-1] = '\0';
                    string[i-2] = '\0';
                    string[i-3] = '\0';
                    string[i-4] = '\0';
                    i -= 4;
                }
            }
            else{
                string[i] = '\n'; i++;
            }
            for (int j = 0; j < flag * 4; j++)
            {
                string[i] = ' ';
                i++;
            }
            string[i] = '}'; i++;
            string[i] = '\n';
            //printf("3:%s" , string);
        }
        else{
        if(get == ' ' &&  string[i-1] == ' ' && string[i-2] == ' ' && string[i-3] == ' ' && string[i-4] == ' '){
            i--;
        }
        else
            string[i] = get;
        }
    }
    fclose(fp);

    fp = fopen(fileName , "r");
    FILE *hidden;
    hidden = fopen(".hidden.txt" , "w");
    char c;
    while((c = fgetc(fp)) != EOF){
        fputc(c , hidden);
    }
    fclose(fp);
    fclose(hidden);

    fp = fopen(fileName , "w");

    for (int i = 0; i < strlen(string); i++)
    {
        fputc(string[i] , fp);
    }
    fclose(fp);
}

void compare(){
    char get;
    char fileName_1[100] = {'\0'};
    char fileName_2[100] = {'\0'};
    int line_counter = 0 , flag1 = 1 , flag2 = 1;
    for (int i = 0; ; i++)
    {
        get = getchar();
        if(get == ' ')
            break;
        fileName_1[i] = get;
    }
    for (int i = 0; ; i++)
    {
        get = getchar();
        if(get == '\n')
            break;
        fileName_2[i] = get;
    }
    printf("%s -- %s\n" , fileName_1 , fileName_2);
    
    FILE *file_1 , *file_2;
    file_1 = fopen(fileName_1 , "r");
    file_2 = fopen(fileName_2 , "r");
    while (1)
    {
        char line_1[200] = {'\0'};
        char line_2[200] = {'\0'};
        fscanf(file_1 , "%[^\n]%*c" , line_1);
        fscanf(file_2 , "%[^\n]%*c" , line_2);
        if(strlen(line_1) == 0)
            flag1 = 0;
        if(strlen(line_2) == 0)
            flag2 = 0;
        if(flag1 == 0 || flag2 == 0)
            break;
        line_counter++;
        
        if(strcmp(line_1 , line_2) != 0){
            printf("============#%d============\n" , line_counter);
            printf("%s\n" , line_1);
            printf("%s\n" , line_2);
        }
    }

    if(flag1 == 1){
        int same = line_counter;
        line_counter++;
        printf("<<<<<<<<<<<< #%d" , line_counter);
        char line_1[200] = {'\0'};

        for (int i = 0; ; i++)
        {
            fscanf(file_1 , "%[^\n]%*c" , line_1);
            if(strlen(line_1) == 0){
                printf(" - #%d <<<<<<<<<<<<\n" , line_counter);
                break;
            }
            line_counter++;
        }
        fclose(file_1);
        file_1 = fopen(fileName_1 , "r");
        for (int i = 0; i < same; i++)
        {
            fscanf(file_1 , "%[^\n]%*c" , line_1);
        }
        while((get = fgetc(file_1)) != EOF){
            printf("%c" , get);
        }
        fclose(file_1);
    }
    else if(flag2 == 1){
        int same = line_counter;
        line_counter++;
        printf(">>>>>>>>>>>> #%d" , line_counter);
        char line_2[200] = {'\0'};

        for (int i = 0; ; i++)
        {
            fscanf(file_2 , "%[^\n]%*c" , line_2);
            if(strlen(line_2) == 0){
                printf(" - #%d >>>>>>>>>>>>\n" , line_counter);
                break;
            }
            line_counter++;
        }
        fclose(file_2);
        file_2 = fopen(fileName_2 , "r");
        for (int i = 0; i < same; i++)
        {
            fscanf(file_2 , "%[^\n]%*c" , line_2);
        }
        while((get = fgetc(file_2)) != EOF){
            printf("%c" , get);
        }
        fclose(file_2);
    }
    
    else{
        fclose(file_1);
        fclose(file_2);
    }
}

int Fdepth;

void tree(char *basePath, int root , int treeDepthCounter)
{
    if(treeDepthCounter == 0){
        scanf("%d" , &Fdepth);
        if(Fdepth < -1){
            printf("Invalid depth\n");
            return;
        }
    }
    if(treeDepthCounter  == Fdepth  && Fdepth != -1)
        return;
    int i;
    char path[1000];
    struct dirent *dp;
    DIR *dir = opendir(basePath);

    if (!dir){
        return;
    }

    while ((dp = readdir(dir)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
        {
            for (i=0; i<root; i++) 
            {
                if (i%2 == 0 || i == 0)
                    printf("%c", '|');
                else
                    printf(" ");

            }

            printf("%c%c%s\n", '|' , '_', dp->d_name);

            strcpy(path, basePath);
            strcat(path, "/");
            strcat(path, dp->d_name);
            tree(path, root + 2 , treeDepthCounter + 1);
        }
    }

    closedir(dir);
}


void undo(){
    char get;
    char fileName[100] = {'\0'};

    while ((get = getchar()) != 'e')
    {
    }
    getchar();

    for (int i = 0; ; i++)
    {
        get = getchar();
        if(get == '\n')
            break;
        fileName[i] = get;
    }
    
    FILE *hidden , *fp;
    hidden = fopen(".hidden.txt" , "r");
    if(!(fp = fopen(fileName , "w"))){
        printf("file doesn't exist\n");
        return;
    }
    if((get = fgetc(hidden)) == EOF){
        printf("There is no action to undo\n");
        return;
    }
    while (1)
    {
        if(get == EOF)
            break;
        fputc(get , fp);
        get = fgetc(hidden);
    }
    fclose(fp);
    fclose(hidden);
    printf("Undoed successfully\n");
}