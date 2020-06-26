#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include <windows.h>
#include <dos.h>

int board[10] = {2,2,2,2,2,2,2,2,2,2};
int turn = 1,flag = 0;
int player,comp;

void menu();
void go(int n);
void start_game();
void draw_board();
void player_first();
void token_input(char ch,int pos);
COORD coord= {0,0};

void spacing(int x,int y)
{
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

void main()
{
    system("cls");
    system("color 70");
    printf("\n\t\t\t\t\t\tWelcome to the Arcade!!");
    printf("\n\t\t\t\t\t\t1.Tic-Tac-Toe\n\t\t\t\t\t\t2.New games coming soon\n\t\t\t\t\t\tChoose a game: ");
    int game;
    scanf("%d", &game);
    if(game==1)
        menu();
    else
    {
        printf("\t\t\t\t\t\tStay tuned for more games!");
        exit(0);
    }
    getch();

}

void menu()
{
    char choice;
    system("cls");
    printf("\nLet's play Tic Tac Toe!");
    printf("\nChoose your token(X/O): ");
    scanf("%c",&choice);
    turn = 1;
    switch (choice)
    {
    case 'X':
        Beep(500, 300);
        player = 1;
        comp = 0;
        player_first();
        break;
    case 'O':
        Beep(500, 300);
        player = 0;
        comp = 1;
        start_game();
        break;
    default:
        Beep(750, 300);
        menu();
    }
}
void player_first()
{
    int pos;

    if(turn > 9)
    {
        spacing(30,20);
        printf("Game Draw!");
        Beep(500, 50);
        Beep(500, 100);
            getch();
            exit(0);
    }
    draw_board();
    spacing(30,18);
    printf("Play your move: ");
    scanf("%d",&pos);
    if(board[pos] != 2)
        player_first();

    if(pos == posswin(player))
    {
        go(pos);
        draw_board();
        spacing(30,20);
        system("color 72");
        printf("You Won! Well played!");
        Beep(2000, 100);
            getch();
            exit(0);
    }

    go(pos);
    draw_board();
    start_game();
}

void start_game()
{
// p==1 then X   p==0  then  O
    if(posswin(comp))
    {
        go(posswin(comp));
        flag = 1;
    }
    else if(posswin(player))
        go(posswin(player));
    else if(make2())
        go(make2());
    else
        go(make4());
    draw_board();

    if(flag)
    {
        spacing(30,20);
        //textcolor(128+RED);
        printf("Computer Won! Better luck next time!");
        system("color 74");
        Beep(200, 100);
        Beep(200, 100);
            getch();
            exit(0);
    }
    else
        player_first();
}

void draw_board()
{
    int j;
    spacing(28,8);
    printf("----------------------");
    for(j=9; j<17; j++)
    {
        spacing(28,j);
        printf("|      |");
        spacing(42,j);
        printf("|      |");
    }
    spacing(28,11);
    printf("----------------------");
    spacing(28,14);
    printf("----------------------");
    spacing(28,17);
    printf("----------------------");

    for(j=1; j<10; j++)
    {
        if(board[j] == 3)
            token_input('X',j);
        else if(board[j] == 5)
            token_input('O',j);
    }
}

int make2()
{
    if(board[5] == 2)
        return 5;
    if(board[2] == 2)
        return 2;
    if(board[4] == 2)
        return 4;
    if(board[6] == 2)
        return 6;
    if(board[8] == 2)
        return 8;
    return 0;
}

int make4()
{
    if(board[1] == 2)
        return 1;
    if(board[3] == 2)
        return 3;
    if(board[7] == 2)
        return 7;
    if(board[9] == 2)
        return 9;
    return 0;
}

int posswin(int p)
{
// p==1 then X   p==0  then  O
    int i;
    int val,pos;

    if(p == 1)
        val = 18;
    else
        val = 50;

    i = 1;
    while(i<=9)//row check
    {
        if(board[i] * board[i+1] * board[i+2] == val)
        {
            if(board[i] == 2)
                return i;
            if(board[i+1] == 2)
                return i+1;
            if(board[i+2] == 2)
                return i+2;
        }
        i+=3;
    }

    i = 1;
    while(i<=3)//column check
    {
        if(board[i] * board[i+3] * board[i+6] == val)
        {
            if(board[i] == 2)
                return i;
            if(board[i+3] == 2)
                return i+3;
            if(board[i+6] == 2)
                return i+6;
        }
        i++;
    }

    if(board[1] * board[5] * board[9] == val)
    {
        if(board[1] == 2)
            return 1;
        if(board[5] == 2)
            return 5;
        if(board[9] == 2)
            return 9;
    }

    if(board[3] * board[5] * board[7] == val)
    {
        if(board[3] == 2)
            return 3;
        if(board[5] == 2)
            return 5;
        if(board[7] == 2)
            return 7;
    }
    return 0;
}

void go(int n)
{
    if(turn % 2)
        board[n] = 3;
    else
        board[n] = 5;
    turn++;
}

void token_input(char ch,int pos)
{
    int m;
    int x = 31, y = 10;

    m = pos;

    if(m > 3)
    {
        while(m > 3)
        {
            y += 3;
            m -= 3;
        }
    }
    if(pos % 3 == 0)
        x += 16;
    else
    {
        pos %= 3;
        pos--;
        while(pos)
        {
            x+=8;
            pos--;
        }
    }
    spacing(x,y);
    printf("%c",ch);
}
