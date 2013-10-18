#include<stdio.h>
#include<conio.h>
#define MAX 100

typedef struct btree
{
	struct btree *lp;
	int data;
	struct btree *rp;
}btree;
typedef struct queue
{
	btree *arr[MAX];    //array of pointers of type btree,queue stores the pointers
	struct queue *link,*rear;
}Queue;
int ln=0,i=0;
Queue *Q;

btree *getnode();
void create(btree **,int);
btree *create_m(btree *,btree *);

void inorder(btree *);
void preorder(btree *);
void postorder(btree *);

void countl_nodes(btree *);

int height(btree *);

void initQ(Queue *);
int isQempty(Queue *);
void addQ(btree *);
btree *delQ();

void main()
{
	int ch,v,h;
	btree *root=NULL,*mroot=NULL;

	do
	{
		clrscr();
		printf("\n\t\t\tMirror Image program");
		printf("\n\n\t\t\t0. Exit");
		printf("\n\t\t\t1. Create the binary tree");
		printf("\n\t\t\t2. Inorder Display");
		printf("\n\t\t\t3. Preorder Display");
		printf("\n\t\t\t4. Postorder Display");
		printf("\n\t\t\t5. Display Mirror Image of original tree");
		printf("\n\t\t\t6. Display/Count Leaf Nodes");
		printf("\n\t\t\t7. Display Levelwise");
		printf("\n\t\t\t8. Find Height of the tree");
		printf("\n\n\t\tEnter the choice->");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:
					clrscr();
					printf("\nEnter the data->");
					scanf("%d",&v);
					create(&root,v);
					break;
			case 2:
					clrscr();
					printf("\nInorder Display\n\n");
					inorder(root);
					getch();
					break;
			case 3:
					clrscr();
					printf("\nPreorder Display\n\n");
					preorder(root);
					getch();
					break;
			case 4:
					clrscr();
					printf("\nPostorder Display\n\n");
					postorder(root);
					getch();
					break;
			case 5:
					clrscr();
					printf("\nMirror Imgage of tree->\n\n");
					inorder(root);
					printf(" Mirror  ");
					mroot=create_m(root,mroot);
					inorder(mroot);
					getch();
					break;
			case 6:
					clrscr();
					printf("\nInorder display->");
					inorder(root);
					printf("\n\nLeaf Nodes->");
					countl_nodes(root);
					printf("\n\nTotal leaf nodes are->%d",ln);
					getch();
					break;
			case 8:
					clrscr();
					if(root!=NULL)
						h=height(root);
					printf("\nHeight of the tree is->%d",h+1);
					getch();
					break;
		}
	}while(ch!=0);
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
	btree *temp,*temp1,*n;
	n=getnode();
	n->data=v;
	if(*r==NULL)
	{
		*r=n;
	}
	else        //creates original tree
	{
		temp=*r;
		while(temp!=NULL)
		{
			if(v==temp->data)
			{
				printf("\nNode already exists.");
				free(n);
				return;
			}
			else if(v<temp->data)
			{
				temp1=temp;
				temp=temp->lp;
			}
			else
			{
				temp1=temp;
				temp=temp->rp;
			}
		}
		if(v<temp1->data)
			temp1->lp=n;
		else
			temp1->rp=n;
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
	btree *temp;
	temp=r;
	if(temp!=NULL)
	{
		inorder(temp->lp);
		printf("%d  ",temp->data);
		inorder(temp->rp);
	}
}
void preorder(btree *r)
{
	btree *temp;
	temp=r;
	if(temp!=NULL)
	{
		printf("%d  ",temp->data);
		preorder(temp->lp);
		preorder(temp->rp);
	}
}
void postorder(btree *r)
{
	btree *temp;
	temp=r;
	if(temp!=NULL)
	{
		postorder(temp->lp);
		postorder(temp->rp);
		printf("%d  ",temp->data);
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
int height(btree *root)
{
	int h=0;
	btree *temp,*null=NULL;
	if(root->lp==NULL && root->rp==NULL)
		return 0;
	temp=root;
	initQ(Q);
	addQ(temp);
	addQ(null);
	do
	{
		temp=delQ();
		if(temp==NULL)
		{
			if(!isQempty(Q))
			{
				h++;
				addQ(null);
			}
		}
		else
		{
			if(temp->lp)
				addQ(temp->lp);
			if(temp->rp)
				addQ(temp->rp);
		}
	}while(!isQempty(Q));         //continue till queue not empty
	return h;
}
btree *delQ()     //deletes first node of queue and returns address
{
	Queue *temp;
	btree *temp1;

	temp=Q;
	Q->rear=temp->link;
	Q=temp->link;
	temp1=temp->arr[0];
	free(temp);
	return temp1;

}
int isQempty(Queue *Q)
{
	if(Q->rear==NULL)
		return 1;
	return 0;
}
void initQ(Queue *q)
{
	q->rear=q->link=NULL;
}
void addQ(btree *temp)
{
	Queue *p,*temp1,*temp2;
	temp1=Q;
	if(Q->rear==NULL)      //if first element to be added in queue
	{
		p=(Queue *)malloc(sizeof(Queue));
		p->arr[i]=temp;
		Q=p;
		Q->rear=Q->link=Q;
		temp1=Q;
		i++;
//		return;
	}
	else
	{
		p=(Queue *)malloc(sizeof(Queue));
		if(temp==NULL)            //if null pointer to be added to queue
		{
			p->arr[i]=temp;
			i++;
			while(temp1->rear!=Q)  //traverse temp1 upto last node of queue
			{
				temp1=temp1->link;
			}
			p->rear=Q;
			temp1->link=p;
//			return;
		}
/*		else
		{
			while(temp1!=Q->arr[i])  //traverse temp1 upto last node of queue
				{
					temp1=temp1->link;
				}
			p->arr[i]=temp;
			i++;
			p->rear=Q;
			temp1->link=p;
		}
		return;
*/
	}
}