/* a25f5.c */
/* iis21118 Αποστολία Μαρία Σοφιανοπούλου
   ics21138 Ανδρέας Χατζηαντώνης
   iis21027 Ευστάθιος Ιωσηφίδης
   iis21049 Αικατερίνη Γκουζέλη */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Δήλωση τύπων
typedef int BinTreeElementType;             /*ο τύπος των στοιχείων του ΔΔΑ
                                                ενδεικτικά τύπου int */
typedef struct BinTreeNode *BinTreePointer;
typedef struct BinTreeNode {
    BinTreeElementType Data;
    BinTreePointer LChild, RChild;
} BinTreeNode;

typedef enum {
    FALSE, TRUE
} boolean;

// Δήλωση συναρτήσεων

void CreateBST(BinTreePointer *Root);
boolean BSTEmpty(BinTreePointer Root);
void RecBSTInsert(BinTreePointer *Root, BinTreeElementType Item);
void RecBSTSearch(BinTreePointer Root, BinTreeElementType KeyValue, boolean *Found, BinTreePointer *LocPtr);
void RecBSTDelete(BinTreePointer *Root, BinTreeElementType KeyValue);
void RecBSTInorder(BinTreePointer Root);
void RecBSTPreorder(BinTreePointer Root);
void RecBSTPostorder(BinTreePointer Root);
int CountLeaves(BinTreePointer Root);


int main()
{
    // Δήλωση μεταβλητών
    
    BinTreePointer ARoot;
    BinTreeElementType Item;
    char ch;
    int fylla;

    CreateBST(&ARoot); // Δημιουργία ΔΔΑ

    do // Επαναληπτικά
    {
     printf("Enter a number for insertion in the Tree: ");
     scanf("%d", &Item); // Διάβασε τον αριθμό
     RecBSTInsert(&ARoot,Item); // Εισαγωγή του αριθμού στο ΔΔΑ


     printf("Continue Y/N: "); // Ερώτηση για εισαγωγή και άλλων αριθμών
     
     do // Επαναληπτικά
       {
       scanf("%c", &ch); // Διάβασε τον χαρακτήρα ch
       } while (toupper(ch)!= 'N' && toupper(ch)!= 'Y'); // όσο ο χαρακτήρας δεν είναι N ή Υ
       
       } while (toupper(ch)!='N'); // όσο ο χαρακτήρας δεν είναι Ν

    printf("Elements of BST\n");
    RecBSTInorder(ARoot); // Εμφάνιση των στοιχείων του ΔΔΑ (σε αύξουσα διάταξη)
        
    fylla=CountLeaves(ARoot); // Καλούμε την συνάρτηση CountLeaves
    printf("\nNumber of leaves %d\n",fylla); // Εμφάνιση του πλήθους των φύλλων
    return 0;
}

// Συναρτήσεις

int CountLeaves(BinTreePointer Root)
{
   

    if(Root==NULL) // Αν το ΔΔΑ είναι κενό
        {return 0;} // Επέστρεψε 0
    if (Root->LChild==NULL && Root->RChild==NULL) // Αν ο κόμβος είναι φύλλο
        {return 1;} // Επέστρεψε 1

     // Επέστρεψε το άθροισμα της Countleaves για το αριστερό και το δεξί υποδέντρο
     return CountLeaves(Root->LChild)+CountLeaves(Root->RChild);
}



void CreateBST(BinTreePointer *Root)
{
    *Root = NULL;
}

boolean BSTEmpty(BinTreePointer Root)
{
    return (Root==NULL);
}

void RecBSTInsert(BinTreePointer *Root, BinTreeElementType Item)
{
    if (BSTEmpty(*Root)) {
        (*Root) = (BinTreePointer)malloc(sizeof (struct BinTreeNode));
        (*Root) ->Data = Item;
        (*Root) ->LChild = NULL;
        (*Root) ->RChild = NULL;
    }
    else
        if (Item < (*Root) ->Data)
            RecBSTInsert(&(*Root) ->LChild,Item);
        else if (Item > (*Root) ->Data)
            RecBSTInsert(&(*Root) ->RChild,Item);
        else
            printf("TO STOIXEIO EINAI HDH STO DDA\n");
}

