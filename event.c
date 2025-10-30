#include "eventheader.h"
#include "calendarheader.h"
char prev[20]="";
event *CreateEventNode(char *id,char *title,int day,int mon,int year,char *time,char *des)
{
    event *node=NULL;
    node=calloc(1,sizeof(event));
    if(node==NULL)
    {
        printf("Memory allocation failed in CreateEventNode function\n");
        return node;
    }
    //copy the contents into the node
    strcpy(node->event_id,id);
    strcpy(node->title,title);
    node->day=day;
    node->month=mon;
    node->year=year;
    strcpy(node->time,time);
    strcpy(node->desc,des);
    node->next=NULL;
    return node;
}
void GenerateEventID(char *id)
{
    const char charset[]="ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    srand(time(0));
    int i=0;
    id[i]='E';
    i++;
    id[i++]='V';
    for(i=2;i<10;i++)
    {
        id[i]=charset[rand() % (sizeof(charset)-1)];
    }
    id[i]='\0';

}
//ADD EVENT FUCTION TO ADD EVENT TO THE NODE
void AddEvent(event **head)
{
    char id[15],title[100],time[6],desc[200];
    int day,mon,year;
    printf("\n--- Add New Event ---\n");

    //Auto generate event id
    GenerateEventID(id);
    if(strcmp(prev,id)==0)
    {
        GenerateEventID(id);
    }
    strcpy(prev,id);
    printf("Enter Event Title: ");
    getchar();  //clears newline
    fgets(title,sizeof(title),stdin);
    title[strcspn(title,"\n")]='\0';

    printf("Enter Date Formate(DD MM YYYY): ");
    scanf("%d %d %d",&day, &mon,&year);
    if(day<1 || day >31 || mon<1 || mon>12 || year<1900)
    {
        printf("\nInvalid date!\n");
        getchar();
        return;
    }
    getchar(); //clears newline from the scanf


    printf("Enter time (HH:MM) or press enter to skip: ");
    fgets(time,sizeof(time),stdin);
    time[strcspn(time,"\n")]='\0';

        getchar();
   // int c;
   // while ((c = getchar()) != '\n' && c != EOF);

    printf("Enter Description: ");
    fgets(desc,sizeof(desc),stdin);
    desc[strcspn(desc,"\n")]='\0';

    event *newevent=CreateEventNode(id,title,day,mon,year,time,desc);
    if(*head==NULL)
    {
        *head=newevent;

    }
    else
    {
        event *temp=*head;
        while((temp->next)!=NULL)
        {
            temp=temp->next;
        }
        temp->next=newevent;
    }
    printf("\nEvent added successfully with ID: %s\n",id);

}
void DeleteEvent(event **head)
{
    if(*head==NULL)
    {
        printf("no events are there\n");
        return;
    }
    char id[15];
    printf("enter event ID to delete: ");
    scanf("%s",id);

    event *temp=*head;
    event *prev=NULL;
    //if head node is to be deleted
    if(temp!=NULL && strcasecmp(temp->event_id,id)==0)
    {
        *head=temp->next;
        free(temp);
        printf("\n Event deleted successfully\n");
        return;
    }
    //search for a event
    while(temp!=NULL && strcmp(temp->event_id,id)!=0)
    {
        prev=temp;
        temp=temp->next;
    }
    if(temp==NULL)
    {
        printf("Event ID not found\n");
        return;
    }
    prev->next=temp->next;
    free(temp);
    printf("Event Deleted Successfully!\n");
}
void FindEvent(event *head)
{
    if(head==NULL)
    {
        printf("no events are found");
        return;
    }
    int day,mon,year;
    printf("enter date (DD MM YYY): ");
    scanf("%d%d%d",&day,&mon,&year);

    event *temp=head;
    int found=0;

    printf("\n========Events on %02d/%02d/%04d========\n",day,mon,year);

    while(temp!=NULL)
    {
        if(temp->day==day && temp->month==mon && temp->year==year)
        {

            printf("\nEvent ID: %s\n",temp->event_id);
            printf("Title: %s\n",temp->title);
            printf("Description: %s\n",temp->desc);
            printf("DATE: %02d/%02d/%04d\n",temp->day,temp->month,temp->year);
            printf("Time: %s\n",temp->time ? temp->time : "Not specified");
            printf("--------------------------\n");
            found=1;
        }
        temp=temp->next;
    }
    if(!found)
    {
        printf("No events found on this date");
    }
    return;
}
void UpcomingReminders(event *head)
{
    if(head==NULL)
    {
        printf("no events found\n");
        return;
    }
    int days;
    printf("\nShow events for next how many days? ");
    scanf("%d", &days);

    time_t t = time(NULL);
    //struct tm *today = localtime(&t);

    printf("\n========== Upcoming Events ==========\n");
    event *temp = head;
    int found = 0;

    while (temp != NULL)
    {
        struct tm event_date={0};
        event_date.tm_mday=temp->day;
        event_date.tm_mon=temp->month-1;
        event_date.tm_year=temp->year-1900;

        time_t event_time = mktime(&event_date);
        double diff = difftime(event_time, t) / (60 * 60 * 24);

        if (diff >= 0 && diff <= days)
        {
            printf("\n[%d days away]\n", (int)diff);
            printf("Event ID: %s\n", temp->event_id);
            printf("Title: %s\n", temp->title);
            printf("Description: %s\n",temp->desc);
            printf("Date: %02d/%02d/%04d\n", temp->day, temp->month, temp->year);
            printf("Time: %s\n", strlen(temp->time) > 0 ? temp->time : "Not specified");
            printf("--------------------------------\n");
            found=1;
        }
        temp=temp->next;
    }

    if (!found)
    {
        printf("No upcoming events in the next %d days.\n", days);
    }
}
int CompareDates(event *e1, event *e2)
{
    if (e1->year!=e2->year)
    {
        return e1->year-e2->year;
    }
    else if (e1->month!=e2->month)
    {
        return e1->month-e2->month;
    }
    return e1->day-e2->day;
}

