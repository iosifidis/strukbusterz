/* a30f4.c */
/* iis21118 Αποστολία Μαρία Σοφιανοπούλου
   ics21138 Ανδρέας Χατζηαντώνης
   iis21027 Ευστάθιος Ιωσηφίδης
   iis21049 Αικατερίνη Γκουζέλη */

#include <stdio.h>

#define NumberOfNodes 10
#define NilValue -1
#define StackLimit 20

/* Δήλωση Τύπων */

typedef struct
{
    int AM;
    float Grade;
} ListElementType;

typedef int ListPointer;

typedef struct 
{
    ListElementType Data;
    ListPointer Next;
} NodeType;

typedef enum
{
    FALSE, TRUE
} boolean;

typedef int StackElementType;

typedef struct 
{
    int Top;
    StackElementType Element[StackLimit];
} StackType;

/* Δήλωση Συναρτήσεων */

float FindMins(ListPointer List, NodeType Node[NumberOfNodes], StackType *Stack);
boolean FullList(ListPointer FreePtr);
boolean EmptyList(ListPointer List);
boolean FullStack(StackType Stack);
boolean EmptyStack(StackType Stack);
void CreateList(ListPointer *List);
void InitializeStoragePool(NodeType Node[], ListPointer *FreePtr);
void Insert(ListPointer *List, NodeType Node[],ListPointer *FreePtr, ListPointer PredPtr, ListElementType Item);
void GetNode(ListPointer *P, ListPointer *FreePtr, NodeType Node[]);
void printAll(ListPointer List, ListPointer FreePtr, NodeType Node[]);
void TraverseLinked(ListPointer List, NodeType Node[]);
void CreateStack(StackType *Stack);
void Push(StackType *Stack, StackElementType Item);
void Pop(StackType *Stack, StackElementType *Item);
void TraverseStack(StackType Stack);

int main()
{
    int w_i=0;
    float mn;
    NodeType Node[NumberOfNodes];
    ListPointer aList, FreePtr, PredPtr;
    ListElementType AnItem;
    StackElementType am;
    StackType Stack;

    PredPtr = NilValue;

    // Ερώτημα A

    InitializeStoragePool(Node, &FreePtr);

    // Ερώτημα Β

    CreateList(&aList);

    // Ερώτημα C

    printf ("--------------------Question C--------------------\n");
    printf ("-------------------Storage pool-------------------\n");

    printAll(aList, FreePtr, Node);

    // Ερώτημα D

    printf ("--------------------Question D--------------------\n");
    printf ("-------------------Linked list-------------------\n");

    TraverseLinked(aList, Node);

    // Ερώτημα E

    printf ("--------------------Question E--------------------\n");

    for (w_i=0; w_i<5; w_i++)
    {
        printf ("DWSE AM GIA EISAGVGH STH LISTA: ");
        scanf("%d", &AnItem.AM);
        printf ("DWSE VATHMO GIA EISAGWGH STH LISTA: ");
        scanf("%f", &AnItem.Grade);
        Insert(&aList, Node, &FreePtr, PredPtr, AnItem);
    }

    // Ερώτημα F

    printf ("--------------------Question F--------------------\n");
    printf ("-------------------Storage pool-------------------\n");

    printAll(aList, FreePtr, Node);

    // Ερώτημα G

    printf ("--------------------Question G--------------------\n");
    printf ("-------------------Linked list-------------------\n");

    TraverseLinked(aList, Node);

    // Ερώτημα Η

    printf ("--------------------Question H--------------------\n");

    if (EmptyList(aList))
    {
        printf ("Empty List\n");
    }
    else 
    {
        printf ("Not an Empty List\n");
    }

    // Ερώτημα I

    printf ("--------------------Question I--------------------\n");

    if (FullList(FreePtr))
    {
        printf ("Full List\n");
    }
    else 
    {
        printf ("Not a Full List\n");
    }

    // Ερώτημα J

    printf ("--------------------Question J--------------------\n");

    mn = FindMins(aList, Node, &Stack);
    printf ("Min value=%.1f\n", mn);
    printf ("AM with min grade are: ");

    while (!EmptyStack(Stack))
    {
        Pop(&Stack, &am);
        printf ("%d ", am);
    }

    // Ερώτημα K

    printf ("\n--------------------Question K--------------------\n");

    TraverseStack(Stack);

    // Ερώτημα L

    printf ("--------------------Question L--------------------\n");
    printf ("-------------------Storage pool-------------------\n");

    printAll(aList, FreePtr, Node);

    // Ερώτημα M

    printf ("--------------------Question M--------------------\n");
    printf ("-------------------Linked list-------------------\n");

    TraverseLinked(aList, Node);


    return 0;
}

// Συναρτήσεις

