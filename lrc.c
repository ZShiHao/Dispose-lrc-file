#include <stdio.h>
#include <stdlib.h>

/* List node stores lyric in b[] and time(ms) in Time. */
typedef struct line{
	char b[100];
	int Time;
	struct line *Next;
}Line;

typedef Line* LinePosition;

void CreateList(LinePosition L,FILE* fp1);
int ListLength(LinePosition L);
int Repetition(char* a);
void BubbleSort(LinePosition L,int k);
void WriteTxt(LinePosition L,FILE* fp2);

int main(){
	FILE* fp1;
	FILE* fp2;
	char a[100],Ipath[50];
	int k=1;
	Line l;
	LinePosition L;
	printf("Please input the English path of the lrc file and make sure the lrc file encoding is utf-8:\n");
	scanf("%s",Ipath);
	fp1=fopen(Ipath,"r");
	printf("Please input the English path to put the txt file:\n");
	scanf("%s",Ipath);
	fp2=fopen(Ipath,"w");
	while(k<=4){
		fgets(a,100,fp1);
		k++;
	}
	L=&l;
	CreateList(L,fp1);
	BubbleSort(L,ListLength(L));
	WriteTxt(L,fp2);
	return 1;
}
/*
 * ListLength--Count the length of the list.
 *  L is a head pointer which points the head node.
 */
int ListLength(LinePosition L)
{
	int k=0;
	L=L->Next;
	do{
		L=L->Next;
		k++;
	}while(L!=NULL);
	return k;
}
/*
 * BubbleSort--Sort the list  accortding to the time.
 *  L is a head pointer which points the head node.
 *  k is the length of list(Except head node).
 */
void BubbleSort(LinePosition L,int k){
	int i,j;
	LinePosition HeadPointer,temp;
	HeadPointer=L;
	for(i=1;i<=k;i++){
		L=HeadPointer;	
		for(j=1;j<=k-i;j++)
		{
			if(L->Next->Time>L->Next->Next->Time)
			{	/* Excahnge the position of node through changing the 'Next' value in each node */
				temp=L->Next;
				L->Next=L->Next->Next;
				temp->Next=L->Next->Next;
				L->Next->Next=temp;
			}
			L=L->Next;
		}
	}
}
/*
 * CreateList--Create a list node for each lable([00:0.0]),and link every node.
 *  L is a head pointer which points the head node.
 *  fp1 is a file stream pointer which points the lrc file.
 */
void CreateList(LinePosition L,FILE* fp1){
	char a[100];
	int i,k,temp0;
	LinePosition temp;
	while(fgets(a,100,fp1)!=NULL){		//Read a line from lrc file until reading the end of file.
		k=Repetition(a);
		temp0=k;
		while(k){		//Create a list node for each lable in a line.
			k--;
			temp=(LinePosition)malloc(sizeof(Line));
			L->Next=temp;
			L=L->Next;
			L->Time=(a[2+10*k]*60+a[4+10*k]*10+a[5+10*k])*1000+a[7+10*k]*10+a[8+10*k];//Convert time to ms.
			for(i=10*temp0;a[i]!='\0';i++) L->b[i-10*temp0]=a[i];  //Store lyric into b[].
			L->b[i-10*temp0]='\0';
		}

	}
}
/*
 * WriteTxt--Write each line(which was put in the list node)into the txt file. 
 *  L is a head pointer which points the head node.
 *  fp2 is a file stream pointer which points the txt file.
 */
void WriteTxt(LinePosition L,FILE* fp2){
	while(L->Next!=NULL){
		L=L->Next;
		fputs(L->b,fp2);
	}
}
/*
 * Repetition--Count the number of lable([00:0.0]) for each line.
 *  a[100] stores a line.
 */
int Repetition(char* a){
	int i,k=0;
	for(i=0;a[i]!='\0';i++){
		if(a[i]=='[') k++;
	}
	return k;
}
