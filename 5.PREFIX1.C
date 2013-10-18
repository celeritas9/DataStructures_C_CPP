//Terminals are always students -- Teachers always drive students

#include<stdio.h>
#include<conio.h>
#define MAX 50

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

int length(char *);                      //counts length of the exprn

btree *create(char *,btree *);
void Rec_inorder(btree *);               //Recursive Inorder
void Rec_preorder(btree *);              //Recursive Preorder
void Rec_postorder(btree *);             //Recursive Postorder

void nRec_inorder(btree *);              //Non-Recursive Inorder
void nRec_preorder(btree *);             //Non-Recursive Preorder
void nRec_postorder(btree *);            //Non-Recursive Postorder

void push(btree *);             //pushes on stack btree type pointer
btree *pop();                    //pops btree type pointer from stack

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
					printf("\nEnter the valid prefix expression\n\n(e.g -ab)->\n\n");
					scanf("%s",&expr);
					root=create(expr,root);
					break;
			case 2:
					clrscr();
					if(root==NULL)
						printf("\n Create the tree of the expression first!!!");
					else
					{
						printf("\n\nRecursive inorder display of the expression:\n\n\t\t");
						Rec_inorder(root);
					}
					getch();
					break;
			case 3:
					clrscr();
					if(root==NULL)
						printf("\n Create the tree of the expression first!!!");
					else
					{
						printf("\n\nRecursive preorder display of the expression:\n\n\t\t");
						Rec_preorder(root);
					}
					getch();
					break;
			case 4:
					clrscr();
					if(root==NULL)
						printf("\n Create the tree of the expression first!!!");
					else
					{
						printf("\n\nRecursive postorder display of the expression:\n\n\t\t");
						Rec_postorder(root);
					}
					getch();
					break;
			case 5:
					clrscr();
					if(root==NULL)
						printf("\n Create the tree of the expression first!!!");
					else
					{
						printf("\n\nNon-Recursive inorder display of the expression:\n\n\t\t");
						nRec_inorder(root);
					}
					getch();
					break;
			case 6:
					clrscr();
					if(root==NULL)
						printf("\n Create the tree of the expression first!!!");
					else
					{
						printf("\n\nNon-Recursive preorder display of the expression:\n\n\t\t");
						nRec_preorder(root);
					}
					getch();
					break;
			case 7:
					clrscr();
					if(root==NULL)
						printf("\n Create the tree of the expression first!!!");
					else
					{
						printf("\n\nNon-Recursive postorder display of the expression:\n\n\t\t");
						nRec_postorder(root);
					}
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
	char fc;        //fc is first character

	btree *temp;
	btree *item1,*item2;

	fc=*e;
	len=length(e);
	for(i=0;i<len-1;i++)      //e is made to point to last character of the exprn
		e++;
	for(i=len-1;i>=0;i--)
	{
		if(*e=='$'||*e=='~'||*e=='!'||*e=='%'||*e=='^'||*e=='&'||*e=='*'||*e=='-'
			||*e=='+'||*e=='|'||*e=='/')
		{
			item1=pop();
			item2=pop();

			temp=(btree *)malloc(sizeof(btree));
			temp->lp=item1;
			temp->data=*e;
			temp->rp=item2;
			if(top==NULL && *e==fc)
			{
				root=temp;
				return root;
			}
			push(temp);      //pushes btree pointer on the stack
		}
		else
		{
			temp=(btree *)malloc(sizeof(btree));
			temp->lp=NULL;
			temp->rp=NULL;
			temp->data=*e;
			push(temp);
		}
		e--;
	}
	return NULL;
}
void push(btree *r)
{
	stack *temp;

	if(top==NULL)
	{
		top=(stack *)malloc(sizeof(stack));
		top->ptr=r;
		top->link=NULL;
	}
	else
	{
		temp=(stack *)malloc(sizeof(stack));
		temp->ptr=r;
		temp->link=top;
		top=temp;
	}
}
btree *pop()
{
	btree *item;
	stack *temp;

	if(top==NULL)
	{
		printf("\nStack is NULL!!!");
		return NULL;
	}
	temp=top;
	item=temp->ptr;
	top=top->link;
	free(temp);

	return item;               //return only btree pointer in stack
}
void Rec_inorder(btree *r)
{
	btree *temp;
	temp=r;
	if(temp!=NULL)
	{
		Rec_inorder(temp->lp);
		printf("%c",temp->data);
		Rec_inorder(temp->rp);
	}
}
void Rec_preorder(btree *r)
{
	btree *temp;
	temp=r;
	if(temp!=NULL)
	{
		printf("%c",temp->data);
		Rec_preorder(temp->lp);
		Rec_preorder(temp->rp);
	}
}
void Rec_postorder(btree *r)
{
	btree *temp;
	temp=r;
	if(temp!=NULL)
	{
		Rec_postorder(temp->lp);
		Rec_postorder(temp->rp);
		printf("%c",temp->data);
	}
}
void nRec_inorder(btree *root)
{
	btree *temp=root;
	while(temp!=NULL)                //pushes visited nodes on stack
	{
		push(temp);
		temp=temp->lp;
	}
	while(top!=NULL)
	{
		temp=pop();              //after popping from the stack print data
		printf("%c",temp->data);
		temp=temp->rp;
		while(temp!=NULL)
		{
			push(temp);          //pushes visited nodes on stack
			temp=temp->lp;
		}
	}
}
void nRec_preorder(btree *root)
{
	btree *temp=root;

	while(temp!=NULL)
	{
		printf("%c",temp->data);     //before pushing on stack print data
		push(temp);
		temp=temp->lp;
	}
	while(top!=NULL)
	{
		temp=pop();
		temp=temp->rp;
		while(temp!=NULL)
		{
			printf("%c",temp->data);
			push(temp);
			temp=temp->lp;
		}
	}
}
void nRec_postorder(btree *root)
{
	int i=0,j;
	char arr[MAX];
	btree *temp=root;

	while(temp!=NULL)
	{
		while(temp->rp!=NULL)         //goes to the rightmost node
		{
			arr[i]=temp->data;
			i++;
			push(temp);           //only pushes the node having right child on stack
			temp=temp->rp;
		}
		arr[i]=temp->data;
		i++;
		if(top==NULL)
			break;
		else                          //go to left of popped node
		{
			temp=pop();
			temp=temp->lp;
		}
	}
	for(j=i-1;j>=0;j--)
		printf("%c",arr[j]);
}