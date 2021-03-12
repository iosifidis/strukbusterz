/* iis21118 Αποστολία Μαρία Σοφιανοπούλου
   ics21138 Ανδρέας Χατζηαντώνης
   iis21027 Ευστάθιος Ιωσηφίδης
   iis21049 Αικατερίνη Γκουζέλη */


#include <stdio.h>
#include <stdlib.h>

#define StackLimit 60

/* Δήλωση Τύπων */
typedef struct {
    int price;
    char size;
} StackElementType;

typedef struct {
    int Top;
    StackElementType Elements[StackLimit];
} StackType;

typedef enum {
    FALSE, TRUE
} boolean;

/* Δήλωση Συναρτήσεων */
void CreateStack(StackType *Stack);
boolean EmptyStack(StackType Stack);
boolean FullStack(StackType Stack);
void Push(StackType *Stack, StackElementType Item);
void Pop(StackType *Stack, StackElementType *Item);
void TraverseStack(StackType Stack);

/* Main */

int main()
{
    /* Δήλωση Μεταβλητών */
    
    int n, i;
    char size;
    boolean flag;
    StackElementType AnItem;
    StackType itemsStack, tempStack;
    
    CreateStack (&itemsStack);
    CreateStack (&tempStack);
    
    /* Question 1 */
    
    printf ("Give number of items ");
    scanf ("%d", &n);
    
    /* Question 2 */
    
    printf ("Give the items to store\n");
    for (i=0; i<n; i++)
    {
        printf ("Give price ");
        scanf ("%d", &AnItem.price);
        getchar();
        printf ("Give size ");
        scanf ("%c", &AnItem.size);
        getchar();
        Push(&itemsStack, AnItem);
    }
    
    /* Question 3 */
    
    printf ("Items in the box\n");
    TraverseStack(itemsStack);
    
    /* Question 4 */
    
    printf ("What size do you want? ");
    scanf ("%c", &size);
    getchar();
    flag = FALSE;
    
    while (!EmptyStack(itemsStack)) {
        Pop(&itemsStack, &AnItem);
        if (AnItem.size == size)
        {
            flag = TRUE;
        }
        else
        {
            Push(&tempStack, AnItem);
        }
    }
    
    if (flag == TRUE)
        printf("Found the size %c\n\n", size);
    else
        printf("Not Found the size %c\n\n", size);
    
    /* Question 5 */
    
    printf ("Items in the box\n");
    TraverseStack(itemsStack);
    
    printf ("Items out of the box\n");
    TraverseStack(tempStack);
    
    return 0;
}

/* Συναρτήσεις*/

void CreateStack(StackType *Stack)
{
    Stack -> Top = -1;
}

boolean EmptyStack(StackType Stack)
{
    return (Stack.Top == -1);
}

boolean FullStack(StackType Stack)
{
    return (Stack.Top == (StackLimit - 1));
}

void Push(StackType *Stack, StackElementType Item)
{
    if (!FullStack(*Stack)) {
        Stack -> Top++;
        Stack -> Elements[Stack -> Top] = Item;
    } else
        printf("Full Stack...");
}

void Pop(StackType *Stack, StackElementType *Item)
{
    if (!EmptyStack(*Stack)) {
        *Item = Stack -> Elements[Stack -> Top];
        Stack -> Top--;
    } else
        printf("Empty Stack...");
}

void TraverseStack(StackType Stack)
{
    int i;
    printf("plithos sto stack %d\n",Stack.Top+1);
    for (i=0;i<=Stack.Top;i++) {
        printf("%c,%d\n",Stack.Elements[i].size,Stack.Elements[i].price);
    }
    printf("\n");
}
