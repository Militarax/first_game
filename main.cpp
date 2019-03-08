#include <graphics.h>
#include <winbgim.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include<iomanip>
#include <string>
#include <windows.h>
#include <time.h>
#include <MMSystem.h>
#include <iostream>

#define MAX 8

using namespace std;

int game_table[MAX][MAX];
int table[1000][MAX][MAX];
bool is_clicked, play, fplayer, settings, play_com, fl = true, placed, moved,found, que;
int sz, width, height, part, xx, yy, add_x, counter, prev_pl, color_1 = 1, color_2 = 4,fplayer_int, background;
unsigned int mov = 0;
char buff[20];

bool is_blocked(int line, int column);
void print_table();
int main();
void print_piece();
void buttons(int x, int y);
void print_buttons();

void save()
{
    if (counter < 1000)
    {
        for(int i = 0; i < 8; i++)
            for(int j = 0; j < 8; j++)
                table[counter][i][j] = game_table[i][j];

        prev_pl = fplayer;
        counter++;
    }
}

void prev()
{
    if (counter >= 0)
    {
        counter--;
        for(int i = 0; i < 8; i++)
            for(int j = 0; j < 8; j++)
                game_table[i][j] = table[counter][i][j];

        fplayer = prev_pl;
        mov--;
    }
    clearviewport();
    print_table();
    print_piece();
}