void RecBSTSearch(BinTreePointer Root, BinTreeElementType KeyValue, boolean *Found, BinTreePointer *LocPtr)
{
    if (BSTEmpty(Root))
        *Found=FALSE;
    else
        if (KeyValue < Root->Data)
            RecBSTSearch(Root->LChild, KeyValue, &(*Found), &(*LocPtr));
        else
            if (KeyValue > Root->Data)
                RecBSTSearch(Root->RChild, KeyValue, &(*Found), &(*LocPtr));
            else
                {
                    *Found = TRUE;
                    *LocPtr=Root;
                }
}

void RecBSTDelete(BinTreePointer *Root, BinTreeElementType KeyValue)
{

   BinTreePointer TempPtr;          //* true AN TO STOIXEIO KeyValue EINAI STOIXEIO TOY DDA *)

    if (BSTEmpty(*Root))          //* ΑΔΕΙΟ ΔΕΝΔΡΟ ΤΟ KeyValue ΔΕ ΘΑ ΒΡΕΘΕΙ *)
        printf("TO STOIXEIO DEN BRE8HKE STO DDA\n");
     else
         //* αναζήτησε αναδρομικά τον κόμβο που περιέχει την τιμή KeyValue και διάγραψέ τον
          if (KeyValue < (*Root)->Data)
             RecBSTDelete(&((*Root)->LChild), KeyValue);       //* ΑΡΙΣΤΕΡΟ ΥΠΟΔΕΝΔΡΟ *
          else
            if (KeyValue > (*Root)->Data)
                  RecBSTDelete(&((*Root)->RChild), KeyValue);   //* ΔΕΞΙ  ΥΠΟΔΕΝΔΡΟ *
            else                                       //* TO KeyValue ΒΡΕΘΗΚΕ ΔΙΑΓΡΑΦΗ ΤΟΥ ΚΟΜΒΟΥ *)
                if ((*Root)->LChild ==NULL)
                 {
                      TempPtr = *Root;
                      *Root = (*Root)->RChild;      //* ΔΕΝ ΕΧΕΙ ΑΡΙΣΤΕΡΟ ΠΑΙΔΙ *)
                      free(TempPtr);
                 }
                else if ((*Root)->RChild == NULL)
                   {
                        TempPtr = *Root;
                        *Root = (*Root)->LChild;      //* ΕΧΕΙ ΑΡΙΣΤΕΡΟ ΠΑΙΔΙ, ΑΛΛΑ ΟΧΙ ΔΕΞΙ *)
                        free(TempPtr);
                   }
                   else                               //* ΕΧΕΙ 2 ΠΑΙΔΙΑ *)
                   {
                        //* ΕΥΡΕΣΗ ΤΟΥ INORDER ΑΠΟΓΟΝΟΥ ΤΟΥ *)
                        TempPtr = (*Root)->RChild;
                        while (TempPtr->LChild != NULL)
                              TempPtr = TempPtr->LChild;
                        /* ΜΕΤΑΚΙΝΗΣΗ ΤΟΥ ΑΠΟΓΟΝΟΥ ΤΗς ΡΙΖΑΣ ΤΟΥ ΥΠΟΔΕΝΔΡΟΥ
                        ΠΟΥ ΕΞΕΤΑΖΕΤΑΙ ΚΑΙ ΔΙΑΓΡΑΦΗ ΤΟΥ ΑΠΟΓΟΝΟΥ ΚΟΜΒΟΥ */
                        (*Root)->Data = TempPtr->Data;
                        RecBSTDelete(&((*Root)->RChild), (*Root)->Data);
                   }
}

void RecBSTInorder(BinTreePointer Root)
{
    if (Root!=NULL) 
    {
        RecBSTInorder(Root->LChild);
        printf("%d ",Root->Data);
        RecBSTInorder(Root->RChild);
    }
}

void RecBSTPreorder(BinTreePointer Root)
{
    if (Root!=NULL) 
    {
        printf("%d ",Root->Data);
        RecBSTPreorder(Root->LChild);
        RecBSTPreorder(Root->RChild);
    }
}

void RecBSTPostorder(BinTreePointer Root)
{
    if (Root!=NULL) 
    {
        RecBSTPostorder(Root->LChild);
        RecBSTPostorder(Root->RChild);
        printf("%d ",Root->Data);
    }
}