#include<stdio.h>
#include<conio.h>

typedef struct list
{
	int data;
	struct list *next;
}list;
list *start,*sorted;
int pass;

void insertNode(list **);
void display(list *);
void mergeSort(int,int);
void merge(int,int,int,int);
int countNode(list *);
list *get(list *,int);
void create(list **,list *);

void main()
{
	list *temp;
	int ch,c;
	clrscr();
	start=NULL;
	do{
		clrscr();
		printf("\n\t\t\tMerge Sort Menu");
		printf("\n\t\t\t0. Exit");
		printf("\n\t\t\t1. Enter data in list");
		printf("\n\t\t\t2. Display the list before sorting");
		printf("\n\t\t\t3. Display after sorting");
		printf("\n\t\t\tEnter your choice : ");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:
				clrscr();
				insertNode(&start);
				break;
			case 2:
				printf("\n");
				display(start);
				getch();
				break;
			case 3:
				c=countNode(start);
				temp=start;
				sorted=NULL;
				while(temp!=NULL)
				{
					create(&sorted,temp);
					temp=temp->next;
				}
				pass=1;
				printf("\nBefore sorting : \n");
				display(sorted);
				mergeSort(0,c-1);
				printf("\nAfter sorting : ");
				display(sorted);
				getch();
				break;
		}
	}while(ch!=0);
}

list *get(list *start,int i)
{
	list *temp;
	temp=start;
	while(i>0)
	{
		temp=temp->next;
		i--;
	}
	return temp;
}
int countNode(list *start)
{
	int cnt=0;
	list *temp;
	for(temp=start;temp!=NULL;temp=temp->next)
		cnt++;

	return cnt;
}
void create(list **p,list *q)
{
	list *temp,*temp1;
	temp=(list *)malloc(sizeof(list));
	temp->data=q->data;
	temp->next=NULL;
	if(*p==NULL)
	{
		  *p=temp;
	}
	else
	{
		temp1=*p;
		while(temp1->next!=NULL)
			temp1=temp1->next;
		temp1->next=temp;
	}
}
void merge(int lf,int ll,int rf,int rl)
{
	list *first,*second,*third;
	list *temp;
	int plf,i;
	first=second=third=NULL;
	plf=lf;
	printf("\nAfter pass %d",pass);
	pass++;
	for(i=lf;i<=ll;i++)
	{
		temp=get(sorted,i);
		create(&first,temp);
	}
	printf("\nFirst list  : ");
	display(first);
	for(i=rf;i<=rl;i++)
	{
		temp=get(sorted,i);
		create(&second,temp);
	}
	printf("\nSecond list : ");
	display(second);
	printf("\n");
	while(lf<=ll && rf<=rl)
	{

		if(first->data < second->data)
		{
			create(&third,first);
			first=first->next;
			lf++;
		}
		else
		{
			create(&third,second);
			second=second->next;
			rf++;
		}
	}
	while(lf<=ll)
	{
		create(&third,first);
		first=first->next;
		lf++;
	}
	while(rf<=rl)
	{
		create(&third,second);
		second=second->next;
		rf++;
	}
	printf("Third List  : ");
	display(third);
	printf("\n");
	while(plf<=rl)
	{
		   temp=get(sorted,plf);
		   temp->data=third->data;
		   third=third->next;
		   plf++;
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
void insertNode(list **start)
{
	int d;

	list *temp,*temp1;
	printf("\nEnter the data : ");
	scanf("%d",&d);

	temp=(list *)malloc(sizeof(list));
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
void display(list *start)
{
	list *temp;
	temp=start;
	while(temp!=NULL)
	{
		if(temp->next==NULL)
			printf("%d",temp->data);
		else
			printf("%d  ",temp->data);
		temp=temp->next;
	}
}