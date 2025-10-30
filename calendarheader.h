#ifndef CALENDAR_H
#define CALENDAR_H

#include <stdio.h>
#include<string.h>
#include <stdlib.h>


//STRUCTURE DEFINITION
typedef struct calendar
{
        char name[20];
        int days;
        int start_wday;
        int mon_num;
        struct calendar *next;
}cal;

//FUCTION DECLARATIONS
cal *CreateMonthNode(char *name,int days,int mon_num);
void AddMonthAtEnd(cal **head,char *name,int days,int mon_num);
void CalculateStartday(cal *start,int year);
void PrintMonth(cal *month);
void PrintYear(cal *head,int year);

#endif