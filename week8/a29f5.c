/* a29f5.c */
/* iis21118 Αποστολία Μαρία Σοφιανοπούλου
   ics21138 Ανδρέας Χατζηαντώνης
   iis21027 Ευστάθιος Ιωσηφίδης
   iis21049 Αικατερίνη Γκουζέλη */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct{
    int AMKA;
    int afm;
    int age;
} BinTreeElementType;

typedef struct BinTreeNode *BinTreePointer;
 struct BinTreeNode {
    BinTreeElementType Data;
    BinTreePointer LChild, RChild;
} ;

typedef enum {
    FALSE, TRUE
} boolean;

void CreateBST(BinTreePointer *Root);
boolean EmptyBST(BinTreePointer Root);
void BSTInsert(BinTreePointer *Root, BinTreeElementType Item);
void BSTSearch(BinTreePointer Root, BinTreeElementType KeyValue, boolean *Found, BinTreePointer *LocPtr);
void InorderTraversal(BinTreePointer Root);

int main()
{
    BinTreePointer Root1, Root2, LocPtr;
    BinTreeElementType person;
    boolean found;
    char ch;
    int i;

    CreateBST(&Root1);
    CreateBST(&Root2);

    do
    {
     printf("Give AMKA? ");
     scanf("%d", &person.AMKA);
     printf("Give AFM? ");
     scanf("%d", &person.afm);
     printf("Give age? ");
     scanf("%d", &person.age);
    
     if(person.AMKA<=60){
        BSTInsert(&Root1, person);
     }
     else{
        BSTInsert(&Root2, person);
     }
     printf("\nContinue Y/N: ");
     
     do
       {
       scanf("%c", &ch);
       } while (toupper(ch)!= 'N' && toupper(ch)!= 'Y');
       
       } while (toupper(ch)!='N');

    printf("\nPeople with age less-equal 60\n");
    InorderTraversal(Root1);
    printf("\n");
    printf("\nPeople with age greater than 60\n");
    InorderTraversal(Root2);
    printf("\n");
    for(i=0;i<3;i++)
    {
     printf("Give AMKA: ");
     scanf("%d", &person.AMKA);
     printf("Give age: ");
     scanf("%d", &person.age);

    if(person.age<=60)
    {
        BSTSearch(Root1, person, &found, &LocPtr);
    }
    else
    {
        BSTSearch(Root2, person, &found, &LocPtr);
    }
    if(found)
    {
        if(person.age==LocPtr->Data.age)
        {
            printf("The person with AMKA %d, AFM %d and age %d is in the catalogue\n",LocPtr->Data.AMKA,LocPtr->Data.afm,LocPtr->Data.age);
        }
        else{
            printf("The person with AMKA %d has age %d different from the person you are looking for\n",LocPtr->Data.AMKA,LocPtr->Data.age);
        }
    }

    else{
        printf("The person with AMKA %d and age %d is Unknown\n",person.AMKA,person.age);
    }
    }

    printf("\n");
    return 0;
}

void CreateBST(BinTreePointer *Root)
/* Λειτουργία: Δημιουργεί ένα κενό ΔΔΑ.
   Επιστρέφει:  Τον μηδενικό δείκτη(NULL) Root
*/
{
    *Root = NULL;
}

boolean EmptyBST(BinTreePointer Root)
/* Δέχεται:   Ενα ΔΔα με το Root να δείχνει στη ρίζα του.
  Λειτουργία: Ελέγχει αν το ΔΔΑ είναι κενό.
  Επιστρέφει: TRUE αν το ΔΔΑ είναι κενό και FALSE διαφορετικά
*/
{   return (Root==NULL);
}

void BSTInsert(BinTreePointer *Root, BinTreeElementType Item)
/* Δέχεται:     Ένα ΔΔΑ με το δείκτη Root να δείχνει στη ρίζα του και ένα στοιχείο Item.
   Λειτουργία:  Εισάγει το στοιχείο Item στο ΔΔΑ.
   Επιστρέφει: Το τροποποιημένο ΔΔΑ με τον δείκτη Root να δείχνει στη ρίζα του
*/
{
    BinTreePointer LocPtr, Parent;
    boolean Found;

    LocPtr = *Root;
    Parent = NULL;
    Found = FALSE;
    while (!Found && LocPtr != NULL) {
        Parent = LocPtr;
        if (Item.AMKA < LocPtr->Data.AMKA)
            LocPtr = LocPtr ->LChild;
        else if (Item.AMKA > LocPtr ->Data.AMKA)
            LocPtr = LocPtr ->RChild;
        else
            Found = TRUE;
    }
    if (Found)
        printf("To %d EINAI HDH STO DDA\n", Item.AMKA);
    else {
        LocPtr = (BinTreePointer)malloc(sizeof (struct BinTreeNode));
        LocPtr ->Data = Item;
        LocPtr ->LChild = NULL;
        LocPtr ->RChild = NULL;
        if (Parent == NULL)
            *Root = LocPtr;
        else if (Item.AMKA < Parent ->Data.AMKA)
            Parent ->LChild = LocPtr;
        else
            Parent ->RChild = LocPtr;
    }
}


void BSTSearch(BinTreePointer Root, BinTreeElementType KeyValue, boolean *Found, BinTreePointer *LocPtr)
/* Δέχεται:    Ένα ΔΔΑ με το δείκτη Root να δείχνει στη ρίζα του και μια τιμή KeyValue.
   Λειτουργία: Αναζητά στο ΔΔΑ έναν κόμβο με τιμή KeyValue στο πεδίο κλειδί του.
   Επιστρέφει: Η Found έχει τιμή TRUE και ο δείκτης LocPtr δείχνει στον κόμβο που
                περιέχει την τιμή KeyValue, αν η αναζήτηση είναι επιτυχής.
                Διαφορετικά η Found έχει τιμή FALSE
*/
{
    boolean stop;

    *LocPtr = Root;
    stop = FALSE;
    while (!stop && *LocPtr != NULL)
    {
        if (KeyValue.AMKA < (*LocPtr)->Data.AMKA)
            *LocPtr = (*LocPtr)->LChild;
        else
            if (KeyValue.AMKA > (*LocPtr)->Data.AMKA)
                *LocPtr = (*LocPtr)->RChild;
            else stop = TRUE;
    }
   *Found=stop;
}

void InorderTraversal(BinTreePointer Root)
/* Δέχεται:    Ένα δυαδικό δέντρο με το δείκτη Root να δείχνει στην ρίζα του.
   Λειτουργία: Εκτελεί ενδοδιατεταγμένη διάσχιση του δυαδικού δέντρου και
                επεξεργάζεται κάθε κόμβο ακριβώς μια φορά.
   Εμφανίζει: Το περιεχόμενο του κόμβου, και εξαρτάται από το είδος της επεξεργασίας
*/
{
    if (Root!=NULL) {
        InorderTraversal(Root->LChild);
        printf("(%d, %d, %d)",Root->Data.AMKA,Root->Data.afm,Root->Data.age);
        InorderTraversal(Root->RChild);
    }
}

