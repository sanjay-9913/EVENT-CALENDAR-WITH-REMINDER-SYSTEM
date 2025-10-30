#include "calendarheader.h"
void AddMonthAtEnd(cal **head,char *name,int days,int mon_num)
{
    cal *newnode=CreateMonthNode(name,days,mon_num);
    if(newnode==NULL)
    {
        return;
    }
    if(*head==NULL)
    {
        *head=newnode;
        return;
    }
    cal*temp=*head;
    while((temp->next)!=NULL)
    {
        temp=temp->next;
    }
    temp->next=newnode;
}
//Function to create a new node
cal *CreateMonthNode(char *name,int days,int mon_num)
{
    cal *newnode=calloc(1,sizeof(cal));
    if(newnode==NULL)
    {
        printf("Memory allocation failed in CreateMonthNode function\n");
        exit(0);
    }
    //memory alloction is successful then place the parameters into newnode
    strcpy(newnode->name,name);
    newnode->days=days;
    newnode->mon_num=mon_num;
    newnode->start_wday=0; //default starting week day
    newnode->next=NULL;
    return newnode;


}
void CalculateStartday(cal *start,int year)
{
    //calculate the day for january the starting month of the year
    int d1=(year-1)/4;      //calculating leap year count "2024/4=506 leap years"
    int d2=(year-1)/100;    /*not every year divisible by 4 1600,1800 are not leap years "2024/100=20"
                              century boundries subtract these from leap years divided by 4*/


    int d3=(year-1)/400;    //years divided by 400 are leap years


    int daycount=(year+d1-d2+d3)%7;     /* ADD YEAR AND COUNT OF LEAP YEARS - SUBTRACT MIS CALCULATED LEAP YEARS + ACTUAL LEAP CENTURIES
                                           THEN % MODULUS OF 7
                                           (7 DAYS A WEEK) 0 SUNDAY,1 MONDAY, 2 TUESDAY, 3 WEDNESDAY, 4 THURSDAY, 5 FRIDAY, 6 SATURDAY
                                        */
    // creating temp pointer to start default JANUARY
    cal *temp=start;
    if(temp==NULL)
    {
        printf("failed to create temp node in CalulatestartDay function\n");
        return;
    }
    //ASSIGNING DAYCOUNT TO HTE START WEEK DAY
    while(temp!=NULL)
    {
        temp->start_wday=daycount;
        daycount=((daycount)+(temp->days))%7;
        temp=temp->next;
    }
}
//PRINTING CALENDAR
void PrintMonth(cal *month)
{
        int col=0;
    //print month header
    printf("----------%s----------\n",month->name);
    printf("Sun Mon Tue Wed Thu Fri Sat\n");
    //printing spaces until the week start
        for(int day=0;day<month->start_wday;day++)
        {
            printf("    ");
            col++;
        }
        //printing dates starting with the week start
        for(int day=1;day<=month->days;day++)
        {
            printf("%3d ",day);
            col++;
            if(col==7)
            {
                    printf("\n");
                    col=0;
            }
        }
        if(col!=0)
        {
                printf("\n");
        }
}
//PRINTING ENTIRE YEAR CALENDAR
void PrintYear(cal *head,int year)
{
    CalculateStartday(head,year);
    cal *temp=head;
    if(temp==NULL)
    {
        printf("failed to create a temp pointer in PrintYear function\n");
        return;
    }
    while(temp!=NULL)
    {
        PrintMonth(temp);
        temp=temp->next;
    }

}
