#include<stdio.h>
#include<conio.h>
#include<alloc.h>

struct list
{
	int data;
	struct list *next;
}*start,*sorted;


	int pass;
	void addItem(struct list **);
	void display(struct list *);
	void mergeSort(int,int);
	void merge(int,int,int,int);
	int countNode(struct list *);
	struct list* get(struct list *,int);
	void create(struct list **,struct list *);

void main()
{
	struct list *temp;
	int ch,c;
	clrscr();
	start=NULL;
	do{
		clrscr();
		printf("\n\t0. Exit");
		printf("\n\t1. Enter data in list");
		printf("\n\t2. Display the list");
		printf("\n\t3. Sort List");
		printf("\n\tEnter your choice : ");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1: clrscr();
				addItem(&start);
				break;
			case 2: printf("\n");
				display(start);
				getch();
				break;
			case 3:	c=countNode(start);
				temp=start;
				sorted=NULL;
				while(temp!=NULL)
				{
					create(&sorted,temp);
					temp=temp->next;
				}
				pass=1;
				mergeSort(0,c-1);
				printf("\n\nAfter sorting : ");
				display(sorted);
				getch();
				break;
			default: printf("\n\tWrong choice !!");
				break;
		}
	}while(ch!=0);
}

struct list* get(struct list *start,int i)
{
	struct list *temp;
	temp=start;
	while(i>0)
	{
		temp=temp->next;
		i--;
	}
	return temp;
}
int countNode(struct list *start)
{
	int cnt=0;
	struct list *temp;
	for(temp=start;temp!=NULL;temp=temp->next)
		cnt++;

	return cnt;
}
void create(struct list **p,struct list *q)
{
	struct list *temp,*temp1;
	temp=(struct list *)malloc(sizeof(struct list));
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
	struct list *first,*second,*third;
	struct list *temp;
	int plf,i;
	first=second=third=NULL;
	plf=lf;
	printf("\nPass %d",pass);
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
void addItem(struct list **start)
{
	int d;
	char ch;
	struct list *temp,*temp1;
	printf("\nY : Create new list ");
	printf("\nN : Add to existing ");
	printf("\nYour choice : ");
	flushall();
	scanf("%c",&ch);
	if(ch=='Y' || ch=='y')
		*start=NULL;
	else if(ch=='N' || ch=='n')
		temp=*start;
	else
	{
		printf("\n\nWrong choice!!");
		getch();
		return;
	}
	printf("\nEnter the data : ");
	scanf("%d",&d);

	temp=(struct list *)malloc(sizeof(struct list));
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
void display(struct list *start)
{
	struct list *temp;
	temp=start;
	while(temp!=NULL)
	{
		if(temp->next==NULL)
			printf("%d",temp->data);
		else
			printf("%d, ",temp->data);
		temp=temp->next;
	}
}