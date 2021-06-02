/* a30f5.c */
/* iis21118 Αποστολία Μαρία Σοφιανοπούλου
   ics21138 Ανδρέας Χατζηαντώνης
   iis21027 Ευστάθιος Ιωσηφίδης
   iis21049 Αικατερίνη Γκουζέλη */

#include <stdio.h>
#include <ctype.h>

#define HMax 5              /*     �� ������� ��� ������ HashTable ���������� ��� �� 5 */

#define VMax 30             /*�� ������� ��� ������, ���������� ��� �� 30 */

#define EndOfList -1        /* ������ ��� ����������� �� ����� ��� ������
                                ��� ��� ���� ��������� ��������� */

typedef struct{
    char name[20];
    int amount;
} ListElementType;

typedef int KeyType;

typedef struct {
	KeyType RecKey;
	ListElementType Data;
	int Link;
} ListElm;

typedef struct  {
	int HashTable[HMax];
    int Size;
	int SubListPtr;
    int StackPtr;
	ListElm List[VMax];
} HashListType;

typedef enum {
    FALSE, TRUE
} boolean;

void CreateHashList(HashListType *HList);
int HashKey(KeyType Key);
boolean FullHashList(HashListType HList);
void SearchSynonymList(HashListType HList,KeyType KeyArg,int *Loc,int *Pred);
void SearchHashList(HashListType HList,KeyType KeyArg,int *Loc,int *Pred);
void AddRec(HashListType *HList,ListElm InRec);
void DeleteRec(HashListType *HList,KeyType DelKey);
void PrintListOfSynonyms(HashListType HList, KeyType key);
void Print_HashList(HashListType HList);
void PrintPinakes(HashListType HList);

int main()
{

    char ch;
    HashListType HList;
    ListElm AnItem;
    KeyType AKey;
    int Loc, Pred;

    //1
    printf("1. Create HashList\n");
    CreateHashList(&HList);
    Print_HashList(HList);
    PrintPinakes(HList);

    //2
    printf("2. Insert new member\n");
    do
    {
        printf("Give code: ");
        scanf("%d", &AnItem.RecKey); //diavazw ton kwdiko toy pelath
        printf("Give name: ");
        scanf("%s", AnItem.Data.name); getchar(); //onoma pelath
        printf("Give amount: ");
        scanf("%d", &AnItem.Data.amount); //xrwstoumeno poso
        AddRec(&HList, AnItem);

        printf("\nContinue Y/N: ");
        do{
            scanf("%c", &ch);
        } while (toupper(ch)!= 'N' && toupper(ch)!= 'Y');
    } while (toupper(ch)!='N');
    Print_HashList(HList);
    PrintPinakes(HList);

    //3
    printf("3. Search for a member\n");
    do
    {
        printf("Give code: ");
        scanf("%d", &AnItem.RecKey); //diavazw ton kwdiko toy pelath
        SearchHashList(HList, AnItem.RecKey, &Loc, &Pred);
        if(Loc!=EndOfList)
            printf("[%d, %s, %d, %d]\n", HList.List[Loc].RecKey, HList.List[Loc].Data.name, HList.List[Loc].Data.amount, HList.List[Loc].Link);
        else
            printf("DEN YPARXEI EGGRAFH ME KLEIDI %d\n", AnItem.RecKey);
        printf("\nContinue Y/N: ");
        do{
            scanf("%c", &ch);
        } while (toupper(ch)!= 'N' && toupper(ch)!= 'Y');
    } while (toupper(ch)!='N');

    //4
    printf("4. Update member amount\n");
    do
    {
        printf("Give code: ");
        scanf("%d", &AnItem.RecKey);
        SearchHashList(HList, AnItem.RecKey, &Loc, &Pred);
        if(Loc!=EndOfList)
        {
            printf("[%d, %s, %d, %d]\n", HList.List[Loc].RecKey, HList.List[Loc].Data.name, HList.List[Loc].Data.amount, HList.List[Loc].Link);
            printf("Give amount: ");
            scanf("%d", &AKey);
            if(HList.List[Loc].Data.amount>=AKey)
                HList.List[Loc].Data.amount-=AKey;
        }
        else
            printf("DEN YPARXEI EGGRAFH ME KLEIDI %d\n", AnItem.RecKey);
        printf("\nContinue Y/N: ");
        do{
            scanf("%c", &ch);
        } while (toupper(ch)!= 'N' && toupper(ch)!= 'Y');
    } while (toupper(ch)!='N');

    Print_HashList(HList);
    PrintPinakes(HList);

    //5
    printf("5. Delete a member\n");
    do
    {
        printf("Give code: ");
        scanf("%d", &AnItem.RecKey);
        SearchHashList(HList, AnItem.RecKey, &Loc, &Pred);
        if(Loc!=EndOfList)
        {
            if(HList.List[Loc].Data.amount==0)
                DeleteRec(&HList, AnItem.RecKey);
            else
                printf("Not deleted arrange amount\n");
        }
        else
            printf("DEN YPARXEI EGGRAFH ME KLEIDI %d\n", AnItem.RecKey);

        printf("\nContinue Y/N: ");
        do{
            scanf("%c", &ch);
        } while (toupper(ch)!= 'N' && toupper(ch)!= 'Y');
    } while (toupper(ch)!='N');
    Print_HashList(HList);
    PrintPinakes(HList);

    //6
    printf("6. Print list of synonyms\n");
    do
    {
        printf("Give code: ");
        scanf("%d", &AnItem.RecKey);
        SearchHashList(HList, AnItem.RecKey, &Loc, &Pred);
        if(Loc!=EndOfList)
        {
            printf("[%d, %s, %d, %d]\n", HList.List[Loc].RecKey, HList.List[Loc].Data.name, HList.List[Loc].Data.amount, HList.List[Loc].Link);
            PrintListOfSynonyms(HList, AnItem.RecKey);
        }
        else
            printf("DEN YPARXEI EGGRAFH ME KLEIDI %d\n", AnItem.RecKey);
        printf("\nContinue Y/N: ");
        do{
            scanf("%c", &ch);
        } while (toupper(ch)!= 'N' && toupper(ch)!= 'Y');
    } while (toupper(ch)!='N');

    return 0;
}