bool find_the_unblocked(int line, int column, int n)
{
    if (game_table[line][column] == n and !is_blocked(line, column))
        return true;
    if (line - 1 >= 0 and line + 1 <= 7 and column + 1 <= 7 and column - 1 >= 0)
    {
        if (game_table[line - 1][column] != 0 and game_table[line + 1][column] != 0 and game_table[line][column + 1] != 0 and game_table[line][column - 1] != 0)
        {
            if (game_table[line - 1][column] == n and game_table[line + 1][column] == n and game_table[line][column + 1] == n and game_table[line][column - 1] == n)
            {
                game_table[line][column] = -n;
                return false || find_the_unblocked(line - 1, column, n) || find_the_unblocked(line + 1, column, n) || find_the_unblocked(line, column - 1, n) || find_the_unblocked(line, column + 1, n);
            }
            else if(game_table[line - 1][column] == n and game_table[line + 1][column] == n and game_table[line][column + 1] == n and game_table[line][column - 1] != n)
            {
                game_table[line][column] = -n;
                return false || find_the_unblocked(line - 1, column, n) || find_the_unblocked(line + 1, column, n) || find_the_unblocked(line, column + 1, n);
            }
            else if(game_table[line - 1][column] == n and game_table[line + 1][column] == n and game_table[line][column + 1] != n and game_table[line][column - 1] == n)
            {
                game_table[line][column] = -n;
                return false || find_the_unblocked(line - 1, column, n) || find_the_unblocked(line + 1, column, n) || find_the_unblocked(line, column - 1, n);
            }
            else if(game_table[line - 1][column] == n and game_table[line + 1][column] != n and game_table[line][column + 1] == n and game_table[line][column - 1] == n)
            {
                game_table[line][column] = -n;
                return false || find_the_unblocked(line - 1, column, n) || find_the_unblocked(line, column - 1, n) || find_the_unblocked(line, column + 1, n);
            }
            else if(game_table[line - 1][column] != n and game_table[line + 1][column] == n and game_table[line][column + 1] == n and game_table[line][column - 1] == n)
            {
                game_table[line][column] = -n;
                return false || find_the_unblocked(line + 1, column, n) || find_the_unblocked(line, column - 1, n) || find_the_unblocked(line, column + 1, n);
            }
            else if(game_table[line - 1][column] != n and game_table[line + 1][column] != n and game_table[line][column + 1] == n and game_table[line][column - 1] == n)
            {
                game_table[line][column] = -n;
                return false || find_the_unblocked(line, column - 1, n) || find_the_unblocked(line, column + 1, n);
            }
            else if(game_table[line - 1][column] != n and game_table[line + 1][column] == n and game_table[line][column + 1] != n and game_table[line][column - 1] == n)
            {
                game_table[line][column] = -n;
                return false || find_the_unblocked(line + 1, column, n) || find_the_unblocked(line, column - 1, n);
            }
            else if(game_table[line - 1][column] != n and game_table[line + 1][column] == n and game_table[line][column + 1] == n and game_table[line][column - 1] != n)
            {
                game_table[line][column] = -n;
                return false || find_the_unblocked(line + 1, column, n) || find_the_unblocked(line, column + 1, n);
            }
            else if(game_table[line - 1][column] == n and game_table[line + 1][column] != n and game_table[line][column + 1] != n and game_table[line][column - 1] == n)
            {
                game_table[line][column] = -n;
                return false || find_the_unblocked(line - 1, column, n) || find_the_unblocked(line, column - 1, n);
            }
            else if(game_table[line - 1][column] == n and game_table[line + 1][column] != n and game_table[line][column + 1] == n and game_table[line][column - 1] != n)
            {
                game_table[line][column] = -n;
                return false || find_the_unblocked(line - 1, column, n) || find_the_unblocked(line, column + 1, n);
            }
            else if(game_table[line - 1][column] == n and game_table[line + 1][column] == n and game_table[line][column + 1] != n and game_table[line][column - 1] != n)
            {
                game_table[line][column] = -n;
                return false || find_the_unblocked(line - 1, column, n) || find_the_unblocked(line + 1, column, n);
            }
            else if (game_table[line - 1][column] == n and game_table[line + 1][column] != n and game_table[line][column + 1] != n and game_table[line][column - 1] != n)
            {
                game_table[line][column] = -n;
                return false || find_the_unblocked(line - 1, column, n);
            }
            else if (game_table[line - 1][column] != n and game_table[line + 1][column] == n and game_table[line][column + 1] != n and game_table[line][column - 1] != n)
            {
                game_table[line][column] = -n;
                return false || find_the_unblocked(line + 1, column, n);
            }
            else if (game_table[line - 1][column] != n and game_table[line + 1][column] != n and game_table[line][column + 1] != n and game_table[line][column - 1] == n)
            {
                game_table[line][column] = -n;
                return false || find_the_unblocked(line, column - 1, n);
            }
            else if (game_table[line - 1][column] != n and game_table[line + 1][column] != n and game_table[line][column + 1] == n and game_table[line][column - 1] != n)
            {
                game_table[line][column] = -n;
                return false || find_the_unblocked(line, column + 1, n);
            }
            else
                return false;
        }
    }
    else if (line - 1 < 0 and column - 1 >=0 and column + 1 <= 7)
    {
        if (game_table[line + 1][column] != 0 and game_table[line][column + 1] != 0 and game_table[line][column - 1] != 0)
        {
            if (game_table[line + 1][column] == n and game_table[line][column - 1] == n and game_table[line][column + 1] == n)
            {
                game_table[line][column] = -n;
                return false || find_the_unblocked(line + 1, column, n) || find_the_unblocked(line,column - 1, n)  || find_the_unblocked(line, column + 1, n);
            }
            else if(game_table[line + 1][column] != n and game_table[line][column - 1] == n and game_table[line][column + 1] == n)
            {
                game_table[line][column] = -n;
                return false ||  find_the_unblocked(line,column - 1, n)  || find_the_unblocked(line, column + 1, n);
            }
            else if (game_table[line + 1][column] == n and game_table[line][column - 1] != n and game_table[line][column + 1] == n)
            {
                game_table[line][column] = -n;
                return false || find_the_unblocked(line + 1, column, n) || find_the_unblocked(line, column + 1, n);
            }
            else if (game_table[line + 1][column] == n and game_table[line][column - 1] == n and game_table[line][column + 1] != n)
            {
                game_table[line][column] = -n;
                return false || find_the_unblocked(line + 1, column, n) || find_the_unblocked(line,column - 1, n);
            }
            else if (game_table[line][column - 1] == n and game_table[line + 1][column] != n and game_table[line][column + 1] != n)
            {
                game_table[line][column] = -n;
                return false || find_the_unblocked(line, column - 1, n);
            }
            else if (game_table[line][column + 1] == n and game_table[line + 1][column] != n and game_table[line][column - 1] != n)
            {
                game_table[line][column] = -n;
                return false || find_the_unblocked(line, column + 1, n);
            }
            else if (game_table[line + 1][column] == n and game_table[line][column - 1] != n and game_table[line][column + 1] != n)
            {
                game_table[line][column] = -n;
                return false || find_the_unblocked(line + 1, column, n);
            }
            else
                return false;
        }
    }
    else if (line + 1 > 7 and column - 1 >= 0 and column + 1 <= 7)
    {
        if (game_table[line - 1][column] != 0 and game_table[line][column + 1] != 0 and game_table[line][column - 1] != 0)
        {
            if (game_table[line - 1][column] == n and game_table[line][column - 1] == n and game_table[line][column + 1] == n)
            {
                game_table[line][column] = -n;
                return false || find_the_unblocked(line - 1, column, n) || find_the_unblocked(line,column - 1, n)  || find_the_unblocked(line, column + 1, n);
            }
            else if(game_table[line - 1][column] != n and game_table[line][column - 1] == n and game_table[line][column + 1] == n)
            {
                game_table[line][column] = -n;
                return false ||  find_the_unblocked(line,column - 1, n)  || find_the_unblocked(line, column + 1, n);
            }
            else if (game_table[line - 1][column] == n and game_table[line][column - 1] != n and game_table[line][column + 1] == n)
            {
                game_table[line][column] = -n;
                return false || find_the_unblocked(line - 1, column, n) || find_the_unblocked(line, column + 1, n);
            }
            else if (game_table[line - 1][column] == n and game_table[line][column - 1] == n and game_table[line][column + 1] != n)
            {
                game_table[line][column] = -n;
                return false || find_the_unblocked(line - 1, column, n) || find_the_unblocked(line,column - 1, n);
            }
            else if (game_table[line - 1][column] != n and game_table[line][column - 1] != n and game_table[line][column + 1] == n)
            {
                game_table[line][column] = -n;
                return false || find_the_unblocked(line, column + 1, n);
            }
            else if (game_table[line - 1][column] != n and game_table[line][column - 1] == n and game_table[line][column + 1] != n)
            {
                game_table[line][column] = -n;
                return false || find_the_unblocked(line, column - 1, n);
            }
            else if (game_table[line - 1][column] == n and game_table[line][column - 1] != n and game_table[line][column + 1] != n)
            {
                game_table[line][column] = -n;
                return false || find_the_unblocked(line - 1, column, n);
            }
            else
                return false;
        }
    }
    else if (column - 1 < 0 and line - 1 >=0 and line + 1 <= 7)
    {
        if (game_table[line + 1][column] != 0 and game_table[line - 1][column] != 0 and game_table[line][column + 1] != 0)
        {
            if(game_table[line + 1][column] == n and game_table[line - 1][column]  == n and game_table[line][column + 1] == n)
            {
                game_table[line][column] = -n;
                return false || find_the_unblocked(line + 1,column, n) || find_the_unblocked(line, column + 1, n) || find_the_unblocked(line - 1, column, n);
            }
            else if(game_table[line + 1][column] != n and game_table[line - 1][column]  == n and game_table[line][column + 1] == n)
            {
                game_table[line][column] = -n;
                return false || find_the_unblocked(line - 1,column, n) || find_the_unblocked(line, column + 1, n);
            }
            else if(game_table[line + 1][column] == n and game_table[line - 1][column]  != n and game_table[line][column + 1] == n)
            {
                game_table[line][column] = -n;
                return false || find_the_unblocked(line + 1,column, n) || find_the_unblocked(line, column + 1, n);
            }
            else if(game_table[line + 1][column] == n and game_table[line - 1][column]  == n and game_table[line][column + 1] != n)
            {
                game_table[line][column] = -n;
                return false || find_the_unblocked(line + 1, column, n) || find_the_unblocked(line - 1, column, n);
            }
            else if (game_table[line + 1][column] == n and game_table[line - 1][column]  != n and game_table[line][column + 1] != n)
            {
                game_table[line][column] = -n;
                return false || find_the_unblocked(line + 1, column, n);
            }
            else if (game_table[line + 1][column] != n and game_table[line - 1][column]  == n and game_table[line][column + 1] != n)
            {
                game_table[line][column] = -n;
                return false || find_the_unblocked(line - 1, column, n);
            }
            else if (game_table[line + 1][column] != n and game_table[line - 1][column]  != n and game_table[line][column + 1] == n)
            {
                game_table[line][column] = -n;
                return false || find_the_unblocked(line, column + 1, n);
            }
            else
                return false;
        }
    }
    else if (column + 1 > 7 and line - 1 >=0 and line + 1 <= 7)
    {
        if (game_table[line + 1][column] != 0 and game_table[line - 1][column] != 0 and game_table[line][column - 1] != 0)
        {
            if(game_table[line + 1][column] == n and game_table[line - 1][column]  == n and game_table[line][column - 1] == n)
            {
                game_table[line][column] = -n;
                return false || find_the_unblocked(line + 1,column, n) || find_the_unblocked(line, column - 1, n) || find_the_unblocked(line - 1, column, n);
            }
            else if(game_table[line + 1][column] != n and game_table[line - 1][column]  == n and game_table[line][column - 1] == n)
            {
                game_table[line][column] = -n;
                return false || find_the_unblocked(line - 1,column, n) || find_the_unblocked(line, column - 1, n);
            }
            else if(game_table[line + 1][column] == n and game_table[line - 1][column]  != n and game_table[line][column - 1] == n)
            {
                game_table[line][column] = -n;
                return false || find_the_unblocked(line + 1,column, n) || find_the_unblocked(line, column - 1, n);
            }
            else if(game_table[line + 1][column] == n and game_table[line - 1][column]  == n and game_table[line][column - 1] != n)
            {
                game_table[line][column] = -n;
                return false || find_the_unblocked(line + 1, column, n) || find_the_unblocked(line - 1, column, n);
            }
            else if (game_table[line + 1][column] == n and game_table[line - 1][column]  != n and game_table[line][column - 1] != n)
            {
                game_table[line][column] = -n;
                return false || find_the_unblocked(line + 1, column, n);
            }
            else if (game_table[line + 1][column] != n and game_table[line - 1][column]  == n and game_table[line][column - 1] != n)
            {
                game_table[line][column] = -n;
                return false || find_the_unblocked(line - 1, column, n);
            }
            else if (game_table[line + 1][column] != n and game_table[line - 1][column]  != n and game_table[line][column - 1] == n)
            {
                game_table[line][column] = -n;
                return false || find_the_unblocked(line, column - 1, n);
            }
            else
                return false;
        }
    }
    else if (line - 1 < 0 and column - 1 < 0)
    {
        if(game_table[line + 1][column] != 0 and game_table[line][column + 1] != 0)
        {
            if (game_table[line + 1][column] == n and game_table[line][column + 1] == n)
            {
                game_table[line][column] = -n;
                return false || find_the_unblocked(line + 1, column, n) || find_the_unblocked(line, column + 1, n);
            }
            else if (game_table[line + 1][column] != n and game_table[line][column + 1] == n)
            {
                game_table[line][column] = -n;
                return false || find_the_unblocked(line, column + 1, n);
            }
            else if(game_table[line + 1][column] == n and game_table[line][column + 1] != n)
            {
                game_table[line][column] =-n;
                return false || find_the_unblocked(line + 1, column, n);
            }
            else
                return false;
        }
    }
    else if (line + 1 > 7 and column + 1 > 7)
    {
        if(game_table[line - 1][column] != 0 and game_table[line ][column - 1] != 0)
        {
            if (game_table[line - 1][column] == n and game_table[line][column - 1] == n)
            {
                game_table[line][column] = -n;
                return false || find_the_unblocked(line - 1, column, n) || find_the_unblocked(line, column - 1, n);
            }
            else if (game_table[line - 1][column] != n and game_table[line][column - 1] == n)
            {
                game_table[line][column] = -n;
                return false || find_the_unblocked(line, column - 1, n);
            }
            else if(game_table[line - 1][column] == n and game_table[line][column - 1] != n)
            {
                game_table[line][column] = -n;
                return false || find_the_unblocked(line - 1, column, n);
            }
            else
                return false;
        }
    }
    else if (line + 1 > 7 and column - 1 < 0)
    {
        if(game_table[line - 1][column] != 0 and game_table[line][column + 1] != 0)
        {
            if (game_table[line - 1][column] == n and game_table[line][column + 1] == n)
            {
                game_table[line][column] = -n;
                return false || find_the_unblocked(line - 1, column, n) || find_the_unblocked(line, column + 1, n);
            }
            else if (game_table[line - 1][column] != n and game_table[line][column + 1] == n)
            {
                game_table[line][column] = -n;
                return false || find_the_unblocked(line, column + 1, n);
            }
            else if(game_table[line - 1][column] == n and game_table[line][column + 1] != n)
            {
                game_table[line][column] = -n;
                return false || find_the_unblocked(line - 1, column, n);
            }
            else
                return false;
        }
    }
    else if (line - 1 < 0 and column + 1 > 7)
    {
        if(game_table[line + 1][column] != 0 and game_table[line][column - 1] != 0)
        {
            if (game_table[line + 1][column] == n and game_table[line][column - 1] == n)
            {
                game_table[line][column] = -n;
                return false || find_the_unblocked(line + 1, column, n) || find_the_unblocked(line, column - 1, n);
            }
            else if (game_table[line][column - 1] == n and game_table[line + 1][column] != n)
            {
                game_table[line][column] = -n;
                return false || find_the_unblocked(line, column - 1, n);
            }
            else if(game_table[line + 1][column] == n and game_table[line][column - 1] != n)
            {
                game_table[line][column] = -n;
                return false || find_the_unblocked(line + 1, column, n);
            }
            else
                return false;
        }
    }
    return false;
}

