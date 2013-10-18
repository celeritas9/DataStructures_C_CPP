#include<stdio.h>
#include<conio.h>
typedef struct list
{
	int data;
	struct list *next;
}list;
void merge_sort(list *);
list *merge(list *,list *);
void main()
{
	int i,n;
	list *p,*head;
	clrscr();
	printf("\nenter the no. of nodes\t");
	scanf("%d",&n);
	printf("\nenter 0th value-");
	head=(list*)malloc(sizeof(list));
	scanf("%d",&(head->data));
	head->next=NULL;
	p=(list*)malloc(sizeof(list));
	p=head;
	for(i=1;i<n;i++)
	{
		printf("\nenter %d value-",i);
		p->next=(list*)malloc(sizeof(list));
		p=p->next;
		p->next=NULL;
		scanf("%d",&(p->data));
	}
	p=head;
	while(p!=NULL)
	{
		printf("-<%d>-",p->data);
		p=p->next;
	}
	merge_sort(head);
	getch();

}
void merge_sort(list *head)
{
	int m,i,n;
	list *p,*mid,*q;
	while(head->next!=NULL)
	{
		m=n/2;
		p=head;
		mid=head;
		while(
		{
			mid=mid->next;
		}
		q=mid->next;
		mid->next=NULL;

		merge_sort(p);
		merge_sort(q);
		merge(p,q);
	}
}
list *merge(list *p,list *q)
{
	list *l1,*l2;
	if(p==NULL)
	{
		return (q);
	}
	if(q==NULL)
	{
		return (p);
	}
	if((p->data)<(q->data))
	{
		l1=l2=p;
		p=p->next;
	}
	else
	{
		l1=l2=q;
		q=q->next;
	}
	while(p!=NULL && q!=NULL)
	{
		if((p->data)<(q->data))
		{
			l1->next=p;
			p=p->next;
			l1=l1->next;
		}
		else
		{
			l1->next=p;
			p=p->next;
			l1=l1->next;
		}
	}
	if(p==NULL)
	{
		l1->next=q;
	}
	else
	{
		l1->next=p;
	}
	return(l1);
}