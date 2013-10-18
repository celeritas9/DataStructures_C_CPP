#include<stdio.h>
#include<conio.h>
typedef struct gll    // structure for the GLL
{
	int flag;
	char data;
	struct gll *down,*next;
}gll;

gll *stack[20];       // declare stack globally
int tos=-1,flag=1,x=4;

gll *getnode(void)     // getnode function to create a new node
{
	gll *p;
	p=(gll*)malloc(sizeof(gll));  // dynamically allocate space for new node
	p->down=p->next=NULL;
	p->flag=0;
	p->data='\0';
	return p;      // return address of newly created node
}
void push(gll *p)       // push function for stack
{
	stack[++tos]=p;
}
gll *pop()           // pop function for stack
{
	return stack[tos--];
}
gll *create(char ch[])   // create function for creating GLL
{
	int i=0,popped=0;
	gll *root=NULL,*curr,*temp;
	while(ch[i]!='\0')       // loop until character of the string becomes null
	{
		if(ch[i]=='(')         // if character is ( then create node with flag 1
		{
			if(root==NULL)
			{
				root=getnode();
				root->flag=1;
				push(root);
				curr=root;
			}
			else
			{
				if(curr->flag==0)
				{
					curr->next=getnode();
					curr->next->flag=1;
					curr=curr->next;
				}
				else
				{
					push(curr);
					curr->down=getnode();
					curr->down->flag=1;
					curr=curr->down;
				}
			}
		}
		else if(ch[i]!='('&&ch[i]!=')'&&ch[i]!=',')  // if character is alphabet
		{
			//popped is used to show that curr is recently popped so add node
			//next to it
			if(curr->flag==0 || popped==1)
			{
				curr->next=getnode();
				curr=curr->next;
				curr->data=ch[i];
			}
			else
			{
				push(curr);
				curr->down=getnode();
				curr=curr->down;
				curr->data=ch[i];
			}
		}
		else if(ch[i]==')')  // if character is ) then pop the top of stack
		{
			curr=pop();
			popped=1;
		}
		i++;
	}
	return root;
}

void display(gll *r,int y)
{
	while(r!=NULL)
	{
		if(r->flag==0)   // there is data
		{
			gotoxy(x,y);
			printf("%c",r->data);
			if(r->next!=NULL)
			{
				gotoxy(x+2,y);
				printf("-");
			}
			x+=4;
		}
		if(r->flag==1)
		{
			gotoxy(x,y);
			printf("|");
			if(r->next!=NULL)
			{
				gotoxy(x+2,y);
				printf("-");
			}
			display(r->down,y+1);
		}
		r=r->next;
	}
}

int depth(gll *root)       // function for finding depth
{
	int count=0;
	gll *curr=root;
	while(curr!=NULL)       // loop until node not becomes null
	{
		if(curr->flag==1)
		{
			count++;           // increment depth counter if flag is 1
			curr=curr->down;
		}
		else
		curr=curr->next;
	}
	return count;      // return the depth count
}

void eq(gll *root1,gll *root2,int pass)  // function for equivalence
{
	gll *curr1=root1,*curr2=root2;
	while(curr1!=NULL && curr2!=NULL)  // loop until both node not becomes null
	{
		if(curr1->flag==curr2->flag)     // go inside loop only if flags are same
		{
			if(curr1->flag==1 && pass==0)
			{
				push(curr1);
				push(curr2);
				curr1=curr1->down;
				curr2=curr2->down;
			}
			else
			{
				curr1=curr1->next;
				curr2=curr2->next;
			}
		}
		else             // if flags are not same make flag 0 & break;
		{
			flag=0;
			break;
		}
		if((curr1!=NULL && curr2==NULL) || (curr1==NULL && curr2!=NULL))
		{
			flag=0;
			break;
		}
	}
	while(flag==1 && tos>=0)
	{
		curr2=pop();
		curr1=pop();
		eq(curr1,curr2,1);  // pass the popped element to recursive function
	}
}

gll * copy(gll *root)     // copy function to copy GLL
{
	gll *p=NULL;
	if(root!=NULL)        // if GLL is not NULL
	{
		p=(gll*)malloc(sizeof(gll));    // dynamically allocate memory space
		p->flag=root->flag;   // make their flags equal
		if(p->flag==0)
			p->data=root->data;    // if flag is zero then also assign data
		else
			p->down=copy(root->down);  // call recursive function for downlink copy
		p->next=copy(root->next);   // call recursive function for nextlink copy
	}
	return p;     // return newly copied node
}

void main(void)       // main function
{
	int ch;
	char str1[20],str2[20],str3[20];
	gll *gll1=NULL,*gll2=NULL,*gll3=NULL,*gll4;
	gll4=(gll*)malloc(sizeof(gll));
	do
	{
		tos=-1;
		clrscr();
		printf("\n\t\tGeneralised linked list(Expression)");
		printf("\n\t\t-----------------------------------");
		printf("\n\t0.Exit.");
		printf("\n\t1.Create first GLL");
		printf("\n\t2.Create second GLL");
		printf("\n\t3.Display first GLL");
		printf("\n\t4.Display second GLL");
		printf("\n\t5.Check equivalence");
		printf("\n\t6.Depth");
		printf("\n\t7.Copy GLL");
		printf("\n\nEnter the choice: ");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:
					printf("\n\nEnter the first expression: ");
					scanf("%s",str1);
					gll1=create(str1);
					break;
			case 2:
					printf("\n\nEnter the second expression: ");
					scanf("%s",str2);
					gll2=create(str2);
					break;
			case 3:
					printf("\n\nThe first expression is: ");
					display(gll1,24);
					getch();
					break;
			case 4:
					printf("\n\nThe second expression is: ");
					display(gll2,24);
					getch();
					break;
			case 5:
					flag=1;
					eq(gll1,gll2,0);
					if(flag==0)
						printf("\n\nThe expressions are not same...");
					else
						printf("\n\nThe expressions are same...");
					getch();
					break;
			case 6:
					printf("\n\nThe depth of first GLL is :- %d",depth(gll1));
					printf("\n\nThe depth of second GLL is :- %d",depth(gll2));
					getch();
					break;
			case 7:
					printf("\n\nEnter the expression to copy: ");
					scanf("%s",str3);
					gll3=create(str3);
					tos=-1;
					printf("\n\nThe original expression is: ");
					display(gll3,24);
					gll4=copy(gll3);
					tos=-1;
					printf("\n\nThe copied expression is: ");
					display(gll4,24);
					getch();
					break;
		}
	}while(ch!=0);
}