int logic()
{
    int count_1 = 0;
    int count_2 = 0;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (game_table[i][j] == 1 and is_blocked(i, j))
            {
                if (!find_the_unblocked(i, j, 1))
                    count_1++;
            }
            else if(game_table[i][j] == 2 and is_blocked(i, j))
            {
                if (!find_the_unblocked(i, j, 2))
                    count_2++;
            }
            for (int i = 0; i < 8; i++)
                for (int j = 0; j < 8; j++)
                {
                    if (game_table[i][j] == -1)
                        game_table[i][j] = 1;
                    if(game_table[i][j] == -2)
                        game_table[i][j] = 2;
                }
        }
    }
    if (count_1 > count_2)
    {
        fplayer_int = 1;
        return 1;
    }
    if (count_1 < count_2)
    {
        fplayer_int = 2;
        return 2;
    }
    if (count_1 != 0  and count_2 != 0 and (count_1 == count_2))
    {
        fplayer_int = 228;
        return 3;
    }
    if(fl == false)
        return 4;
    return 0;
}

bool is_blocked(int line, int column)
{
    if (line - 1 >= 0 and line + 1 <= 7 and column + 1 <= 7 and column - 1 >= 0)
    {
        if (game_table[line - 1][column] != 0 and game_table[line + 1][column] != 0 and game_table[line][column + 1] != 0 and game_table[line][column - 1] != 0)
            return true;
    }
    else if (line - 1 < 0 and column - 1 >=0 and column + 1 <= 7)
    {
        if (game_table[line + 1][column] != 0 and game_table[line][column + 1] != 0 and game_table[line][column - 1] != 0)
            return true;
    }
    else if (line + 1 > 7 and column - 1 >=0 and column + 1 <= 7)
    {
        if (game_table[line - 1][column] != 0 and game_table[line][column + 1] != 0 and game_table[line][column - 1] != 0)
            return true;
    }
    else if (column - 1 < 0 and line - 1 >=0 and line + 1 <= 7)
    {
        if (game_table[line + 1][column] != 0 and game_table[line - 1][column] != 0 and game_table[line][column + 1] != 0)
            return true;
    }
    else if (column + 1 > 7 and line - 1 >=0 and line + 1 <= 7)
    {
        if (game_table[line + 1][column] != 0 and game_table[line - 1][column] != 0 and game_table[line][column - 1] != 0)
            return true;
    }
    else if (line - 1 < 0 and column - 1 < 0)
    {
        if(game_table[line + 1][column] != 0 and game_table[line][column + 1] != 0)
            return true;
    }
    else if (line + 1 > 7 and column + 1 > 7)
    {
        if(game_table[line - 1][column] != 0 and game_table[line][column - 1] != 0)
            return true;
    }
    else if (line + 1 > 7 and column - 1 < 0)
    {
        if(game_table[line - 1][column] != 0 and game_table[line][column + 1] != 0)
            return true;
    }
    else if (line - 1 < 0 and column + 1 > 7)
    {
        if(game_table[line + 1][column] != 0 and game_table[line][column - 1] != 0)
            return true;
    }
    return false;
}

int count_pieces()
{
    int cnt = 0;
    for(int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
            if (game_table[i][j] != 0)
                cnt++;
    }
    return cnt;
}

