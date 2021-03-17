/* iis21118 Αποστολία Μαρία Σοφιανοπούλου
 ics21138 Ανδρέας Χατζηαντώνης
 iis21027 Ευστάθιος Ιωσηφίδης
 iis21049 Αικατερίνη Γκουζέλη */

#include <stdio.h>
#include <stdlib.h>

#define StackLimit 50

typedef char StackElementType;

typedef struct  {
    int Top;
    StackElementType Element[StackLimit];
} StackType;

typedef enum {
    FALSE, TRUE
} boolean;

void CreateStack(StackType *Stack);
void Push(StackType *Stack, StackElementType Item);
void Pop(StackType *Stack, StackElementType *Item);
boolean FullStack(StackType Stack);
boolean EmptyStack(StackType Stack);

int main()
{
    StackType Stack;
    StackElementType Item, ch;
    boolean flag, valid;

    flag=FALSE;
    valid=TRUE;
    CreateStack(&Stack);

    printf("Enter string:\n");
    scanf("%c", &ch); getchar();
    if(ch=='#') return 0;
    while(ch!='#' && valid)
    {
        if(!flag){
            if(ch=='C')
            {
                flag=TRUE;
                scanf("%c", &ch); getchar();
            }
            else
            {
                Push(&Stack, ch);
                scanf("%c", &ch); getchar();
            }
        }
        else{
            if(!EmptyStack(Stack))
            {
                Pop(&Stack, &Item);
                if(Item!=ch) valid=FALSE;
                else {scanf("%c", &ch); getchar();}
            }
            else valid=FALSE;
        }
    }

    if(valid && EmptyStack(Stack)) printf("TRUE");
    else printf("FALSE");

    return 0;
    system("PAUSE");
}

void CreateStack(StackType *Stack)
/* ����������: ���������� ��� ���� ������.
   ����������: ���� ������.*
*/
{
    Stack -> Top = -1;
   // (*Stack).Top = -1;
}

void Push(StackType *Stack, StackElementType Item)
/* �������: ��� ������ Stack ��� ��� �������� Item.
   ����������: ������� �� �������� Item ���� ������ Stack �� � Stack ��� ����� ������.
   ����������: ��� ������������� Stack.
   ������: ������ ������� �������, �� � ������ Stack ����� ������
*/
{
    if (!FullStack(*Stack)) {
        Stack -> Top++;
        Stack -> Element[Stack -> Top] = Item;
    } else
        printf("Full Stack...");
}

void Pop(StackType *Stack, StackElementType *Item)
/* �������: ��� ������ Stack.
   ����������: ��������� �� �������� Item ��� ��� ������ ��� ������� �� � ������ ��� ����� ����.
   ����������: �� �������� Item ��� ��� ������������� Stack.
   ������:  ������ ����� ������� �� � Stack ����� ����
*/
{
    if (!EmptyStack(*Stack)) {
        *Item = Stack -> Element[Stack -> Top];
        Stack -> Top--;
    } else
        printf("Empty Stack...");
}

boolean EmptyStack(StackType Stack)
/* �������: ��� ������ Stack.
   ����������: ������� �� � ������ Stack ����� ����.
   ����������: True �� � Stack ����� ����, False �����������
*/
{
    return (Stack.Top == -1);
}

boolean FullStack(StackType Stack)
/* �������: ��� ������ Stack.
   ����������: ������� �� � ������ Stack ����� ������.
   ����������: True �� � Stack ����� ������, False �����������
*/
{
    return (Stack.Top == (StackLimit - 1));
}

