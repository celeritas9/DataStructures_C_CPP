#include<stdio.h>
#include<conio.h>
#include<alloc.h>

struct node
{
	int data;
	struct node *next;
}*start;

void insertNode(struct node **);
void display(struct node *);
void mergeSort(int,int);
void merge(int,int,int,int);
int countNode(struct node *);
int get(struct node *,int);

void main()
{
	int ch,c;
	clrscr();
	start=NULL;
	do{
		clrscr();
		printf("\n\t\t\tMerge Sort Menu");
		printf("\n\t\t\t0. Exit");
		printf("\n\t\t\t1. Enter data in list");
		printf("\n\t\t\t2. Display the list");
		printf("\n\t\t\t3. Sort List");
		printf("\n\t\t\tEnter your choice : ");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:
				clrscr();
				insertNode(&start);
				break;
			case 2:
				clrscr();
				display(start);
				getch();
				break;
			case 3:
				c=countNode(start);
				mergeSort(0,c-1);
				display(start);
				getch();
				break;
		}
	}while(ch!=0);
}

int get(struct node *start,int i)
{
	struct node *temp;
	temp=start;
	while(i>0)
	{
		temp=temp->next;
		i--;
	}
	return temp->data;
}
int countNode(struct node *start)
{
	int cnt=0;
	struct node *temp;
	for(temp=start;temp!=NULL;temp=temp->next)
		cnt++;

	return cnt;
}
void merge(int lf,int ll,int rf,int rl)
{
	struct node *temp;
	int tempArray[20],b[20],c,i;
	int plf,ti;
	int x,y;
	plf=lf;
	ti=0;
	c=countNode(start);
	temp=start;
	for(i=0;i<c;i++)
		tempArray[i]=get(start,i);

	while(lf<=ll && rf<=rl)
	{

		if(tempArray[lf]<tempArray[rf])
		{
			b[ti]=tempArray[lf];
			ti++;
			lf++;
		}
		else
		{
			b[ti]=tempArray[rf];
			ti++;
			rf++;
		}
	}
	while(lf<=ll)
	{
		b[ti]=tempArray[lf];
		ti++;
		lf++;
	}
	while(rf<=rl)
	{
		b[ti]=tempArray[rf];
		ti++;
		rf++;
	}
	ti=0;
	while(plf<=rl)
	{
		tempArray[plf]=b[ti];
		plf++;
		ti++;
	}
	ti=0;
	while(temp!=NULL)
	{
		temp->data=tempArray[ti];
		temp=temp->next;
		ti++;
	}

}
void mergeSort(int first,int last)
{
	int mid;
	if(first<last)
	{
		mid=(first+last)/2;
		mergeSort(first,mid);
		mergeSort(mid+1,last);
		merge(first,mid,mid+1,last);
	}
}
void insertNode(struct node **start)
{
	int d;
	struct node *temp,*temp1=*start;
	printf("\nEnter the data : ");
	scanf("%d",&d);

	temp=(struct node *)malloc(sizeof(struct node));
	temp->data=d;

	if(*start==NULL)
	{
		*start=temp;
		(*start)->next=NULL;
	}
	else
	{
		temp1=*start;
		while(temp1->next!=NULL)
			temp1=temp1->next;
		temp1->next=temp;
		temp->next=NULL;
	}
}
void display(struct node *start)
{
	struct node *temp;
	temp=start;
	while(temp!=NULL)
	{
		printf("%d ",temp->data);
		temp=temp->next;
	}
}