int count_bl_pieces(int player)
{
    int cnt = 0;
    for(int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
            if (is_blocked(i, j) and game_table[i][j] == player)
                cnt++;
    }
    return cnt;
}

void print_piece()
{
    for(int i = 0; i <= 7; i++)
    {
        for(int j = 0; j <= 7; j ++)
        {
            if(game_table[i][j] == 1)
            {
                setfillstyle(SOLID_FILL, color_1);
                circle(xx + sz * j + sz / 2, yy + sz * i + sz / 2, sz / 4);
                floodfill(xx + sz * j + sz / 2, yy + sz * i + sz / 2, WHITE);
            }
            else if(game_table[i][j] == 2)
            {
                setfillstyle(SOLID_FILL, color_2);
                circle(xx + sz * j + sz / 2, yy + sz * i + sz / 2, sz / 4);
                floodfill(xx + sz * j + sz / 2, yy + sz * i + sz / 2, WHITE);
            }
        }
    }
}

void delete_piece(int line, int column)
{
    if ((line + column) % 2 == 0)
    {
        setfillstyle(SOLID_FILL, 9);
        bar(xx + sz * column + 6, yy + sz * line + 6, xx + sz * column + (sz- 6), yy + sz * line + (sz- 6));
    }
    else
    {
        setfillstyle(SOLID_FILL, BLACK);
        bar(xx + sz * column + 6, yy + sz * line + 6, xx + sz * column + (sz - 6), yy + sz * line + (sz - 6));
    }
    game_table[line][column] = 0;
}

void buttons(int x, int y)
{
    if ((x >= (getmaxx() - 105) and x <= (getmaxx() - 85)) and (y >= 20 and y <= 40))
    {
        if (height < getmaxx() - 20 and width < getmaxy() - 20)
        {
            PlaySound("00171.wav",NULL,SND_FILENAME);
            add_x += 20;
            print_table();
            print_piece();
            if (fplayer == true and (!play_com))
                outtextxy(getmaxx() - 180, getmaxy() / 2 + 2, (char*)"It is second player's turn         ");
            else if(fplayer == false and !play_com)
                outtextxy(getmaxx() - 180, getmaxy() / 2 + 2, (char*)"It is first player's turn                 ");
        }
    }
    if ((x >= getmaxx() - 135 and x <= getmaxx() - 115) and (y >= 20 and y <= 40))
    {
        PlaySound("00171.wav",NULL,SND_FILENAME);
        add_x -= 20;
        print_table();
        print_piece();
        if (fplayer == true and (!play_com))
            outtextxy(getmaxx() - 180, getmaxy() / 2 + 2, (char*)"It is second player's turn         ");
        else if(fplayer == false and !play_com)
            outtextxy(getmaxx() - 180, getmaxy() / 2 + 2, (char*)"It is first player's turn                     ");
    }
    if ((x >= 15 and x <= 65) and (y >= 15 and y <= 50))
    {
        PlaySound("00171.wav",NULL,SND_FILENAME);
        clearviewport();
        outtextxy(getmaxx() / 2, getmaxy() / 2, (char*)"BYE");
        Sleep(2000);
        exit(1);
    }
}

void print_buttons()
{
    rectangle(15, 15, 65, 50);
    outtextxy(25,25, (char*)"EXIT");

    rectangle(getmaxx() - 105, 20, getmaxx() - 85, 40);
    outtextxy(getmaxx() - 98,22, (char*)"+");

    rectangle(getmaxx() - 135, 20, getmaxx() - 115, 40);
    outtextxy(getmaxx() - 128,22,(char*)"--");

    itoa(mov, buff, 10);
    outtextxy(getmaxx() - 180, getmaxy() - 100, (char*)"Move number: ");
    outtextxy(getmaxx() - 80, getmaxy() - 100, buff);

    if (fplayer == false and (!play_com))
        outtextxy(getmaxx() - 180, getmaxy() / 2 + 2, (char*)"It is second player's turn                    ");
    else if(fplayer == true and (!play_com))
        outtextxy(getmaxx() - 180, getmaxy() / 2 + 2, (char*)"It is first player's turn                        ");
}