float FindMins(ListPointer List, NodeType Node[NumberOfNodes], StackType *Stack)
{
    ListPointer CurrentPtr;
    float min;
    StackElementType Itm, StdAM;

    CreateStack(Stack);
    if (!EmptyList(List))
    {
        CurrentPtr = List;
        min = Node[CurrentPtr].Data.Grade;

        while (CurrentPtr != NilValue)
        {
            if (Node[CurrentPtr].Data.Grade <= min)
            {
                if (Node[CurrentPtr].Data.Grade < min)
                {
                    while (!EmptyStack(*Stack))
                    {
                        Pop(&(*Stack), &Itm);
                    }
                    min = Node[CurrentPtr].Data.Grade;
                }
                StdAM = Node[CurrentPtr].Data.AM;
                Push(&(*Stack), StdAM);
            }
            CurrentPtr = Node[CurrentPtr].Next;
        }
    }
    else 
    {
        printf ("Empty List...");
    }

    return min;
}

boolean FullList(ListPointer FreePtr)
{
    return (FreePtr == NilValue);
}

boolean EmptyList(ListPointer List)
{
    return (List == NilValue);
}

boolean FullStack(StackType Stack)
{
    return (Stack.Top == (StackLimit - 1));
}

boolean EmptyStack(StackType Stack)
{
    return (Stack.Top == -1);
}

void CreateList(ListPointer *List)
{
    *List = NilValue;
}

void InitializeStoragePool(NodeType Node[], ListPointer *FreePtr)
{
    int i;

    for (i=0; i<NumberOfNodes-1; i++)
    {
        Node[i].Next = i+1;
        Node[i].Data.AM = -1;
        Node[i].Data.Grade = -1.0;
    }
    
    Node[NumberOfNodes-1].Next = NilValue;
    Node[NumberOfNodes-1].Data.AM = NilValue;
    Node[NumberOfNodes-1].Data.Grade = -1.0;
    *FreePtr = 0;
}

void Insert(ListPointer *List, NodeType Node[],ListPointer *FreePtr, ListPointer PredPtr, ListElementType Item)
{
    ListPointer TempPtr;
    GetNode(&TempPtr,FreePtr,Node);
    if (!FullList(TempPtr)) 
    {
      if (PredPtr==NilValue)
      {
          Node[TempPtr].Data =Item;
          Node[TempPtr].Next =*List;
          *List =TempPtr;
      }
      else
        {
          Node[TempPtr].Data =Item;
          Node[TempPtr].Next =Node[PredPtr].Next;
          Node[PredPtr].Next =TempPtr;
        }
    }
    else
      printf("Full List ...\n");
}

void GetNode(ListPointer *P, ListPointer *FreePtr, NodeType Node[])
{
    *P = *FreePtr;
    if (!FullList(*FreePtr))
    {
        *FreePtr = Node[*FreePtr].Next;
    }
}

void printAll(ListPointer List, ListPointer FreePtr, NodeType Node[])
{
    int i;

    printf ("1o STOIXEIO LISTAS=%d, 1H FREE POSITION=%d\n", List, FreePtr);
    printf ("H STORAGE POOL EXEI TA EJHS STOIXEIA\n");

    for (i=0; i<NumberOfNodes; i++)
    {
        printf ("(%d:<%d,%.1f> ->%d) ", i, Node[i].Data.AM, Node[i].Data.Grade, Node[i].Next);
    }
    printf ("\n");
}

void TraverseLinked(ListPointer List, NodeType Node[])
{
    ListPointer CurrentPtr;

    if (!EmptyList(List))
    {
        CurrentPtr = List;

        while (CurrentPtr != NilValue)
        {
            printf ("(%d:<%d,%.1f> ->%d) ", CurrentPtr, Node[CurrentPtr].Data.AM, Node[CurrentPtr].Data.Grade, Node[CurrentPtr].Next);
            CurrentPtr = Node[CurrentPtr].Next;
        }
        printf ("\n");
    }
    else 
    {
        printf ("Empty List...\n");
    }
}

void CreateStack(StackType *Stack)
{
    Stack -> Top = -1;
}

void Push(StackType *Stack, StackElementType Item)
{
    if (!FullStack(*Stack))
    {
        Stack -> Top++;
        Stack -> Element[Stack -> Top] = Item;
    }
    else 
    {
        printf ("Full Stack...");
    }
}

void Pop(StackType *Stack, StackElementType *Item)
{
    if (!EmptyStack(*Stack))
    {
        *Item = Stack -> Element[Stack -> Top];
        Stack -> Top--;
    }
    else 
    {
        printf("Empty Stack..");
    }
}

void TraverseStack(StackType Stack)
{
    int i;

    printf ("\nplithos sto stack %d\n", Stack.Top+1);
    for (i=0; i<=Stack.Top; i++)
    {
        printf ("%d ", Stack.Element[i]);
    }
    printf ("\n");
}