void ViewAllEvents(event *head)
{
    if(head==NULL)
    {
        printf("No events are found\n");
        return;
    }
    event *temp=head;
    int cnt=0;
    while(temp!=NULL)
    {
        cnt++;
        temp=temp->next;
    }

    //Creating array of pointers
    event *arr[100];
    temp=head;
    int i=0;
    while(temp!=NULL && i<100)
    {
        arr[i++]=temp;
        temp=temp->next;
    }
    //Bubble sort array
    for(int j=0;j<cnt-1;j++)
    {
        for(int k=0;k<cnt-j-1;k++)
        {
            if(CompareDates(arr[k],arr[k+1])>0)
            {
                event *swap=arr[k];
                arr[k]=arr[k+1];
                arr[k+1]=swap;
            }
        }
     }
    printf("\n========== ALL EVENTS ==========\n");
     for(int j = 0; j < cnt; j++)  // Use array, not linked list
    {
        printf("\n--- Event #%d ---\n",j + 1);
        printf("Event ID: %s\n", arr[j]->event_id);
        printf("Title: %s\n",arr[j]->title);
        printf("Date: %02d/%02d/%04d\n",arr[j]->day,arr[j]->month,arr[j]->year);
        printf("Time: %s\n",strlen(arr[j]->time)>0 ? arr[j]->time:"Not specified");
        printf("Description: %s\n",arr[j]->desc);
        printf("--------------------------\n");
    }
}
void PrintCalendarWithEvents(event *head,int month,int year)
{
    char *mon[]={"January","February","March","April","May","June",
                "July","August","September","October","November","December"};
    int days[]={31,28,31,30,31,30,31,31,30,31,30,31};

    //checking for leap year
    if((year%4==0 && year%100!=0) || (year%400)==0)
    {
        days[1]=29;
    }
    //creating calendar for the year using AddMonthAtEnd function
    cal *calendar=NULL;
    for(int i=0;i<12;i++)
    {
        AddMonthAtEnd(&calendar,mon[i],days[i],i+1);
    }
    //Calculate starting weekdays using CalculateStartday function
    CalculateStartday(calendar,year);

    //Navigate to requested month
    cal *tem=calendar;
    for(int i=1;i<month;i++)
    {
        tem=tem->next;
    }
    //Print the month using PrintMonth function
    if(tem!=NULL)
    {
        PrintMonth(tem);
        //show events for the month;
        printf("\n---- Events in %s %04d ----\n",mon[month-1],year);
        event *temp= head;
        int found=0;
        while(temp!=NULL)
        {
            if(temp->month==month && temp->year==year)
            {
                printf("%02d %02d %04d: %s ",temp->day,temp->month,temp->year,temp->title);
                if (strlen(temp->time) > 0)
                {
                    printf(" at %s", temp->time);
                }
                printf("\n");
                found=1;
            }
            temp=temp->next;
        }
        if(!found)
        {
            printf("No events sceduled!\n");
        }
        //free calendar memory
        cal *ct=calendar;
        while(ct!=NULL)
        {
            cal *next=ct->next;
            free(ct);
            ct=next;
        }

    }

}
event *SyncFile()
{
    FILE *fptr=fopen("eventdata","rb");
    if(fptr==NULL)
    {
        printf("failed to open the file to read content from the file\n");
        return NULL;
    }
    event *head=NULL;
    event *tail=NULL;
    event temp;         //temp event variable
    int cnt=0;

    while(fread(&temp,sizeof(event),1,fptr)==1)
    {
        event*events=CreateEventNode(temp.event_id, temp.title, temp.day,temp.month, temp.year, temp.time,temp.desc);
        if(head==NULL)
        {
            head=events;
            tail=events;
        }
        else
        {
            tail->next=events;
            tail=events;
        }
        cnt++;

    }
    fclose(fptr);
    printf("Backing Up Events from the file\n");
    printf("%d Events are Synced to application\n",cnt);
    return head;
}
void SaveEvents(event *head)
{
    FILE *fptr=fopen("eventdata","wb");
    event *temp=head;
    int cnt=0;
    while(temp!=NULL)
    {
        fwrite(temp,sizeof(event),1,fptr);
        cnt++;
        temp=temp->next;

    }
    fclose(fptr);
    printf("%d events saved to the file\n",cnt);
}
void FreeAllEvents(event *head)
{

    event *nxt=NULL;
    while(head!=NULL)
    {
        nxt=head;
        head=head->next;
        free(nxt);
    }
}