void move_piece_c()
{
b:
    srand (time(NULL));
    int j1 = rand() % 7, i1 = rand() % 7;
    int i = 0,j = 0;

    for(; i1 < 8; i1++)
    {
        for(; j1 < 8; j1++)
            if(game_table[i1][j1] == 2 and !is_blocked(i1, j1))
                break;
        if(game_table[i1][j1] == 2 and !is_blocked(i1, j1))
            break;
    }

    for(i = i1; i < 8; i++)
    {
        for(j = j1; j < 8; j++)
            if(game_table[i][j] == 1 and !is_blocked(i, j))
                break;
        if(game_table[i][j] == 1 and !is_blocked(i, j))
            break;
    }
    if(game_table[i][j] == 0)
        goto b;
    else
    {
        if(j == j1 and i < i1 and (i1 >= 0 and i1 <= 7 and j1 >= 0 and j1 <= 7))
        {
            if (game_table[i1 - 1][j1] == 0 and i1 - 1 >= 0)
            {
                delete_piece(i1, j1);
                game_table[i1 - 1][j1] = 2;
                found = true;
            }
            else if(game_table[i1][j1 - 1] == 0 and j1 - 1 >= 0)
            {
                delete_piece(i1, j1);
                game_table[i1][j1 - 1] = 2;
                found = true;
            }
            else if(game_table[i1][j1 + 1] == 0 and j1  + 1 < 8)
            {
                delete_piece(i1, j1);
                game_table[i1][j1 + 1] = 2;
                found = true;
            }
        }
        else if(j == j1 and i > i1 and (i1 >= 0 and i1 <= 7 and j1 >= 0 and j1 <= 7))
        {
            if (game_table[i1 + 1][j1] == 0 and i1 + 1 < 8)
            {
                delete_piece(i1, j1);
                game_table[i1 + 1][j1] = 2;
                found = true;
            }
            else if(game_table[i1][j1 - 1] == 0 and j1 - 1 >= 0)
            {
                delete_piece(i1, j1);
                game_table[i1][j1 - 1] = 2;
                found = true;
            }
            else if(game_table[i1][j1 + 1] == 0 and j1 + 1 < 8)
            {
                delete_piece(i1, j1);
                found = true;
                game_table[i1][j1 + 1] = 2;
            }
        }
        else if(j > j1 and i == i1 and (i1 >= 0 and i1 <= 7 and j1 >= 0 and j1 <= 7))
        {
            if (game_table[i1][j1 + 1] == 0 and j1 + 1 < 8)
            {
                delete_piece(i1, j1);
                game_table[i1][j1 + 1] = 2;
                found = true;
            }
            else if(game_table[i1 - 1][j1] == 0 and i1 - 1 >= 0)
            {
                delete_piece(i1, j1);
                game_table[i1 - 1][j1] = 2;
                found = true;
            }
            else if(game_table[i1 + 1][j1] == 0 and i1 + 1 < 8)
            {
                delete_piece(i1, j1);
                game_table[i1 + 1][j1] = 2;
                found = true;
            }
        }
        else if(j < j1 and i == i1 and (i1 >= 0 and i1 <= 7 and j1 >= 0 and j1 <= 7))
        {
            if (game_table[i1][j1 - 1] == 0 and j1 - 1 >= 0)
            {
                delete_piece(i1, j1);
                game_table[i1][j1 - 1] = 2;
                found = true;
            }
            else if(game_table[i1 - 1][j1] == 0 and i1 - 1 >= 0)
            {
                delete_piece(i1, j1);
                game_table[i1 - 1][j1] = 2;
                found = true;
            }
            else if(game_table[i1 + 1][j1] == 0 and i1 + 1 < 8)
            {
                delete_piece(i1, j1);
                game_table[i1 + 1][j1] = 2;
                found = true;
            }
        }
        else if(j > j1 and i > i1 and (i1 >= 0 and i1 <= 7 and j1 >= 0 and j1 <= 7))
        {
            if (game_table[i1 + 1][j1] == 0 and i1 + 1 < 8)
            {
                delete_piece(i1, j1);
                game_table[i1 + 1][j1] = 2;
                found = true;
            }
            else if (game_table[i1][j1 + 1] == 0 and j1 + 1 < 8)
            {
                delete_piece(i1, j1);
                game_table[i1][j1 + 1] = 2;
                found = true;
            }
            else if (game_table[i1 - 1][j1] == 0 and i1 - 1 >= 0)
            {
                delete_piece(i1, j1);
                found = true;
                game_table[i1 -1][j1] = 2;
            }
            else if (game_table[i1][j1 - 1] == 0 and j1 - 1 >= 0)
            {
                delete_piece(i1, j1);
                found = true;
                game_table[i1][j1 - 1] = 2;
            }
        }
        else if(j > j1 and i < i1 and (i1 >= 0 and i1 <= 7 and j1 >= 0 and j1 <= 7))
        {
            if (game_table[i1 + 1][j1] == 0 and i1 + 1 < 8)
            {
                delete_piece(i1, j1);
                found = true;
                game_table[i1 + 1][j1] = 2;
            }
            else if (game_table[i1][j1 + 1] == 0 and j1 + 1 < 8)
            {
                delete_piece(i1, j1);
                game_table[i1][j1 + 1] = 2;
                found = true;
            }
            else if (game_table[i1 - 1][j1] == 0 and i1 - 1 >= 0)
            {
                delete_piece(i1, j1);
                game_table[i1 -1][j1] = 2;
            }
            else if (game_table[i1][j1 - 1] == 0 and j1 - 1 >= 0)
            {
                delete_piece(i1, j1);
                game_table[i1][j1 - 1] = 2;
                found = true;
            }
        }
        else if(j < j1 and i > i1 and (i1 >= 0 and i1 <= 7 and j1 >= 0 and j1 <= 7))
        {
            if (game_table[i1 + 1][j1] == 0 and i1 + 1 < 8)
            {
                delete_piece(i1, j1);
                game_table[i1 + 1][j1] = 2;
                found = true;
            }
            else if (game_table[i1][j1 + 1] == 0 and j1 + 1 < 8)
            {
                delete_piece(i1, j1);
                game_table[i1][j1 + 1] = 2;
                found = true;
            }
            else if (game_table[i1 - 1][j1] == 0 and i1 - 1 >= 0)
            {
                delete_piece(i1, j1);
                found = true;
                game_table[i1 -1][j1] = 2;
            }
            else if (game_table[i1][j1 - 1] == 0 and j1 - 1 >= 0)
            {
                delete_piece(i1, j1);
                found = true;
                game_table[i1][j1 - 1] = 2;
            }
        }
        else if(j < j1 and i < i1 and (i1 >= 0 and i1 <= 7 and j1 >= 0 and j1 <= 7))
        {
            if (game_table[i1 + 1][j1] == 0 and i1 + 1 < 8)
            {
                delete_piece(i1, j1);
                found = true;
                game_table[i1 + 1][j1] = 2;
            }
            else if (game_table[i1][j1 + 1] == 0 and j1 + 1 < 8)
            {
                delete_piece(i1, j1);
                found = true;
                game_table[i1][j1 + 1] = 2;
            }
            else if (game_table[i1 - 1][j1] == 0 and i1 - 1 >= 0)
            {
                delete_piece(i1, j1);
                found = true;
                game_table[i1 -1][j1] = 2;
            }
            else if (game_table[i1][j1 - 1] == 0 and j1 - 1 >= 0)
            {
                delete_piece(i1, j1);
                found = true;
                game_table[i1][j1 - 1] = 2;
            }
        }
        if (!found)
            goto b;
        mov++;
        PlaySound("Drawer Slide Close-SoundBible.com-35853910-[AudioTrimmer.com].wav",NULL,SND_FILENAME);
        fplayer = !fplayer;
        print_piece();
    }
}

