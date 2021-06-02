/* a26f5.c */
/* iis21118 Αποστολία Μαρία Σοφιανοπούλου
   ics21138 Ανδρέας Χατζηαντώνης
   iis21027 Ευστάθιος Ιωσηφίδης
   iis21049 Αικατερίνη Γκουζέλη */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

//Δήλωση Τύπων

typedef struct
{
    int code;
    int recNo;
}BinTreeElementType;

typedef struct BinTreeNode *BinTreePointer;

typedef struct BinTreeNode
{
    BinTreeElementType Data;
    BinTreePointer LChild, RChild;
} BinTreeNode;

typedef enum
{
    FALSE, TRUE
} boolean;

typedef struct
{
    int code;
    char surname[20];
    char name[20];
    char sex;
    int year;
    float grade;
}StudentT;

// Δήλωση Συναρτήσεων

int BuildBST(BinTreePointer *Root);
boolean BSTEmpty(BinTreePointer Root);
void PrintStudent(int recNum);
void writeNewStudents(BinTreePointer *Root, int *size);
void CreateBST(BinTreePointer *Root);
void RecBSTInsert(BinTreePointer *Root, BinTreeElementType Item);
void RecBSTSearch(BinTreePointer Root, BinTreeElementType KeyValue, boolean *Found, BinTreePointer *LocPtr);
void RecBSTDelete(BinTreePointer *Root, BinTreeElementType KeyValue);
void RecBSTInorder(BinTreePointer Root);
void RecBSTPreorder(BinTreePointer Root);
void RecBSTPostorder(BinTreePointer Root);
void printStudentsWithGrade(float theGrade);

int main()
{
    BinTreePointer ARoot, LocPtr;
    int size;   // πλήθος κόμβων του ΔΔΑ
    StudentT student;
    boolean found;
    float theGrade;

    //1
    printf("Q1. Build BST from a file\n");
    size=BuildBST(&ARoot);

    //2
    printf("Q2. Print size and BST\n");
    printf("Size=%d\n", size);
    printf("Nodes of BST\n");
    RecBSTInorder(ARoot); // Εμφάνιση των κόμβων (σε αύξουσα διάταξη)
    printf("\n");

    //3
    printf("Q3. Write new students, update file and BST\n");
    writeNewStudents(&ARoot, &size);

    //4
    printf("Q4. Print size and BST\n");
    printf("Size=%d", size);
    printf("Nodes of BST\n");
    RecBSTInorder(ARoot); // Εμφάνιση των κόμβων του δέντρου (σε αύξουσα διάταξη)
    printf("\n");

    //5
    printf("Q5. Search for a student\n");
    printf("Give student's code?");
    scanf("%d", &LocPtr->Data.recNo);
    RecBSTSearch(ARoot, LocPtr->Data, &found, &LocPtr);    //******************************
    if(found)
        PrintStudent(LocPtr->Data.recNo);
    else
        printf("Student with AM %d wasn't found", LocPtr->Data.recNo);

    //6
    printf("Q6. Print size and BST\n");
    printf("Size=%d\n", size);
    printf("Nodes of BST\n");
    RecBSTInorder(ARoot); // Εμφάνιση των κόμβων του δέντρου (σε αύξουσα διάταξη)
    printf("\n");

    //7
    printf("Q7. Print students with grades>=given grade\n");
    printf("Give the grade: ");
    scanf("%f", &theGrade);
    printStudentsWithGrade(theGrade);

    return 0;
}

int BuildBST(BinTreePointer *Root)
{
    FILE *fp;
    int nscan;
    char termch;
    StudentT student; // εγγραφή για την ανάγνωση των στοιχείων φοιτητή απο το αρχείο
    BinTreeElementType indexRec; // εγγραφή για το ΔΔΑ
    int size; // πλήθος εγγραφών φοιτητή

    CreateBST(&(*Root));

    fp=fopen("foitites.dat", "r");
    size=0;
    if(fp!=NULL)
    {
        while(TRUE)
        {
            nscan=fscanf(fp, "%d, %20[^,], %20[^,], %c, %d, %f%c", &student.code, student.name, student.surname, &student.sex, &student.year, &student.grade, &termch);
            if(nscan==EOF) break;
            if(nscan!=7 || termch!='\n')
                printf("Error\n");
            else
            {
                indexRec.code=student.code;
                indexRec.recNo=size;
                RecBSTInsert(&(*Root), indexRec);
                size++;
            }
        }
    }
    else printf("Problem opening file");

    fclose(fp);
    return size;
}

void PrintStudent(int recNum)
{
    FILE *fp;
    int nscan;
    char termch;
    StudentT student;
    // BinTreeElementType indexRec;
    int lines;

    fp=fopen("foitites.dat", "r");
    lines=0;
    if(fp!=NULL)
    {
        while(lines<=recNum)
        {
            nscan=fscanf(fp, "%d, %20[^,], %20[^,], %c, %d, %f%c", &student.code, student.name, student.surname, &student.sex, &student.year, &student.grade, &termch);
            if(nscan==EOF) break;
            if(nscan!=7 || termch!='\n')
                printf("Error\n");
            lines++;
        }
        if(lines==recNum+1)
            printf("%d,%s,%s,%c,%d,%f\n", student.code, student.name, student.surname, student.sex, student.year, student.grade);
    }
    fclose(fp);
}

