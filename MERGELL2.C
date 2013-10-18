#include<stdio.h>
#include<conio.h>
typedef struct list
{
	struct list *next;
	int data;
}list;
void create(list *,int);
void display(list *);
void mergesort(list *);
void merge(list *,list *);
void main()
{
	int ch,n;
	list *head,*p;
	do
	{
		clrscr();
		printf("\n\t\t\t\tMenu");
		printf("\n\t\t0.Exit");
		printf("\n\t\t1.Prepare the list");
		printf("\n\t\t2.Display list before sorting");
		printf("\n\t\t3.Display list after sorting");
		printf("\nEnter your choice->");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:
					clrscr();
					printf("\nEnter no. of elements->");
					scanf("%d",&n);
					head=(list*)malloc(sizeof(list));
					printf("\nEnter head element->");
					scanf("%d",&head->data);
					create(head,n);
					break;
			case 2:
					clrscr();
					display(head);
					getch();
					break;
			case 3:
					clrscr();
					mergesort(head);
					break;
		 }
	}while(ch!=0);
}
void create(list *head,int n)
{
	int i;
	list *q;
//	printf("\nEnter the no. of elements");
//	scanf("%d",&n);
//	head=(list*)malloc(sizeof(list));
//	printf("\nEnter head element->");
//	scanf("%d",&head->data);
	q=head;
	for(i=1;i<n;i++)
	{
		printf("\nEnter remaining elements->");
		q->next=(list*)malloc(sizeof(list));
		q=q->next;
		scanf("%d",&q->data);
		q->next=NULL;
	}
}
void display(list *head)
{
	list *q;
	q=head;
	printf("\n\t\t");
	while(q!=NULL)
	{
		printf(" %d ",q->data);
		q=q->next;
	}
}
void mergesort(list *head)
{
	int n=1,m,i;
	list *q,*mid,*p;
	q=head;
	while(q->next!=NULL)
	{
		q=q->next;
		n++;
	}
	m=n/2;
	q=head;
	mid=head;
	for(i=0;i<m;i++)
	{
		mid=mid->next;
	}
	p=mid->next;
	mid->next=NULL;
	merge(q,p);
}
void merge(list *head,list *second)
{
	int temparr[20],i=0;
	list *first;
	int *one,*two,k=0;
//	one=temparr;
//	two=second;
	first=head;
	while((first->data)<(second->data))
	{
		if((first->data)<temparr[i] && i!=0)
		{
			while(temparr[k]<(first->data))
			{
				k++;
			}
			if(temparr[k]>=(first->data))
			{
				for(;i>=k;i--)
				{
					temparr[i+1]=temparr[i];
					temparr[i]=head->data;
				}
			}
		}
		else
		{
			temparr[i]=head->data;
			i++;
		}
		first=first->next;
	}
	while((first->data)>(second->data))
	{
		temparr[i]=second->data;
		i++;
		second=second->next;
	}
}