void move_piece()
{
    int x,y,line,column, line1, column1,x1 = getmaxx(), y1 = getmaxy();
    bool click = false;
    int player;
    found = false;
    print_buttons();
    long int ttime = time(NULL);

    if (fplayer == false)
    {
        if (!play_com)
            outtextxy(getmaxx() - 180, getmaxy() / 2 + 2, (char*)"It is first player's turn                 ");
        player = 1;
    }
    else
    {
        if (!play_com)
            outtextxy(getmaxx() - 180, getmaxy() / 2 + 2, (char*)"It is second player's turn");
        player = 2;
    }
    do
    {
        if (GetAsyncKeyState(VK_ESCAPE))
            return;
        click = false;
        char timeShow[6]="00:05";
        long int ttime2 = time(NULL);
        timeShow[4]=timeShow[4]-(ttime2-ttime);
       if(!play_com and timeShow[4] >= '0')
            {
                rectangle(getmaxx() - 135, 110, getmaxx() - 85, 150);
                outtextxy(getmaxx() - 110-textwidth(timeShow)/2, 130-textheight(timeShow)/2, timeShow);
            }
        if(ismouseclick(WM_LBUTTONDOWN))
        {
             if(!play_com and timeShow[4] >= '0')
            {
                rectangle(getmaxx() - 135, 110, getmaxx() - 85, 150);
                outtextxy(getmaxx() - 110-textwidth(timeShow)/2, 130-textheight(timeShow)/2, timeShow);
            }
            if (! play_com and ttime2 - ttime > 5)
            {
                fl = false;
                fplayer = !fplayer;
            }
            clearmouseclick(WM_LBUTTONDOWN);
            x = mousex();
            y = mousey();
            if (x >= xx && x <= xx + width && y >= yy && y <=  yy + height)
            {
                line = (y - yy) / sz;
                column = (x - xx) / sz;
                if(is_blocked(line, column))
                {
                    outtextxy(getmaxx() - 180, y1 / 2 + 2,(char*)"Try another piece                               ");
                    Sleep(1000);
                    outtextxy(x1 / 2 + 300, y1 / 2,(char*) "                               ");
                    move_piece();
                    return;
                }

                if(game_table[line][column] == 2 and play_com)
                {
                    outtextxy(getmaxx() - 180, y1 / 2,(char*)"It is not your piece                               ");
                    Sleep(1500);
                    outtextxy(getmaxx() - 180, y1 / 2, (char*)"                               ");
                    move_piece();
                    return;
                }
                if (game_table[line][column] == player)
                {
                    do
                    {
                        if (GetAsyncKeyState(VK_ESCAPE))
                            return;
                        if(ismouseclick(WM_LBUTTONDOWN))
                        {
                            clearmouseclick(WM_LBUTTONDOWN);
                            x = mousex();
                            y = mousey();

                            if(!play_com)
                            {
                                rectangle(getmaxx() - 135, 110, getmaxx() - 85, 150);
                                outtextxy(getmaxx() - 110-textwidth(timeShow)/2, 130-textheight(timeShow)/2, timeShow);
                            }
                            if (x >= xx && x <= xx + width && y >= yy && y <=  yy + height)
                            {
                                line1 = (y - yy) / sz;
                                column1 = (x - xx) / sz;
                                if ((line1 >= 0 and line1 <=7) and (column1 >= 0 and column <= 7) and ((line1 == line + 1 and column1 == column) or
                                        (line1 == line - 1 and column1 == column) or (line1 == line and column1 == column - 1) or (line1 == line and column1 == column + 1)) and game_table[line1][column1] == 0)
                                {
                                    PlaySound("Drawer Slide Close-SoundBible.com-35853910-[AudioTrimmer.com].wav",NULL,SND_FILENAME);
                                    click = true;
                                    fplayer = !fplayer;
                                    game_table[line1][column1] = player;
                                    mov++;
                                    delete_piece(line, column);

                                    if (player == 1)
                                        setfillstyle(SOLID_FILL, color_1);
                                    else
                                        setfillstyle(SOLID_FILL, color_2);

                                    circle(xx + sz * column1 + sz / 2, yy + sz * line1 + sz / 2, sz / 4);
                                    floodfill(xx + sz * column1 + sz / 2, yy + sz * line1 + sz / 2, WHITE);

                                }
                            }
                        }
                    }
                    while(!click);
                }
            }
            else
                buttons(x, y);
        }
    }
    while(!click);
    save();
    if(GetAsyncKeyState(66) and mov > 16)
    {
        prev();
        cout<<1;
        return;
    }
}

void put_piece_c()
{
    for(int i = 0; i < MAX; i++)
    {
        for(int j = 0; j < MAX; j++)
        {
            if (game_table[i][j] == 1 and !is_blocked(i, j))
            {
                if (game_table[i - 1][j] == 0 and (i - 1 >= 0))
                {
                    game_table[i - 1][j] = 2;
                    mov++;
                    print_piece();
                    fplayer = !fplayer;
                    placed = true;
                    return;
                }
                if (game_table[i + 1][j] == 0 and (i + 1 < 8))
                {
                    game_table[i + 1][j] = 2;
                    mov++;
                    print_piece();
                    fplayer = !fplayer;
                    placed = true;
                    return;
                }
                if (game_table[i][j + 1] == 0 and (j + 1 < 8))
                {
                    game_table[i][j + 1] = 2;
                    mov++;
                    print_piece();
                    fplayer = !fplayer;
                    placed = true;
                    return;
                }
                if (game_table[i][j - 1] == 0 and (j - 1 >= 0))
                {
                    game_table[i][j - 1] = 2;
                    mov++;
                    print_piece();
                    fplayer = !fplayer;
                    placed = true;
                    return;
                }
            }
        }
    }
}

void put_piece()
{

    int line,column,x,y;

    itoa(mov, buff, 10);
    outtextxy(getmaxx() - 180, getmaxy() - 100, (char*)"Move number: ");
    outtextxy(getmaxx() - 80, getmaxy() - 100, buff);
    if(ismouseclick(WM_LBUTTONDOWN))
    {
        clearmouseclick(WM_LBUTTONDOWN);
        x=mousex();
        y=mousey();
        if (x >= xx && x <= xx + width && y >= yy && y <=  yy + height)
        {
            line = (y - yy) / sz;
            column = (x - xx) / sz;
            if ((line >= 0 and line <= 7) and (column >= 0 and column <= 7) and (game_table[line][column] == 0))
            {
                PlaySound("17269037_337993434 (mp3cut.net) (1).wav",NULL,SND_FILENAME);
                if (fplayer == false)
                {
                    if (!play_com)
                        outtextxy(getmaxx() - 180, getmaxy() / 2 + 2, (char*)"It is second player's turn          ");
                    game_table[line][column] = 1;
                    fplayer = true;
                    setfillstyle(SOLID_FILL, color_1);
                    circle(xx + sz * column + sz / 2, yy + sz * line + sz / 2, sz / 4);
                    floodfill(xx + sz * column + sz / 2, yy + sz * line + sz / 2, WHITE);
                }
                else
                {
                    if (!play_com)
                        outtextxy(getmaxx() - 180, getmaxy() / 2 + 2, (char*)"It is first player's turn                ");
                    game_table[line][column] = 2;
                    fplayer = false;
                    setfillstyle(SOLID_FILL, color_2);
                    circle(xx + sz * column + sz / 2, yy + sz * line + sz / 2, sz / 4);
                    floodfill(xx + sz * column + sz / 2, yy + sz * line + sz / 2, WHITE);
                }
                save();
                placed = false;
                mov++;
            }
        }
        else
            buttons(x, y);
    }
}

void print_table()
{
    clearviewport();
    setcolor(WHITE);
    width = max(getmaxy(), getmaxx() - min(getmaxy(), getmaxx())) + add_x;
    height = width;
    xx = (getmaxx() - width) / 2;
    yy = (getmaxy() - height) / 2;
    sz = width / 8;

    if(background == 1)
        readimagefile("qZdz8WL0J4Q.jpg",0,0,getmaxx(),getmaxy());
    else if(background == 2)
        readimagefile("ZbZYnRF_Y6E.jpg",0,0,getmaxx(),getmaxy());
     else if(background == 3)
        readimagefile("3B8AXPzewO4.jpg",0,0,getmaxx(),getmaxy());


    for(int i = 1; i <= 8; i++)
    {
        for(int j = 1; j  <= 8; j++)
        {
            rectangle(xx + (sz * j - 1) - sz, yy + (sz * i  - 1) - sz, xx  + (sz * j - 1), yy + (sz * i - 1));
            rectangle(xx + (sz * j - 1) + 5 - sz, yy + (sz * i  - 1) - sz + 5, xx + (sz * j - 1) - 5, yy + (sz * i - 1)- 5);

            if ((i + j) % 2 == 0)
            {
                setfillstyle(SOLID_FILL, 9);
                floodfill(xx + (sz * j - 1) + 6 - sz,yy + (sz * i  - 1) - sz + 6, WHITE);
            }
            else
            {
                setfillstyle(SOLID_FILL, BLACK);
                floodfill(xx + (sz * j - 1) + 6 - sz,yy + (sz * i  - 1) - sz + 6, WHITE);
            }
        }
    }
    print_buttons();
}

