#ifndef EVENT_H
#define EVENT_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct Eventdetails
{
        char event_id[15];
        char title[100];
        int day;
        int month;
        int year;
        char time[6];
        char desc[200];
        struct Eventdetails*next;
}event;
event *CreateEventNode(char *id,char *title,int day,int mon,int year,char *time,char *des);
void GenerateEventID(char *id);
void AddEvent(event **head);
void DeleteEvent(event **head);
void FindEvent(event *head);
void UpcomingReminders(event *head);
void ViewAllEvents(event *head);
int CompareDates(event *e1, event *e2);
void PrintCalendarWithEvents(event *head,int month,int year);
event *SyncFile();
void SaveEvents(event *head);
void FreeAllEvents(event *head);
#endif
