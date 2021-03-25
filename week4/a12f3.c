/* a12f3.c */
/* iis21118 Αποστολία Μαρία Σοφιανοπούλου
   ics21138 Ανδρέας Χατζηαντώνης
   iis21027 Ευστάθιος Ιωσηφίδης
   iis21049 Αικατερίνη Γκουζέλη */

#include <stdio.h>
#define QueueLimit 4

typedef struct {
    int ArrivalTime;
    int WaitingTime;
    int StartTime;
    int EndTime;
} QueueElementType;

typedef struct {
	int Front, Rear;
	QueueElementType Element[QueueLimit];;
} QueueType;

typedef enum {FALSE, TRUE} boolean;

void ReadCustomer(QueueType *Queue);
QueueType TimesInQueue(QueueType *Queue);
void TraverseQ(char prompt[],QueueType Queue);

void CreateQ(QueueType *Queue);
boolean EmptyQ(QueueType Queue);
boolean FullQ(QueueType Queue);
void RemoveQ(QueueType *Queue, QueueElementType *Item);
void AddQ(QueueType *Queue, QueueElementType Item);

int main()
{
    int i;
    QueueType WaitingQueue, ServiceQueue;

    CreateQ(&WaitingQueue);
    CreateQ(&ServiceQueue);
    for(i=1;i<QueueLimit;i++)
    {
        printf("Give: arival time,stay time for client %d: ",i);
        ReadCustomer(&WaitingQueue);
    }

    TraverseQ("Waiting Queue", WaitingQueue);
    printf("\n");

    ServiceQueue=TimesInQueue(&WaitingQueue);

    TraverseQ("Waiting Queue", WaitingQueue);
    TraverseQ("Service Queue", ServiceQueue);

    return 0;
}

//Question 1
void ReadCustomer(QueueType *Queue)
{
    QueueElementType tmpCustomer;
    scanf("%d,%d", &tmpCustomer.ArrivalTime,&tmpCustomer.WaitingTime);
    tmpCustomer.StartTime=tmpCustomer.EndTime=-1;
    AddQ(&(*Queue),tmpCustomer);
}

//Question 2
QueueType TimesInQueue(QueueType *Queue)
{
    int earlierStart=0; // ������ ������� ������������
    int currentStart=0; // ��� ������� ������������ ��� �������� ������
    int currentEnd=0; // ��� ����� ������������ ��� �������� ������

    QueueType QueueServiced;
    QueueElementType CurrentCust;

    CreateQ(&QueueServiced);
    while(!EmptyQ(*Queue))
    {
        RemoveQ(Queue, &CurrentCust);
        if(CurrentCust.ArrivalTime>earlierStart)
            currentStart=CurrentCust.ArrivalTime;
        else
            currentStart=earlierStart;

        currentEnd=currentStart+CurrentCust.WaitingTime;
        earlierStart=currentEnd;

        CurrentCust.StartTime=currentStart;
        CurrentCust.EndTime=currentEnd;

        AddQ(&QueueServiced, CurrentCust);
    }

    return QueueServiced;
}

//Question 3
void TraverseQ(char prompt[],QueueType Queue)
{
    int current;
    int i=1;

    if(!EmptyQ(Queue))
    {
            printf("%s\n", prompt);
            current=Queue.Front;
            printf("Client \t\tStart\tEnd\tArrival\tStay\n");

            while(current!=Queue.Rear)
            {
                printf("Client %-d \t%-d\t%-d\t%-d\t%-d\n", i, Queue.Element[current].StartTime, Queue.Element[current].EndTime, Queue.Element[current].ArrivalTime, Queue.Element[current].WaitingTime);
                current=(current+1)%QueueLimit;
                i++;
            }
    }
    else printf("%s is empty\n", prompt);
}

void CreateQ(QueueType *Queue)
/*  ����������:  ���������� ��� ���� ����.
    ����������:  ���� ����
*/
{
	Queue->Front = 0;
	Queue->Rear = 0;
}

boolean EmptyQ(QueueType Queue)
/* �������:    ��� ����.
   ����������: ������� �� � ���� ����� ����.
   ����������: True �� � ���� ����� ����, False �����������
*/
{
	return (Queue.Front == Queue.Rear);
}

boolean FullQ(QueueType Queue)
/* �������:    ��� ����.
   ����������: ������� �� � ���� ����� ������.
   ����������: True �� � ���� ����� ������, False �����������
*/
{
	return ((Queue.Front) == ((Queue.Rear +1) % QueueLimit));
}

void RemoveQ(QueueType *Queue, QueueElementType *Item)
/* �������:    ��� ����.
   ����������: ������� �� �������� Item ��� ��� ������ ���� ��� �����
                �� � ���� ��� ����� ����.
   ����������: �� �������� Item ��� ��� ������������� ����.
   ������:     ������ ����� ���� �� � ���� ����� ����
*/
{
	if(!EmptyQ(*Queue))
	{
		*Item = Queue ->Element[Queue -> Front];
		Queue ->Front  = (Queue ->Front + 1) % QueueLimit;
	}
	else
		printf("Empty Queue");
}

void AddQ(QueueType *Queue, QueueElementType Item)
/* �������:    ��� ���� Queue ��� ��� �������� Item.
   ����������: ��������� �� �������� Item ���� ���� Queue
                �� � ���� ��� ����� ������.
   ����������: ��� ������������� ����.
   ������:     ������ ������� ����� �� � ���� ����� ������
*/
{
	if(!FullQ(*Queue))
	{
		Queue ->Element[Queue ->Rear] = Item;
		Queue ->Rear = (Queue ->Rear + 1) % QueueLimit; ;
	}
	else
		printf("Full Queue");
}