void menu(int x, int y)
{
    setcolor(WHITE);
    readimagefile("3130412_0.jpg", x / 2 - 150, y / 2 + 50, x / 2 + 150, y);
    outtextxy(x / 2 - x / 20 - x / 40, y / 5,(char*)"You entered the main menu. ");

    rectangle(x / 2 - 75, y / 2 - 64, x / 2 + 85, y / 2 - 41);
    outtextxy(x / 2 - 65, y / 2 - 58, (char*)"Play Player vs Player");

    rectangle(x / 2 - 82, y / 2 - 34, x / 2 + 92, y / 2 - 11);
    outtextxy(x / 2 - 73, y / 2 - 28,(char*)"Play Player vs Computer");

    rectangle(x / 2 - 60, y / 2 - 4, x / 2 + 60, y / 2 + 19);
    outtextxy(x / 2 - 27, y / 2, (char*)"Settings");

    rectangle(getmaxx() - 135, 20, getmaxx() - 115, 40);
    outtextxy(getmaxx() - 128,22,(char*)"?");

    rectangle(x / 2 - 50, y / 2 + 26, x / 2 + 50, y / 2 + 49);
    outtextxy(x / 2 - 15, y / 2  + 30, (char*)"Exit");

    if(ismouseclick(WM_LBUTTONDOWN))
    {
        clearmouseclick(WM_LBUTTONDOWN);
        int mx = mousex();
        int my = mousey();
        if(mx >= x / 2 - 75 and mx <= x / 2 + 85 and my >= y / 2 - 64  and my <= y / 2 - 41 )
        {
            play = true;
            is_clicked = true;
            PlaySound("00171.wav",NULL,SND_FILENAME);
        }
        else if(mx >= x / 2 - 50 and mx <= x / 2 + 50 and my >= y / 2  + 26 and my <= y / 2 + 49)
        {
            PlaySound("00171.wav",NULL,SND_FILENAME);
            clearviewport();
            outtextxy(x / 2 - 70, y / 2, (char*)"See you soon");
            Sleep(4444);
            exit(1);
        }
        else if (mx >= x / 2 - 82 and mx <= x / 2 + 92 and my >= y / 2 - 34 and my <=  y / 2 - 11)
        {
            PlaySound("00171.wav",NULL,SND_FILENAME);
            play_com = true;
            is_clicked = true;
        }
        else if (mx >= x / 2 - 60 and mx <= x / 2 + 60 and my >=  y / 2 - 4 and my <= y / 2 + 19)
        {
            PlaySound("00171.wav",NULL,SND_FILENAME);
            settings = true;
            is_clicked = true;
        }
        else if(mx >= getmaxx() - 135 and mx <= getmaxx() - 115 and my >= 20 and my <= 40)
        {
            PlaySound("00171.wav",NULL,SND_FILENAME);
            is_clicked = true;
            que = true;
        }
    }
}

void begining(int x, int y)
{
    while(!kbhit())
    {
        outtextxy(x / 2 - 10, y / 2 - 5,  (char*)"Welcome.");
        outtextxy(x / 2  - 25, y / 2 + 10, (char*)"Press any key");
    }
    clearviewport();

    for(int i = 0; i  != 200; i += 2)
        readimagefile("3130412_0.jpg", x / 2 - 150, (y / 2 + 250) - i, x / 2 + 150, y + 200 - i);
}

void end_game(int x, int y)
{
    if (fplayer_int == 2)
        outtextxy(x / 2 - 200, y / 2, (char*)"First player won. Second player maybe next time. Maybe...");
    else if(fplayer_int == 1)
        outtextxy(x / 2 - 200, y / 2, (char*)"Second player won. First player maybe next time. Maybe...");
    else if(fplayer_int == 3)
        outtextxy(x / 2 - 120, y / 2, (char*)"Nice job guys! You did your best!");
    else
        outtextxy(x / 2 - 70, y / 2, (char*)"5 seconds expired");

    rectangle(x / 2 - 50, y / 2 + 66, x / 2 + 50, y / 2 + 89);
    outtextxy(x / 2 - 15, y / 2  + 70, (char*)"Exit");

    rectangle(x / 2 - 70, y / 2 + 26, x / 2 + 70, y / 2 + 49);
    outtextxy(x / 2 - 55, y / 2  + 30, (char*)"Restart the game?");

    if(ismouseclick(WM_LBUTTONDOWN))
    {
        clearmouseclick(WM_LBUTTONDOWN);
        int xm = mousex();
        int ym = mousey();
        if (xm >= x / 2 - 60 and xm <= x / 2 + 60 and  ym >= y / 2 + 26 and ym <= y / 2 + 49)
        {
            PlaySound("00171.wav",NULL,SND_FILENAME);
            is_clicked = false;
            play_com = false;
            play = false;
            settings = false;
            fl = true;
            mov = 0;
            color_1 = 1, color_2 = 4;
            que = false;
            fplayer = false;
            placed = false;
            moved = false;
            found = false;
            for(int i = 0; i < 8; i++)
                for(int j = 0; j < 8; j++)
                {
                    game_table[i][j] = 0;
                    table[0][i][j] = 0;
                }
            counter = 0;
            closegraph();
            main();
        }
        else if(xm >= x / 2 - 50 and xm <= x / 2 + 50 and ym >= y / 2  + 66 and ym <= y / 2 + 89)
        {
            PlaySound("00171.wav",NULL,SND_FILENAME);
            clearviewport();
            outtextxy(x / 2 - 70, y / 2, (char*)"Have a nice day ;)");
            Sleep(4444);
            exit(1);
        }
    }
}

void question()
{
    int x,y;
    que = false;
    clearviewport();
    while(true)
    {
        rectangle(15, 15, 65, 50);
        outtextxy(25,25, (char*)"EXIT");

        rectangle(80, 15, 130, 50);
        outtextxy(88, 25, (char*)"BACK");

        outtextxy(getmaxx()/ 2 - 150, getmaxy() / 6, (char*)"Here you have some rules of this game:");
        outtextxy(getmaxx() / 2 - 220, getmaxy() / 6 + 20, (char*)"1. Your main goal is to block pieces of your opponent");
        outtextxy(getmaxx() / 2 - 220, getmaxy() / 6 + 40, (char*)"2. Who blocks most of the opponent's pieces - wins");
        outtextxy(getmaxx() / 2 - 220, getmaxy() / 6 + 60,(char*)"3. Game has 2 stages: you put pieces, you move pieces");
        outtextxy(getmaxx() / 2 - 220, getmaxy() / 6 + 80,(char*)"4. You move your pieces only right, or left, or top, or down");
        outtextxy(getmaxx() / 2 - 220, getmaxy() / 6 + 100, (char*)"5. You have only 5 seconds to move your piece otherwise you will loose");


        if(ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            x=mousex();
            y=mousey();
            if ((x >= 15 and x <= 65) and (y >= 15 and y <= 50))
            {
                PlaySound("00171.wav",NULL,SND_FILENAME);
                clearviewport();
                outtextxy(getmaxx() / 2, getmaxy() / 2, (char*)"BYE");
                Sleep(2000);
                exit(1);
            }
            if(x >= 80 and x <= 130 and y >= 15 and y <= 50)
            {
                PlaySound("00171.wav",NULL,SND_FILENAME);
                is_clicked = false;
                settings = false;
                clearviewport();
                return;
            }
        }
    }
}

