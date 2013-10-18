#include<stdio.h>
#include<conio.h>
typedef struct node
{
	int data;
	struct node *next;
}list;
list *temp;
list *t;
list *l;

int flag=0;

void create(list **,int);
void display(list *);
int count(list *);
list *merge_sort(list *);
list *merge(list *,list *,list *);

void main()
{
	list *head=NULL;
	int d;
//	list *p1,*p2;
	int ch;flag=0;
	do
	{
		clrscr();
		printf("\t\t\tMENU");
		printf("\n\t\t0.Exit");
		printf("\n\t\t1.Create the list");
		printf("\n\t\t2.Display list before sorting");
		printf("\n\t\t3.Display list after sorting");
		printf("\n\n\tEnter the choice->");
		scanf("%d",&ch);

		switch(ch)
		{
			case 1:
					clrscr();
					printf("\nEnter the data for node->");
					scanf("%d",&d);
					create(&head,d);
					break;
			case 2:
					clrscr();
					printf("\nArray before sorting\n\t");
					display(head);
					getch();
					break;
			case 3:
					clrscr();
//					l=NULL;
/*					p1=head;
					p2=temp;
					while(p1!=NULL)
					{
						p2=(list *)malloc(sizeof(list));
						if(flag==0)
						{
							temp=p2;
							flag++;
						}
						p2->data=p1->data;
						p2=p2->next;
						p1=p1->next;
					}
*/
					merge_sort(head);
					head=t;
	   //				diplay(head);
					getch();
					break;
		}
	}while(ch!=0);

}
void create(list **h,int d)
{
	list *p;
	p=*h;
	if(*h==NULL)
	{
//		printf("\nEnter the data for head node->");
//		scanf("%d",&d);
		*h=(list *)malloc(sizeof(list));
		(*h)->data=d;
		(*h)->next=NULL;
	}
	else
	{
//		printf("\nEnter the data->");
//		scanf("%d",&d);
		while(p->next!=NULL)
			p=p->next;
		p->next=(list *)malloc(sizeof(list));
		p=p->next;
		p->data=d;
		p->next=NULL;
	}
	return;
}
void display(list *head)
{
	list *q;
	q=head;
	while(q!=NULL)
	{
		printf("%d  ",q->data);
		q=q->next;
	}
}
int count(list *head)
{
	int n=0;
	list *p;
	p=head;
	while(p->next!=NULL)
	{
		n++;
		p=p->next;
	}
	return n;
}

list *merge_sort(list *head)
{
	int n,m,i;
	list *p,*mid,*q;
	list *l;
	q=head;
	while(q->next!=NULL)
	{
		n=count(head);
		m=n/2;
		p=head;
		mid=head;
		for(i=1;i<=m;i++)
		{
			mid=mid->next;
		}
		q=mid->next;
		mid->next=NULL;

		p=merge_sort(p);
		q=merge_sort(q);
		l=merge(p,q,head);
		return l;
	}
//	if(flag!=0)
		return head;
}

list *merge(list *l1,list *l2,list *head)
{
	list *temp;
//	list *l;
//	temp1=l1;
//	temp2=l2;

	while(l1!=NULL && l2!=NULL)
	{
		if((l2->data)>=(l1->data))
		{
			create(&l,l1->data);
			l1=l1->next;
		}
		else
		{
			create(&l,l2->data);
			l2=l2->next;
		}
	}
	while(l1!=NULL)
	{
	   create(&l,l1->data);
	   l1=l1->next;
	}
	while(l2!=NULL)
	{
		create(&l,l2->data);
		l2=l2->next;
	}
//	l1=temp1;
//	l2=temp2;
	l=temp;
	return l;
}