int HashKey(KeyType Key)
/* �������:    ��� ���� Key ���� ��������.
   ����������: ������� ��� ���� ��������������� HValue ��� �� ������ Key.
   ����������: ��� ���� ��������������� HValue
*/
{
	/*�� ��������� ��� �� KeyType ��� ����� ��������
	�� ������ �� ������������ ��������� �� ������ �� ������*/
	return Key%HMax;
}

void CreateHashList(HashListType *HList)
/* ����������: ���������� ��� ���� HList.
   ����������: ��� ���� HList
*/
{
	int index;

	HList->Size=0;           //���������� ��� ���� �����
	HList->StackPtr=0;       //������� ��� ������ ��� ������� ��� ��������� ������

    /*����������� ��� ������ HashTable ��� ����� HList ���� ���� ��������� ���
        �� ���� �� ���� EndOfList (-1)*/
    index=0;
	while (index<HMax)
	{
		HList->HashTable[index]=EndOfList;
		index=index+1;
    }

     //���������� ��� ������� ��� ��������� ������ ��� ����� HList
    index=0;
	while(index < VMax-1)
	{
		HList->List[index].Link=index+1;
		index=index+1;
	}
	HList->List[index].Link=EndOfList;
}

boolean FullHashList(HashListType HList)
/* �������:    ��� ���� HList.
   ����������: ������� �� � ����� List ��� ����� HList ����� ������.
   ����������: TRUE �� � ����� List ����� ������, FALSE �����������.
*/
{
	return(HList.Size==VMax);
}

void SearchSynonymList(HashListType HList,KeyType KeyArg,int *Loc,int *Pred)
/* �������:     ��� ���� HList ��� ��� ���� �������� KeyArg.
    ����������: ������� ��� ������� �� ������ KeyArg ���� �������� ���������.
    ����������: �� ���� Loc ��� �������� ��� �� ���� Pred ��� ������������
                �������� ���� ��������
*/
{
	int Next;
	Next=HList.SubListPtr;
	*Loc=-1;
	*Pred=-1;
	while(Next!=EndOfList)
	{
		if (HList.List[Next].RecKey==KeyArg)
		{
			*Loc=Next;
			Next=EndOfList;
		}
		else
		{
			*Pred=Next;
			Next=HList.List[Next].Link;
		}
	}
}
void SearchHashList(HashListType HList,KeyType KeyArg,int *Loc,int *Pred)
/* �������:     ��� ���� HList ��� ��� ���� �������� KeyArg.
    ����������: ������� ��� ������� �� ������ KeyArg ��� ���� HList.
    ����������: �� ���� Loc ��� �������� ��� �� ���� Pred ���
                ������������ �������� ��� ��������� ���� ����� ������.
                �� ��� ������� ������� �� ������ KeyArg ���� Loc=Pred=-1
*/
{
	int HVal;
	HVal=HashKey(KeyArg);
    if (HList.HashTable[HVal]==EndOfList)
	{
		*Pred=-1;
		*Loc=-1;
	}
	else
	{
		HList.SubListPtr=HList.HashTable[HVal];
		SearchSynonymList(HList,KeyArg,Loc,Pred);
	}
}

