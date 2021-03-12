/* iis21118 Αποστολία Μαρία Σοφιανοπούλου
   ics21138 Ανδρέας Χατζηαντώνης
   iis21027 Ευστάθιος Ιωσηφίδης
   iis21049 Αικατερίνη Γκουζέλη */

#include <stdio.h>
#include <stdlib.h>

#define StackLimit 15

typedef int StackElementType;

typedef struct  {
    int Top;
    StackElementType Element[StackLimit];
} StackType;

typedef enum {
    FALSE, TRUE
} boolean;

void CreateStack(StackType *Stack);
boolean EmptyStack(StackType Stack);
boolean FullStack(StackType Stack);
void Push(StackType *Stack, StackElementType Item);
void Pop(StackType *Stack, StackElementType *Item);

void TraverseStack(StackType Stack);

int main () {

    StackType Stack,TempStack;
    StackElementType n, x, Temp;

    CreateStack(&Stack);

    for(StackElementType i=0;i<StackLimit;i++)
        Push(&Stack, i*10);

    TraverseStack(Stack);
    printf("Give nth element (n<=6) ");
    scanf("%d",&n);
    printf("\n");

    //a
    Pop(&Stack, &x);
    Pop(&Stack, &x);
    printf("Question a: x=%d",x);
    TraverseStack(Stack);
    printf("\n");

    //b
    Pop(&Stack, &Temp);
    Pop(&Stack, &x);
    Push(&Stack, x);
    Push(&Stack, Temp);

    printf("Question b: x=%d",x);
    TraverseStack(Stack);
    printf("\n");

    //c
    for(StackElementType i=0;i<n;i++)
        Pop(&Stack,&x);
    printf("Question c: x=%d",x);
    TraverseStack(Stack);
    printf("\n");

    //d
    CreateStack(&TempStack);
    for(StackElementType i=0;i<n;i++){
        Pop(&Stack, &x);
        Push(&TempStack, x);
    }
    printf("Question d: x=%d",x);

    while(!(EmptyStack(TempStack))){
        Pop(&TempStack, &Temp);
        Push(&Stack, Temp);
    }
    TraverseStack(Stack);
    printf("\n");

    //e
    while(!EmptyStack(Stack)){

        Pop(&Stack,&x);
        Push(&TempStack,x);
    }
    printf("Question e: x=%d",x);

    while(!EmptyStack(TempStack)){

        Pop(&TempStack,&Temp);
        Push(&Stack,Temp);
    }
    TraverseStack(Stack);
    printf("\n");

    //f
    while(Stack.Top >=2){
        Pop(&Stack,&x);
        Push(&TempStack,x);
    }
    printf("Question f: x=%d",x);

    while(!EmptyStack(TempStack)){
        Pop(&TempStack,&x);
        Push(&Stack,x);
    }
    TraverseStack(Stack);
    printf("\n");

    //g
    while(!EmptyStack(Stack)){
        Pop(&Stack,&x);
    }

    printf("Question g: x=%d",x);
    TraverseStack(Stack);

return 0;
}

void CreateStack(StackType *Stack)
/* Λειτουργία: Δημιουργεί μια κενή στοίβα.
   Επιστρέφει: Κενή Στοίβα.*
*/
{
    Stack -> Top = -1;
   // (*Stack).Top = -1;
}

boolean EmptyStack(StackType Stack)
/* Δέχεται: Μια στοίβα Stack.
   Λειτουργία: Ελέγχει αν η στοίβα Stack είναι κενή.
   Επιστρέφει: True αν η Stack είναι κενή, False διαφορετικά
*/
{
    return (Stack.Top == -1);
}

boolean FullStack(StackType Stack)
/* Δέχεται: Μια στοίβα Stack.
   Λειτουργία: Ελέγχει αν η στοίβα Stack είναι γεμάτη.
   Επιστρέφει: True αν η Stack είναι γεμάτη, False διαφορετικά
*/
{
    return (Stack.Top == (StackLimit - 1));
}

void Push(StackType *Stack, StackElementType Item)
/* Δέχεται: Μια στοίβα Stack και ένα στοιχείο Item.
   Λειτουργία: Εισάγει το στοιχείο Item στην στοίβα Stack αν η Stack δεν είναι γεμάτη.
   Επιστρέφει: Την τροποποιημένη Stack.
   Έξοδος: Μήνυμα γεμάτης στοίβας, αν η στοίβα Stack είναι γεμάτη
*/
{
    if (!FullStack(*Stack)) {
        Stack -> Top++;
        Stack -> Element[Stack -> Top] = Item;
    } else
        printf("Full Stack...");
}

void Pop(StackType *Stack, StackElementType *Item)
/* Δέχεται: Μια στοίβα Stack.
   Λειτουργία: Διαγράφει το στοιχείο Item από την κορυφή της Στοίβας αν η Στοίβα δεν είναι κενή.
   Επιστρέφει: Το στοιχείο Item και την τροποποιημένη Stack.
   Έξοδος:  Μήνυμα κενής στοίβας αν η Stack είναι κενή
*/
{
    if (!EmptyStack(*Stack)) {
        *Item = Stack -> Element[Stack -> Top];
        Stack -> Top--;
    } else
        printf("Empty Stack...");
}

void TraverseStack(StackType Stack)
{
    int i;
    printf("\nplithos sto stack %d\n",Stack.Top+1);
    for (i=0;i<=Stack.Top;i++) {
        printf("%d ",Stack.Element[i]);
    }
    printf("\n");
}
