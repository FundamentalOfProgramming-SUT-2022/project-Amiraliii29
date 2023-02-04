#include <stdio.h>
#include <ncurses.h>
#include <string.h>

void window_layout();
void openfile(WINDOW *);

int main(){

    window_layout();

    return 0;
}

void window_layout(){

    char in;
    initscr();
    char mode[] = "NORMAL";
    char fType = ' ';

    WINDOW *win;
    win = newwin(25 , 70 , 0 , 0);
    refresh();
    box(win , 0 , 0);
    wrefresh(win);
    start_color();
    init_pair(1 , COLOR_BLACK , COLOR_BLUE);

    attron(COLOR_PAIR(1));
    refresh();
    mvwprintw(win , 22 , 1 , "%s" , mode);
    refresh();
    attroff(COLOR_PAIR(1));
    wrefresh(win);

    attron(A_BLINK);
    wrefresh(win);
    attroff(A_BLINK);
    wrefresh(win);

    noecho();
    int x , y;
    x = 3;
    y = 1;
    mvwprintw(win , y , 1 , "1");
    wrefresh(win);
    move(y ,x);
    int yf;
    int xs[100] = {3};
    int get;
    while (1)
    {   
        get = getch();
        if(get == 47 || get == 58){
            char command[100] = {'\0'};
            x = 1;
            while((get = getch()) != KEY_ENTER){
                if(get == KEY_ENTER || get == '\n')
                    break;
                mvwprintw(win , 23 , x , "%c" , get);
                wrefresh(win);
                if(get == ' ')
                    break;
                command[x-1] = get;
                x++;

            }
            //open:
            if(!(strcmp(command , "open"))){
                    get = getch();
                    char slash = '\n';
                    char fileName[100] = {'\0'};
                    int f = 7;
                    for (int i = 0; ; i++)
                    {
                        if(get == (int) slash)
                            break;
                        mvwprintw(win , 23 , f , "%c" , get);
                        f++;
                        wrefresh(win);
                        fileName[i] = get;
                        get = getch();
                    }
                    int x1 = 3;
                    int y1 = 1;
                    char in1;
                    
                    FILE *fp;
                    fp = fopen(fileName , "r");

                    mvwprintw(win , 22 , 15 , "%s" , fileName );
                    mvwprintw(win , 22 , 17 + strlen(fileName) , "+" );
                    wrefresh(win);
                    in1 = fgetc(fp);
                    while (1)
                    {
                        if(in1 == EOF){
                            xs[y1] = x1 + 1;
                            break;
                        }
                        mvwprintw(win , y1 , x1 , "%c" , in1);
                        wrefresh(win);
                        x1++;
                        if(x1 > 68){
                            x1 = 3;
                            y1++;
                        }
                        if(in1 == '\n'){
                            xs[y1] = x1;
                            x1 = 3;
                            y1++;
                            mvwprintw(win , y1 , 1 , "%d" , y1);
                            wrefresh(win);
                        }
                        wrefresh(win);
                        in1 = fgetc(fp);
                    }
                    fclose(fp);
                    getch();
            }
        }

        else if(get == 105){
            char insert;
            attron(COLOR_PAIR(1));
            mvwprintw(win , 22 , 1 , "INSERT");
            refresh();
            attroff(COLOR_PAIR(1));
            refresh();
            insert = getch();
            while(1){
                if(insert == '\\')
                    break;
                mvwprintw(win , y , x , "%c" , insert);
                x++;
                if(x > 68){
                    x = 3;
                    y++;
                }
                move(y , x);
                wrefresh(win);
                insert = getch();
            }
        }


        else if(get == 107){
            if(y > 1){
                y--;
            if(x > xs[y])
                x = xs[y] - 2;
            }
            move(y , x);
        }
        else if(get == 106){
            y++;
            if(x > xs[y])
                x = xs[y] - 2;
            move(y , x);
            
        }
        else if(get == 104){
            if(x > 3){
                x--;
            move(y , x);
            }
        }
        else if(get == 108){
            if(x < xs[y] - 2){
                x++;
            move(y , x);
            }
        }
    }
    getch();
    
    endwin();

}