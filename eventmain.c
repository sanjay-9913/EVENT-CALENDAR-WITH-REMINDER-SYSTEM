#include "eventheader.h"
#include "calendarheader.h"
int main()
{
    event *eventlist=NULL;
    eventlist=SyncFile();
    char choice;
    printf("=======EVENT CALENDER MENU=======\n");

    while(1)
    {
        printf("\n-----------MENU------------\n");
        printf("a/A: Add a new event\nd/D: Delete an event\nf/F: Find events on specific date\nu/U: Upcoming event reminders\n");
        printf("v/V: View all saved events\np/P: Display calendar with Events in a month/year\nl/L: Sync events from file\ns/S: Save all events to a file\nq/Q: Exit from application\n");
        printf("--------------------------------\n");
        //asing the user for a choice
        printf("enter your choice: ");
        scanf(" %c",&choice);

        switch(choice)
        {
            case 'a':
            case 'A':
                    AddEvent(&eventlist);
                    break;
            case 'd':
            case 'D':
                    DeleteEvent(&eventlist);
                    break;
            case 'f':
            case 'F':
                    FindEvent(eventlist);
                    break;
            case 'u':
            case 'U':
                    UpcomingReminders(eventlist);
                    break;
            case 'v':
            case 'V':
                    ViewAllEvents(eventlist);
                    break;
            case 'p':
            case 'P':
                {
                    int mon,year;
                    printf("\nEnter month (1-12): ");
                    scanf("%d",&mon);
                    printf("Enter year: ");
                    scanf("%d",&year);
                    if (mon<1 || mon>12)
                    {
                        printf("Invalid month!\n");
                        break;
                    }
                    PrintCalendarWithEvents(eventlist,mon,year);
                }
                    break;
            case 's':
            case 'S': SaveEvents(eventlist);
                    break;
            case 'l':
            case 'L':printf("syncing events from file...");
                    FreeAllEvents(eventlist);
                    eventlist=SyncFile();
                    break;
            case 'q':
            case 'Q':
                    printf("Do you want to Save the Events before Exiting? (y/n): ");
                    char ch;
                    scanf(" %c",&ch);
                    if(ch=='y' || ch=='Y')
                    {
                        SaveEvents(eventlist);
                    }
                    printf("\nExiting... Goodbye!\n");
                    FreeAllEvents(eventlist);
                    exit(0);

            default:
                    printf("Invalid Choice...Plese try again\n");



        }
    }

}
