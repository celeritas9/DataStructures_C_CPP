#include<stdio.h>
#include<conio.h>
#include<ctype.h>
#define MAX 20

typedef struct btree
{
	struct btree *lp;
	char data;
	struct btree *rp;
}btree;

typedef struct stack
{
	btree *ptr;         //data in the stack struct is of btree type pointer
	struct stack *link;
}stack;
stack *top=NULL;

int length(char *);

btree *create(char *,btree *);

//void push(stack **,char *);      //pushes operand on stack
void push(stack **,btree *);  //pushes operator on stack
btree *pop(stack **);
void main()
{

	btree *root=NULL;

	int ch;
	char expr[MAX];

	do
	{
		clrscr();
		printf("\n\t\tPrefix to binary tree program");
		printf("\n\t\t-----------------------------");
		printf("\n\t\t0. Exit");
		printf("\n\t\t1. Create binary tree from the expression");
		printf("\n\t\t2. Inorder of the tree(Recursive)");
		printf("\n\t\t3. Preorder of the tree(Recursive)");
		printf("\n\t\t4. Postorder of the tree(Recursive)");
		printf("\n\t\t5. Inorder of the tree(Non-Recursive)");
		printf("\n\t\t6. Preorder of the tree(Non-Recursive)");
		printf("\n\t\t7. Postorder of the tree(Non-Recursive)");
		printf("\n\n\tEnter the choice->");
		scanf("%d",&ch);

		switch(ch)
		{
			case 1:
					clrscr();
					printf("\nEnter the valid prefix expression(e.g -ab)->");
					scanf("%s",&expr);
					root=create(expr,root);
					getch();
					break;
			case 2:
					clrscr();
					getch();
					break;
		}
	}while(ch!=NULL);
}
int length(char *e)
{
	int cnt=0;
	while(*e!='\0')
	{
		e++;
		cnt++;
	}
	return cnt;
}
btree *create(char *e,btree *root)
{
	int len,i;
	stack *st;
	btree *temp,*temp1;
	btree *item1,*item2;

	len=length(e);
	for(i=0;i<len-1;i++)      //e is made to point to last character of the exprn
		e++;
	for(i=len-1;i>=0;i--)
	{

		if(*e=='$'||*e=='~'||*e=='!'||*e=='%'||*e=='^'||*e=='&'||*e=='*'||*e=='-'
			||*e=='+'||*e=='|'||*e=='/')
		{
			item1=pop(&top);
			item2=pop(&top);

			temp->lp=item1;
			temp->rp=item2;
			push(&st,temp);      //pushes btree pointer on the stack
		}
		else
		{
			temp1=(btree *)malloc(sizeof(btree));
			temp1->lp=temp->rp=NULL;
			temp1->data=*e;
			push(&st,temp1);
		}
		e--;
	}
}
/*void push(stack **st,char *e)
{
	stack *temp;

	if(*st==NULL)
	{
		(*st)=(stack *)malloc(sizeof(stack));
		(*st)->ptr=e;
		(*st)->link=NULL;
		top=*st;
	}
	else
	{
		temp=(stack *)malloc(sizeof(stack));
		temp->ptr=*e;
		temp->link=top;
		top=temp;
		*st=top;
	}
} */
void push(stack **st,btree *r)
{
	 stack *temp;

	if(*st==NULL)
	{
		(*st)=(stack *)malloc(sizeof(stack));
		(*st)->ptr=r;
		(*st)->link=NULL;
		top=*st;
	}
	else
	{
		temp=(stack *)malloc(sizeof(stack));
		temp->ptr=r;
		temp->link=top;
		top=temp;
		*st=top;
	}
}
btree *pop(stack **top)
{
	btree *item;
	stack *temp;

	if(*top==NULL)
	{
		printf("\nStack is NULL!!!");
		return NULL;
	}
	temp=*top;
	item=temp->ptr;
	*top=(*top)->link;
	free(temp);

	return item;
}