void writeNewStudents(BinTreePointer *Root, int *size)
{
    FILE *fp;
    StudentT student;
    BinTreeElementType indexRec;
    boolean found;
    BinTreePointer LocPtr;
    char ch;

    fp=fopen("foitites.dat", "a");
    if(fp!=NULL)
    {
        do{
            printf("Give student's AM? ");
            scanf("%d", &indexRec.code);
            RecBSTSearch(*Root, indexRec, &found, &LocPtr);
            if(!found)
            {
                 student.code=indexRec.code;
                 printf("Give student surname? "); // ������� �������
                 scanf("%s",student.surname); getchar(); // �������, ��� &
                 printf("Give student name? "); // ������� �����
                 scanf("%s",student.name); getchar() ;
                 printf("Give student sex F/M? "); // ������� ����
                 scanf("%s",&student.sex); getchar();
                 printf("Give student's registration year? "); // ������� ����
                 scanf("%d",&student.year);
                 printf("Give student's grade? "); // ������� �����
                 scanf("%f",&student.grade);
                 
                 indexRec.code = student.code;
                 indexRec.recNo = *size;
                 
                 RecBSTInsert(Root, indexRec);
                 fprintf(fp,"%d,%s,%s,%c,%d,%f\n",student.code,student.name, student.surname,student.sex,student.year,student.grade);
                 (*size)++;
                 printf("Size=%d\n",*size);
            }
            else printf("Student with AM %d already exists\n", indexRec.code);
            printf("Continue Y/N: ");
            do // ������������
            {
                
                scanf("%c", &ch); // ������� ��� ��������� ch
            } while (toupper(ch)!= 'N' && toupper(ch)!= 'Y'); // ��� � ���������� ��� ����� N � �

         }while (toupper(ch)!='N'); // ��� � ���������� ��� ����� �


        fclose(fp); // ������ �� ������

    }

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
        if (Item.code < (*Root)->Data.code)
            RecBSTInsert(&(*Root) ->LChild,Item);
        else if (Item.code > (*Root) ->Data.code)
            RecBSTInsert(&(*Root) ->RChild,Item);
        else
            printf("TO STOIXEIO EINAI HDH STO DDA\n");
}

void RecBSTSearch(BinTreePointer Root, BinTreeElementType KeyValue, boolean *Found, BinTreePointer *LocPtr)
{
    if (BSTEmpty(Root))
        *Found=FALSE;
    else
        if (KeyValue.code < Root->Data.code)
            RecBSTSearch(Root->LChild, KeyValue, &(*Found), &(*LocPtr));
        else
            if (KeyValue.code > Root->Data.code)
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

    if (BSTEmpty(*Root))          //* ����� ������ �� KeyValue �� �� ������ *)
        printf("TO STOIXEIO DEN BRE8HKE STO DDA\n");
     else
         //* ��������� ���������� ��� ����� ��� �������� ��� ���� KeyValue ��� �������� ���
          if (KeyValue.code < (*Root)->Data.code)
             RecBSTDelete(&((*Root)->LChild), KeyValue);       //* �������� ��������� *
          else
            if (KeyValue.code > (*Root)->Data.code)
                  RecBSTDelete(&((*Root)->RChild), KeyValue);   //* ����  ��������� *
            else                                       //* TO KeyValue ������� �������� ��� ������ *)
                if ((*Root)->LChild ==NULL)
                 {
                      TempPtr = *Root;
                      *Root = (*Root)->RChild;      //* ��� ���� �������� ����� *)
                      free(TempPtr);
                 }
                else if ((*Root)->RChild == NULL)
                   {
                        TempPtr = *Root;
                        *Root = (*Root)->LChild;      //* ���� �������� �����, ���� ��� ���� *)
                        free(TempPtr);
                   }
                   else                               //* ���� 2 ������ *)
                   {
                        //* ������ ��� INORDER �������� ��� *)
                        TempPtr = (*Root)->RChild;
                        while (TempPtr->LChild != NULL)
                              TempPtr = TempPtr->LChild;
                        /* ���������� ��� �������� ��� ����� ��� ����������
                        ��� ���������� ��� �������� ��� �������� ������ */
                        (*Root)->Data = TempPtr->Data;
                        RecBSTDelete(&((*Root)->RChild), (*Root)->Data);
                   }
}

void RecBSTInorder(BinTreePointer Root)
{
    if (Root!=NULL)
    {
        RecBSTInorder(Root->LChild);
        printf("(%d %d),",Root->Data.code,Root->Data.recNo);
        RecBSTInorder(Root->RChild);
    }
}

void RecBSTPreorder(BinTreePointer Root)
{
    if (Root!=NULL)
    {
        printf("%d ",Root->Data.code);
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
        printf("%d ",Root->Data.code);
    }
}

void printStudentsWithGrade(float theGrade)
{
    FILE *fp;
    int nscan;
    char termch;
    StudentT student;

    fp=fopen("foitites.dat", "r");
    if(fp!=NULL)
    {
        while(TRUE)
        {
            nscan=fscanf(fp, "%d, %20[^,], %20[^,], %c, %d, %f%c", &student.code, student.name, student.surname, &student.sex, &student.year, &student.grade, &termch);
            if(nscan==EOF) break;
            if(nscan!=7 || termch!='\n')
                printf("Error\n");
            else if(student.grade>=theGrade)
                printf("%d,%s,%s,%c,%d,%.1f\n", student.code, student.name, student.surname, student.sex, student.year, student.grade);
        }
    }

    fclose(fp);
}
