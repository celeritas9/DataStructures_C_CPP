#include<stdio.h>
#include<conio.h>
enum boolean
{
	false=0,
	true=1
};
typedef struct TBtree
{
	enum boolean lt;            //if lt or rt is 1 thread is present
	struct TBtree *lp;
	int data;
	struct TBtree *rp;
	enum boolean rt;
	int flag;
}TBtree;

void create(TBtree **,int);
TBtree *get_node(int);
void preorder(TBtree *);
void inorder(TBtree *);
void postorder(TBtree *);

void main()
{
	int ch,val;
	TBtree *root;
	root=NULL;

	do
	{
		clrscr();
		printf("\t\tThreaded Binary Tree Program\n");
		printf("\t\t----------------------------\n");
		printf("\n\t\t0. Exit");
		printf("\n\t\t1. Create/Insert Node");
		printf("\n\t\t2. Preorder Display");
		printf("\n\t\t3. Inorder Display");
		printf("\n\t\t4. Postorder Display\n");
		printf("\n\tYour Choice-> ");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:
				clrscr();
				do
				{
					printf("\n\nEnter the data for the new node->\t");
					scanf("%d",&val);
					create(&root,val);
					printf("\nDo you want to continue? ");
				}while(getche()=='y' || getche()=='Y');
				break;
			case 2:
				clrscr();
				printf("\nThreaded Preoder Printing\n");
				printf("-------------------------\n\n");
				preorder(root);
				getch();
				break;
			case 3:
				clrscr();
				printf("\nThreaded Inoder Printing\n");
				printf("------------------------\n\n");
				inorder(root);
				getch();
				break;
			case 4:
				clrscr();
				printf("\nThreaded Postoder Printing\n");
				printf("--------------------------\n\n");
				postorder(root);
				getch();
				break;
		}
	}while(ch!=0);
}
TBtree *get_node(int val)
{
	TBtree *node;

	node=(TBtree*)malloc(sizeof(TBtree));
	node->lt=true;
	node->data=val;
	node->rt=true;
	node->flag=0;

	return node;
}
void create(TBtree **s,int val)
{
	TBtree *head=*s,*z,*p;
	z=get_node(val);

	/* if tree is empty */
	if(head==NULL)
	{
		/* head created */
		head=(TBtree*)malloc(sizeof(TBtree));

		head->lt=false;          /* indicates pointer, not thread */
		head->rt=false;          /* indicates pointer, not thread */
		head->data=-9999;        /* no data in head */
		head->lp=z;
		head->rp=head;

		*s=head;                 /* important condition */
		z->lp=head;              /* left thread to head */
		z->rp=head;              /* right thread to head */
	}
	/* if tree not empty */
	else
	{
		p=head->lp;
		/* traverses for the correct position for insertion */
		while(p!=head)
		{
			if(val==p->data)
			{
				printf("\nThis value already exists!!!");
				getch();
				free(z);
				return;
			}
			else if(val<p->data)
			{
				if(p->lt==false)            //if not thread then
					p=p->lp;
				else                        //if thread found then insert z
				{
					z->lp=p->lp;
					z->rp=p;
					p->lp=z;
					p->lt=false;            //indicates leftlink of p is present
											//required for printing
					return;                 //return is important
				}
			}
			else if(val>p->data)
			{
				if(p->rt==false)            //if not thread then
					p=p->rp;
				else                        //if thread found then insert z
				{
					z->rp=p->rp;
					z->lp=p;
					p->rp=z;
					p->rt=false;            //indicates leftlink of p is present
											//required for printing
					return;                 //return is important
				}
			}
		}
	}
}
void preorder(TBtree *root)
{
	TBtree *p;
	p=root->lp;
	while(p!=root)
	{
		printf("  %d",p->data);
		while(p->lt==false)
		{
			p=p->lp;
			printf("  %d",p->data);
		}
		while(p->rt==true)
		{
			p=p->rp;
		}
		p=p->rp;
	}
}
void inorder(TBtree *root)
{
	TBtree *p;
	p=root->lp;
	while(p!=root)
	{
		while(p->lt==false)
			p=p->lp;
		printf("  %d",p->data);
		while(p->rt==true && p->rp!=root)
		{
			p=p->rp;
			if(p->rp==root)
			{
				printf("  %d",p->data);
				break;
			}
			printf("  %d",p->data);
		}
		p=p->rp;
	}
}
void postorder(TBtree *root)
{
	TBtree *p;
	p=root->lp;
	//after printing make flag 2

	while(p!=root)
	{
		//to differentiate left and right child
		//make flag of left child of parent p as 0 &
		//make flag of right child of parent p as 1

		//if p->lp not thread and lp (may be predecessor) not already visited
		if(p->lt==false && p->lp->flag!=2)
		{
			p=p->lp;
			p->flag=0;
		}
		//if p->rp not thread and rp (may be successor) not already visited
		else if(p->rt==false && p->rp->flag!=2)
		{
			p=p->rp;
			p->flag=1;
		}
		else
		{
			printf("  %d",p->data);
			if(p->flag==0)             //if p,left child of parent follow inorder successor i.e right pointer
			{
				p->flag=2;
				while(p->rt==false)
					p=p->rp;
				p=p->rp;
			}
			else                       //if p,right child of parent follow inorder predeccessor i.e left pointer
			{
				p->flag=2;
				while(p->lt==false)
					p=p->lp;
				p=p->lp;
			}
		}
	}
	//reset flags to zero for future use
	//to do so preorder traversal technique
	//is used and flags are initialized to 0
	p=root->lp;
	while(p!=root)
	{
		p->flag=0;
		while(p->lt==false)
		{
			p=p->lp;
			p->flag=0;
		}
		while(p->rt==true)
		{
			p=p->rp;
		}
		p=p->rp;
	}
}