void setting()
{
    int x,y, xmax = getmaxx(), ymax = getmaxy();
    settings = false;
    clearviewport();
    while(true)
    {
        rectangle(15, 15, 65, 50);
        outtextxy(25,25, (char*)"EXIT");

        rectangle(80, 15, 130, 50);
        outtextxy(88, 25, (char*)"BACK");
        outtextxy(getmaxx() / 2 - 180,getmaxy() / 2 - 200,(char*)"Here you can choose color of pieces and the background");
        readimagefile("qZdz8WL0J4Q.jpg",getmaxx() / 2 - 130,getmaxy() / 2 - 145,getmaxx() / 2 - 70,getmaxy() / 2 - 95);
        readimagefile("ZbZYnRF_Y6E.jpg",getmaxx() / 2 - 30,getmaxy() / 2 - 145,getmaxx() / 2 + 30,getmaxy() / 2 - 95);
         readimagefile("3B8AXPzewO4.jpg",getmaxx() / 2 + 70,getmaxy() / 2 - 145,getmaxx() / 2 + 130,getmaxy() / 2 - 95);

        rectangle(xmax / 2 - 60, ymax / 2 - 50, xmax / 2 - 40, ymax / 2 - 30);
        setfillstyle(SOLID_FILL, color_1);
        circle(xmax / 2, ymax / 2 - 40, 25);
        floodfill(getmaxx() / 2, getmaxy() / 2 - 40, WHITE);
        rectangle(getmaxx() / 2 + 40, getmaxy() / 2 - 50, getmaxx() / 2 + 60, getmaxy() / 2 - 30);
        outtextxy(xmax / 2 - 57, ymax / 2 - 48, (char*)" <");
        outtextxy(xmax / 2 + 44, ymax / 2 - 48, (char*)">");


        rectangle(xmax / 2 - 60, ymax / 2 + 50, xmax / 2 - 40, ymax / 2 + 30);
        setfillstyle(SOLID_FILL, color_2);
        circle(xmax / 2, ymax / 2 + 40, 25);
        floodfill(getmaxx() / 2, getmaxy() / 2 + 40, WHITE);
        rectangle(getmaxx() / 2 + 40, getmaxy() / 2 + 50, getmaxx() / 2 + 60, getmaxy() / 2 + 30);
        outtextxy(xmax / 2 - 57, ymax / 2 + 32, (char*)" <");
        outtextxy(xmax / 2 + 45, ymax / 2 + 32, (char*)">");

        if(ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            x=mousex();
            y=mousey();
            if ((x >= 15 and x <= 65) and (y >= 15 and y <= 50))
            {
                PlaySound("00171.wav",NULL,SND_FILENAME);
                clearviewport();
                outtextxy(getmaxx() / 2, getmaxy() / 2, (char*)"BYE");
                Sleep(2000);
                exit(1);
            }
            if(x >= 80 and x <= 130 and y >= 15 and y <= 50)
            {
                PlaySound("00171.wav",NULL,SND_FILENAME);
                is_clicked = false;
                settings = false;
                clearviewport();
                return;
            }
            if(x >= xmax / 2 - 60 and y >= ymax / 2 - 50 and x <= xmax / 2 - 40 and y <= ymax / 2 - 30)
            {
                PlaySound("00171.wav",NULL,SND_FILENAME);
                if(color_1 > 0)
                    color_1 -= 1;
                if(color_1 == color_2)
                    color_1 -= 2;
            }
            if(x >= getmaxx() / 2 + 40 and y >= getmaxy() / 2 - 50 and x <= getmaxx() / 2 + 60 and  y <= getmaxy() / 2 - 30)
            {
                PlaySound("00171.wav",NULL,SND_FILENAME);
                if (color_1 <= 14)
                    color_1 += 1;
                if(color_1 == color_2)
                    color_1 += 2;
            }
            if(x >= (xmax / 2 - 60) and  y >= (ymax / 2 + 30) and x <= (xmax / 2 - 40) and y <= (ymax / 2 + 50))
            {
                PlaySound("00171.wav",NULL,SND_FILENAME);
                if(color_2 > 0)
                    color_2 -= 1;
                if(color_1 == color_2)
                    color_2 -= 2;
            }
            if( x >= (getmaxx() / 2 + 40) and y >= (getmaxy() / 2 + 30) and x <= (getmaxx() / 2 + 60) and y <= (getmaxy() / 2 + 50))
            {
                PlaySound("00171.wav",NULL,SND_FILENAME);
                if(color_2 <= 14)
                    color_2 += 1;
                if(color_1 == color_2)
                    color_2 += 2;
            }
            if (x >= getmaxx() / 2 - 130 and y >= getmaxy() / 2 - 145 and x <= getmaxx() / 2 - 70 and y <= getmaxy() / 2 - 95)
            {
                PlaySound("00171.wav",NULL,SND_FILENAME);
                background = 1;
            }
            if (x >= getmaxx() / 2 - 30 and y >= getmaxy() / 2 - 145 and x <= getmaxx() / 2 + 30 and y <= getmaxy() / 2 - 95)
            {
                PlaySound("00171.wav",NULL,SND_FILENAME);
                background = 2;
            }
            if(x >= getmaxx() / 2 + 70 and y >= getmaxy() / 2 - 145 and x <= getmaxx() / 2 + 130 and y <= getmaxy() / 2 - 95)
            {
                PlaySound("00171.wav",NULL,SND_FILENAME);
                background = 3;
            }
        }
    }
}

void pvp()
{
    print_table();
    outtextxy(getmaxx() - 180, getmaxy() / 2 + 2, (char*)"It is first player's turn                  ");
    while(count_pieces() != 16 and logic() == 0)
    {
        put_piece();
        if (!fl)
            return;
    }
    while(fl and logic() == 0)
        move_piece();
}

void pvc()
{
    print_table();

    while(count_pieces() < 16 and logic() == 0)
    {
        put_piece();
        if (!placed)
            put_piece_c();
    }
    while(logic() == 0)
    {
        move_piece();
        if(!moved)
            move_piece_c();
    }
}

int main()
{
    int x(1200);
    int y (700);
    initwindow(x,y);
    begining(x, y);

    while(true)
    {
        while(!is_clicked)
            menu(x, y);
        if (settings)
        {
            setting();
            settings = false;
        }
        if (que)
        {
            question();
            que = false;
        }
        if(play or play_com)
            break;
    }
    if(play)
        pvp();
    if(play_com)
        pvc();
    clearviewport();
    PlaySound("zvuk-proigrysha-igroka-v-kompyuternoy-igre.wav",NULL,SND_FILENAME);
    while(true)
        end_game(x, y);

    Sleep(10000);
    getch();
    closegraph();
    return 0;
}
