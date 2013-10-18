#include<stdio.h>
#include<conio.h>
typedef struct list
{
	int data;
	struct list *next;
}list;
list *merge_sort(list *);
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
	p=merge_sort(head);
	printf("\nAfter sorting-\n");
	while(p!=NULL)
	{
		printf("-<%d>-",p->data);
		p=p->next;
	}
	getch();

}
list *merge_sort(list *head)
{
	int n=0,m,i;
	list *mid,*l1,*l2,*p;
	while(head->next!=NULL)
	{
		l1=head;
		while(l1->next!=NULL)   //counts the no of nodes
		{
			l1=l1->next;
			n++;
		}
		mid=head;
		m=n/2;
		for(i=0;i<m;i++)
		{
			mid=mid->next;
		}
		l2=mid->next;
		mid->next=NULL;
		l1=head;
		merge_sort(l1);
		merge_sort(l2);
		p=merge(l1,l2);
	}
	return(p);
}
list *merge(list *l1,list *l2)
{
	int temparr[20];
	int i=0;
	list *p;
	while(l1!=NULL && l2!=NULL)
	{
		if((l1->data)<(l2->data))
		{
			temparr[i]=l1->data;
			l1=l1->next;
			i++;
		}
		else
		{
			temparr[i]=l2->data;
			l2=l2->next;
			i++;
		}
	}
	for(i=0;i<10;i++)
	{
		p->data=temparr[i];
		p=p->next;
	}
	if(l1->next==NULL)
	{
		temparr[i]=l2->data;
		l2=l2->next;
		i++;
	}
	if(l2->next==NULL)
	{
		temparr[i]=l1->data;
		l1=l1->next;
		i++;
	}
//	if(l1->next!=NULL && l2->next!=NULL)


	return(p);
}