/* a1f4.c */
/* iis21118 Αποστολία Μαρία Σοφιανοπούλου
   ics21138 Ανδρέας Χατζηαντώνης
   iis21027 Ευστάθιος Ιωσηφίδης
   iis21049 Αικατερίνη Γκουζέλη */

#include <stdio.h>
#include <ctype.h>

#define NumberOfNodes 10
#define NilValue -1

/* Δήλωση Τύπων */

typedef int ListElementType;

typedef int ListPointer;

typedef struct {
    ListElementType Data;
    ListPointer Next;
} NodeType;

typedef enum {
    FALSE, TRUE
} boolean;

/* Δήλωση Συναρτήσεων */

boolean Search(ListPointer FreePtr, ListPointer List, NodeType Nodes[NumberOfNodes], ListElementType Item, ListPointer *PredPtr);
boolean FullList(ListPointer FreePtr);
boolean EmptyList(ListPointer List);
void CreateList(ListPointer *List);
void InitializeStoragePool(NodeType Node[], ListPointer *FreePtr);
void Insert(ListPointer *List, NodeType Node[],ListPointer *FreePtr, ListPointer PredPtr, ListElementType Item);
void GetNode(ListPointer *P, ListPointer *FreePtr, NodeType Node[]);
void printAll(ListPointer List, ListPointer FreePtr, NodeType Node[]);
void TraverseLinked(ListPointer List, NodeType Node[]);

int main()
{
    ListPointer aList, FreePtr, PredPtr;
    NodeType Node[NumberOfNodes];
    boolean flag;
    int i, cho;
    ListElementType AnItem;
    char ch;

    // Ερώτημα A

    InitializeStoragePool(Node, &FreePtr);

    // Ερώτημα B

    CreateList(&aList);

    // Ερώτημα C

    printf ("--------------------Question C--------------------\n");
    printf ("------------------Storage pool---------------------\n");
    printAll(aList, FreePtr, Node);

    //  Ερώτημα D

    printf ("--------------------Question D--------------------\n");
    printf ("------------------Linked list---------------------\n");
    TraverseLinked(aList, Node);

    // Ερώτημα E

    printf ("--------------------Question E--------------------\n");
    do
    {
        printf ("Give a number: ");
        scanf ("%d", &AnItem);
        flag = Search(FreePtr, aList, Node, AnItem, &PredPtr);
        Insert(&aList, Node, &FreePtr, PredPtr, AnItem);
        printf ("\nContinue Y/N: ");
        do
        {
            scanf ("%c", &ch);
        } while (toupper(ch) != 'N' && toupper(ch) != 'Y');
    } while (toupper(ch) != 'N');

    // Ερώτημα F

    printf ("--------------------Question F--------------------\n");
    printf ("------------------Storage pool---------------------\n");
    printAll(aList, FreePtr, Node);

    // Ερώτημα G

    printf ("--------------------Question G--------------------\n");
    printf ("------------------Linked list---------------------\n");
    TraverseLinked(aList, Node);
    // Ερώτημα H

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
    printf ("----------------Search for a number-------------------\n");
    for (i=0; i<2; i++)
    {
        printf ("Give a number: ");
        scanf ("%d", &AnItem);
        flag = Search(FreePtr, aList, Node, AnItem, &PredPtr);

        if(flag)
        {
            printf ("The number is in the list and its predecessor is in position %d\n", PredPtr);
        }
        else 
        {
            printf ("The number is not in the list\n");
        }
    }

    return 0;
}

/* Συναρτήσεις */

boolean Search(ListPointer FreePtr, ListPointer List, NodeType Nodes[NumberOfNodes], ListElementType Item, ListPointer *PredPtr)
{
  boolean stop, flag;
  ListPointer current;

  stop = FALSE;
  flag = FALSE;
  *PredPtr = NilValue;
  
  if(!EmptyList(List))
  {
    current = List;
    while (current != NilValue && !stop) {
      if(Nodes[current].Data >= Item){
      stop = TRUE;
      flag = (Nodes[current].Data == Item);
      }
      else {
      *PredPtr = current;
      current = Nodes[current].Next;
     }
    }
  }
  else
    {flag = FALSE;}

  return flag;
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
        Node[i].Data = -1;
    }
    Node[NumberOfNodes-1].Next = NilValue;
    Node[NumberOfNodes-1].Data = NilValue;
    *FreePtr = 0;
}

void Insert(ListPointer *List, NodeType Node[],ListPointer *FreePtr, ListPointer PredPtr, ListElementType Item)
{
  ListPointer TempPtr;
  
  GetNode(&TempPtr,FreePtr,Node);

  if (!FullList(TempPtr)) {
    if (PredPtr==NilValue)
    {
        Node[TempPtr].Data = Item;
        Node[TempPtr].Next = *List;
        *List = TempPtr;
    }
    else
      {
        Node[TempPtr].Data = Item;
        Node[TempPtr].Next = Node[PredPtr].Next;
        Node[PredPtr].Next = TempPtr;
      }
}
  else
    printf("Full List ...\n");
}

void GetNode(ListPointer *P, ListPointer *FreePtr, NodeType Node[])
{
  *P = *FreePtr;

  if (!FullList(*FreePtr))
    *FreePtr = Node[*FreePtr].Next;
}


boolean EmptyList(ListPointer List)
{
  return (List == NilValue);
}

boolean FullList(ListPointer FreePtr)
{
  return (FreePtr == NilValue);
}

void printAll(ListPointer List, ListPointer FreePtr, NodeType Node[])
{
    int i;

    printf("1o STOIXEIO LISTAS=%d, 1H FREE POSITION=%d\n", List, FreePtr);
    printf("H STORAGE POOL EXEI TA EJHS STOIXEIA\n");
    for (i=0; i<NumberOfNodes; i++)
        printf("(%d: %d->%d) ", i, Node[i].Data, Node[i].Next);
    printf("\n");
}

void TraverseLinked(ListPointer List, NodeType Node[])
{
  ListPointer CurrPtr;

  if (!EmptyList(List))
  {
      CurrPtr =List;
      while (CurrPtr != NilValue)
      {
          printf("(%d: %d->%d) ",CurrPtr,Node[CurrPtr].Data, Node[CurrPtr].Next);
          CurrPtr=Node[CurrPtr].Next;
       }
       printf("\n");
   }
  else printf("Empty List ...\n");
}
