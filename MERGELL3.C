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
list *sort(list *);
int countnode(list *);
list *max(list *);
void swap(list *,int,list *);
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
	int n,m,i;
	list *q,*mid,*p;
	q=head;

	n=countnode(head);
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
int countnode(list *head)
{
	int n=0;
	list *q;
	q=head;
	while(q->next!=NULL)
	{
		q=q->next;
		n++;
	}
	return n;
}
void merge(list *head,list *second)
{
//	int i=0;
	list *l1,*l2,*ans;
	l1=head;
	l1=sort(l1);
	l2=second;
	l2=sort(l2);
}
list *sort(list *head)
{
	list *p,*q,*maxk;
	int n,maxkey,current;
	n=countnode(head);
/*	for(p=head->next,i=1;p!=NULL || i<n;p++,i++)
	{
		for(q=head,j=0;q!=NULL || j<n-1;j++)
			{
				if((p->data)<(q->data))
				{
					q->next=p->next;
					p->next=q;
				}
			}
	}
*/
	for(current=n;current>0;current++)
	{
		maxk=max(head);
		swap(maxk,current,head);
	}
	return head;
}
list *max(list *head)
{
	list *largest;
	list *p,*q;
	p=head;
	q=head;
	largest=p;
	while(q->next!=NULL)
	{
		while(q->data>p->next->data)
		{
			p=p->next;
		}
		if(q->data<p->next->data)
		{
			largest=p->next;
		}
	}
	return largest;
}
void swap(list *p,int high,list *head)
{
	list *temp;
	temp=p;
	p->data=list->data[high];
	list->data[high]=temp;
}