void AddRec(HashListType *HList,ListElm InRec)
/* �������:    ��� ���� HList ��� ��� ������� InRec.
   ����������: ������� ��� ������� InRec ��� ����� List, �� ��� ����� ������,
                ��� ���������� �� ���� HList.
   ����������: ��� ������������� ���� HList.
   ������:     ������ ������� ������, �� � List ����� ������, �����������,
                �� ������� ��� ������� �� �� ���� ������,
                �������� ����������� ���������
*/
{
	int Loc, Pred, New, HVal;

   // New=0;
	if(!(FullHashList(*HList)))
	{
		Loc=-1;
		Pred=-1;
		SearchHashList(*HList,InRec.RecKey,&Loc,&Pred);
		if(Loc==-1)
		{
			HList->Size=HList->Size +1;
			New=HList->StackPtr;
			HList->StackPtr=HList->List[New].Link;
			HList->List[New]=InRec;
			if (Pred==-1)
			{
			    HVal=HashKey(InRec.RecKey);
                HList->HashTable[HVal]=New;
				HList->List[New].Link=EndOfList;
			}
			else
			{
                HList->List[New].Link=HList->List[Pred].Link;
				HList->List[Pred].Link=New;
			}
		}

		else
		{
			printf("YPARXEI HDH EGGRAFH ME TO IDIO KLEIDI \n");
		}
	}
	else
	{
		printf("Full list...");
	}
}
void DeleteRec(HashListType *HList,KeyType DelKey)
/* DEXETAI:    TH DOMH (HList) KAI To KLEIDI (DelKey) THS EGGRAFHS
               POY PROKEITAI NA DIAGRAFEI
   LEITOYRGIA: DIAGRAFEI, THN EGGRAFH ME KLEIDI (DelKey) APO TH
               LISTA (List), AN YPARXEI ENHMERWNEI THN DOMH HList
   EPISTREFEI: THN TROPOPOIHMENH DOMH (HList)
   EJODOS:     "DEN YPARXEI EGGRAFH ME KLEIDI" MHNYMA
*/
{
	int Loc, Pred, HVal;

	SearchHashList(*HList,DelKey,&Loc,&Pred);
	if(Loc!=-1)
	{
		if(Pred!=-1)
		{
			HList->List[Pred].Link=HList->List[Loc].Link;
		}
		else
		{
			HVal=HashKey(DelKey);
		    HList->HashTable[HVal]=HList->List[Loc].Link;
		}
		HList->List[Loc].Link=HList->StackPtr;
		HList->StackPtr=Loc;
		HList->Size=HList->Size -1;
	}
	else
	{
		printf("DEN YPARXEI  EGGRAFH ME KLEIDI %d\n",DelKey);
	}
}

void Print_HashList(HashListType HList)
{
   int i, SubIndex;

     printf("HASHLIST STRUCTURE with SYNONYM CHAINING\n");
     printf("========================================\n");

          printf("PINAKAS DEIKTWN STIS YPO-LISTES SYNWNYMWN EGGRAFWN:\n");
            for (i=0; i<HMax;i++)
                printf("%d| %d\n",i,HList.HashTable[i]);


          printf("OI YPO-LISTES TWN SYNWNYMWN EGGRAFWN:\n");
          for (i=0; i<HMax;i++)
          {
              SubIndex = HList.HashTable[i];
              while ( SubIndex != EndOfList )
              {
                   printf("[%d, %s, %d, %d]",HList.List[SubIndex].RecKey,HList.List[SubIndex].Data.name,HList.List[SubIndex].Data.amount,HList.List[SubIndex].Link);
                   printf(" -> ");
                   SubIndex = HList.List[SubIndex].Link;
               }
              printf("TELOS %dHS YPO-LISTAS\n", i);
          }

          printf("MEGE8OS THS LISTAS = %d\n", HList.Size);
          printf("========================================\n");
}

void PrintListOfSynonyms(HashListType HList, KeyType key)
{
    KeyType Hval, SubIndex;

    Hval=HashKey(key);

    SubIndex=HList.HashTable[Hval];
    while(SubIndex!=EndOfList) //NOT SURE
    {
        printf("%d: [%d, %s, %d]\n",SubIndex,HList.List[SubIndex].RecKey,HList.List[SubIndex].Data.name,HList.List[SubIndex].Data.amount);
        SubIndex=HList.List[SubIndex].Link;
    }
}

void PrintPinakes(HashListType HList)
{
    int i;
	printf("Hash table\n");
	for (i=0; i<HMax;i++)
              printf("%d| %d\n",i,HList.HashTable[i]);

	printf("Hash List\n");
    for (i=0;i<HList.Size;i++)
        printf("%d) %d, %s, %d, %d\n",i,HList.List[i].RecKey,HList.List[i].Data.name,HList.List[i].Data.amount,HList.List[i].Link);

	printf("\n");
}
