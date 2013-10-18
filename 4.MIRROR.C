#include<stdio.h>
#include<stdlib.h>

#define MAX 100

typedef struct btree
{
	struct btree *lp;
	int data;
	struct btree *rp;
}btree;

typedef struct queue
{
	btree *ptr;    //pointer of type btree,queue stores the pointers of the btree type
	struct queue *link;
}Queue;

int ln=0,i=0;
Queue *front,*rear;
									 //tree function
btree *getnode();
void create(btree **,int);
btree *create_m(btree *,btree *);

void inorder(btree *);               //display functions for tree
void preorder(btree *);
void postorder(btree *);

void countl_nodes(btree *);          //count leaf nodes

int height(btree *,int);             //height of the tree

void initQ();                        //functions for queue
int isQempty();
void addQ(btree *);
btree *delQ();

int main()
{
	int ch,v,h;
	btree *root=NULL,*mroot=NULL;

	do
	{
		printf("\n\t\t\tMirror Image program");
		printf("\n\t\t\t--------------------");
		printf("\n\n\t\t\t0. Exit");
		printf("\n\t\t\t1. Create the binary tree");
		printf("\n\t\t\t2. Inorder Display");
		printf("\n\t\t\t3. Preorder Display");
		printf("\n\t\t\t4. Postorder Display");
		printf("\n\t\t\t5. Display/Count Leaf Nodes");
		printf("\n\t\t\t6. Display Mirror Image of original tree");
		printf("\n\t\t\t7. Display Levelwise");
		printf("\n\t\t\t8. Find Height of the tree");
		printf("\n\n\t\tEnter the choice->");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:
					do
					{
						printf("\n\nEnter the data: ");
						scanf("%d",&v);
						create(&root,v);
						printf("\nDo you want to continue? ");
					}while(getchar()=='y' || getchar()=='Y');
					break;
			case 2:
					if(root==NULL)
						printf("\nCreate the tree first!!");
					else
					{
						printf("\nInorder Display\n\n");
						inorder(root);
					}
					break;
			case 3:
					if(root==NULL)
						printf("\nCreate the tree first!!");
					else
					{
						printf("\nPreorder Display\n\n");
						preorder(root);
					}
					break;
			case 4:
					if(root==NULL)
						printf("\nCreate the tree first!!");
					else
					{
						printf("\nPostorder Display\n\n");
						postorder(root);
					}
					break;
			case 5:
					ln=0;
					if(root==NULL)
						printf("\nCreate the tree first!!");
					else
					{
						printf("\nInorder display->");
						inorder(root);
						printf("\n\nLeaf Nodes->");
						countl_nodes(root);
						printf("\n\nTotal leaf nodes are->%d",ln);
					}
					break;
			case 6:
					if(root==NULL)
						printf("\nCreate the tree first!!");
					else
					{
						printf("\nMirror Imgage of tree->\n\n");
						inorder(root);
						printf(" Mirror  ");
						mroot=create_m(root,mroot);
						inorder(mroot);
					}
					break;
			case 7:
					if(root==NULL)
						printf("\nCreate the tree first!!");
					else
					{
						printf("\nOriginal tree->\n");
						h=height(root,1);
						printf("\n");
						if(mroot==NULL)
						{
							printf("\nCreate the mirror image of the tree first to display mirror image tree!\n");
							printf("\nChoose option 6th to create mirror image!!!");
						}
						else
						{
							printf("\nMirror image tree->\n");
							h=height(mroot,1);
						}
					}
					break;
			case 8:
					if(root==NULL)
						printf("\nCreate the tree first");
					else
					{
						if(root!=NULL)
							h=height(root,0);
						printf("\nHeight of the tree is->%d",h);
					}
					break;
		}
	}while(ch!=0);
	return 0;
}
btree *getnode()
{
	btree *n;
	n=(btree *)malloc(sizeof(btree));
	n->lp=NULL;
	n->data=0;
	n->rp=NULL;
	return n;
}
void create(btree **r,int v)
{
	btree *temp,*parent,*n;
	n=getnode();
	n->data=v;
	if(*r==NULL)
	{
		*r=n;
		return;
	}
	else        //creates original tree
	{
		temp=*r;
		while(temp!=NULL)
		{
			if(v==temp->data)
			{
				printf("\nNode already exists.");
				getchar();
				free(n);
				return;
			}
			else if(v<temp->data)
			{
				parent=temp;
				temp=temp->lp;
			}
			else
			{
				parent=temp;
				temp=temp->rp;
			}
		}
		if(v<parent->data)
			parent->lp=n;
		else
			parent->rp=n;
	}
}
btree *create_m(btree *r,btree *mr)    	//creates mirror image tree
{
	if(r!=NULL)
	{
		mr=getnode();
		mr->data=r->data;
		mr->lp=create_m(r->rp,mr->lp);
		mr->rp=create_m(r->lp,mr->rp);
	}
	return mr;
}
void inorder(btree *r)
{
	if(r!=NULL)
	{
		inorder(r->lp);
		printf("%d  ",r->data);
		inorder(r->rp);
	}
}
void preorder(btree *r)
{
	if(r!=NULL)
	{
		printf("%d  ",r->data);
		preorder(r->lp);
		preorder(r->rp);
	}
}
void postorder(btree *r)
{
	if(r!=NULL)
	{
		postorder(r->lp);
		postorder(r->rp);
		printf("%d  ",r->data);
	}
}
void countl_nodes(btree *root)
{
	if(root!=NULL)
	{
		countl_nodes(root->lp);
		if(root->lp==NULL && root->rp==NULL)
		{
			printf("%d  ",root->data);
			ln++;
		}
		countl_nodes(root->rp);
	}
}
int height(btree *root,int choice)
{
	int h=0;
	btree *temp,*null=NULL;

	temp=root;
	initQ();
	addQ(temp);
	addQ(null);
	if(choice==1)
		printf("\nLevel:%d-> ",h);
	do
	{
		temp=delQ();                    //null is removed whn a level ends
		if(choice==1)
			if(temp!=null)
				printf("%d  ",temp->data);
		if(temp==NULL)
		{
			if(!isQempty())           //important condition
			{
				h++;
				if(choice==1)
					printf("\nLevel:%d-> ",h);
				addQ(null);    //add null to queue
			}
		}
		else
		{
			if(temp->lp)
				addQ(temp->lp);
			if(temp->rp)
				addQ(temp->rp);
		}
	}while(!isQempty());         //continue till queue not empty
	return h;
}
btree *delQ()     //deletes first node of queue and returns ptr of it
{
	btree *temp;
	Queue *temp1;

	temp=front->ptr;
	temp1=front;
	front=front->link;
	free(temp1);

	return temp;
}
int isQempty()
{
	if(front==NULL)
		return 1;
	return 0;
}
void initQ()
{
	front=rear=NULL;
}
void addQ(btree *temp)
{
	Queue *temp1;
	if(front==NULL)
	{
		temp1=(Queue *)malloc(sizeof(Queue));
		temp1->ptr=temp;
		temp1->link=NULL;
		front=temp1;
		rear=temp1;
	}
	else
	{
		temp1=(Queue *)malloc(sizeof(Queue));
		temp1->ptr=temp;
		rear->link=temp1;
		temp1->link=NULL;
		rear=rear->link;
	}
}