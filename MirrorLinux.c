#include<stdio.h>
#include<malloc.h>
#define MAX 100

typedef struct BinaryTree
{
	struct BinaryTree *left;
	int data;
	struct BinaryTree *right;
}Btree;

typedef struct queue
{
	int front,rear;
	Btree *item[MAX];
}Queue;

Queue Q;
int countNode;


Btree* getNode();
void insert(Btree **,int,int); //creates Binary Search tree

//---------------------------------------------------------------------------------
//displays tree in inorder manner
void inOrder(Btree *root)
{
	if(root!=NULL)
	{
		inOrder(root->left);
		printf("%d ",root->data);
		inOrder(root->right);
	}
}
//displays tree in preorder manner
void preOrder(Btree *root)
{
	if(root!=NULL)
	{
		printf("%d ",root->data);
		preOrder(root->left);
		preOrder(root->right);
	}
}
//displays tree in postorder manner
void postOrder(Btree *root)
{
	if(root!=NULL)
	{
		postOrder(root->left);
		postOrder(root->right);
		printf("%d ",root->data);
	}
}//------------------------/
void makeMirror(Btree *,Btree **); //creates mirror of * into **
void levelWise(Btree *,int);
void countLeafNodes(Btree *);

/*-------------------------Queue operating functions*/
void initQ()
{
	int i;
	Q.front=Q.rear=-1;
	for(i=0; i<MAX; i++)
		Q.item[i]=NULL;
}
void addQ(Btree *temp)  //adds element to the queue 
{
	if((Q.rear==MAX-1 && Q.front==0) || (Q.rear+1==Q.front))
	{
		printf("\nQueue is full!!!!");
		return;
	}
	if(Q.rear==MAX-1)
		Q.rear=0;
	else
		Q.rear++;

	Q.item[Q.rear]=temp;

	if(Q.front==-1)
		Q.front=0;
}
Btree *delQ()  //deletes element from queue
{
	Btree *temp;
	if(Q.front==-1)
	{
		printf("\nQueue is empty !!!");
		return NULL;
	}

	temp=Q.item[Q.front];
	Q.item[Q.front]=NULL;

	if(Q.front==Q.rear)
	{
		Q.front=-1;
		Q.rear=-1;
	}
	else
	{
		if(Q.front==MAX-1)
			Q.front=0;
		else
			Q.front++;
	}
	return temp;
}
int isQEmpty() //used to check whether queue is empty or not
{
	return(Q.front==-1);
}


void
 main()
{
	int ch,d;
	Btree *root=NULL,*mirror=NULL;
	initQ();
	do{
		printf("\n\t\t\t0.Exit");
		printf("\n\t\t\t1.Insert into tree");
		printf("\n\t\t\t2.Inorder display");
		printf("\n\t\t\t3.Preoder display");
		printf("\n\t\t\t4.Postorder display");
		printf("\n\t\t\t5.Mirror");
		printf("\n\t\t\t6.Height");
		printf("\n\t\t\t7.Leaf node");
		printf("\n\t\t\t8.Display Original and Mirror levelwise");
		printf("\n\t\t\tYour Choice : ");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:
				printf("\nEnter value in tree : ");
				scanf("%d",&d);
				insert(&root,d,0);
				break;
			case 2:
				printf("\n");
				inOrder(root);
				break;
			case 3:
				printf("\n");
				preOrder(root);
				break;
			case 4:
				printf("\n");
				postOrder(root);
				break;
			case 5:
				mirror=NULL;
				makeMirror(root,&mirror);
				printf("\n");
				inOrder(root);
				printf("<--Mirror Image--> ");
				inOrder(mirror);
				printf("\n");
				break;
			case 6:
				initQ();
				levelWise(root,1);
				break;
			case 7:
				countNode=0;
				countLeafNodes(root);
				if(countNode==1)
					printf("\n%d leaf node found.",countNode);
				else
					printf("\n%d leaf nodes found.",countNode);
				break;
			case 8:
				printf("\nOriginal Tree");
				levelWise(root,0);
				printf("\n\nMirror Tree");
				levelWise(mirror,0);
				break;
		}
	}while(ch!=0);
}

//allocates memory and returns address of it
Btree *getNode()
{
	Btree *n;
	n=(Btree *)malloc(sizeof(Btree));
	n->left=NULL;
	n->data=0;
	n->right=NULL;
	return n;
}
//creates binary tree in with original & reverse logic
void insert(Btree **root,int d,int dir)
{
	Btree *temp,*temp1,*n;
	n=getNode();
	n->data=d;
	if(*root==NULL)
	{
		(*root)=n;
	}
	//creates tree like SMALL VALUE<-ROOT VAL->BIG VALUE
	else if(dir==0)
	{
		temp=*root;
		while(temp!=NULL)
		{
			if(d==temp->data)
			{
				printf("\n%d already exist.",d);
				free(n);
				return;
			}
			else if(d < temp->data)
			{
				temp1=temp;
				temp=temp->left;
			}
			else
			{
				temp1=temp;
				temp=temp->right;
			}
		}
		if(d < temp1->data)
			temp1->left=n;
		else
			temp1->right=n;
	}
	else //creates tree like BIG VALUE<-ROOT VAL->SMALL VALUE
	{
		temp=*root;
		while(temp!=NULL)
		{
			if(d > temp->data)
			{
				temp1=temp;
				temp=temp->left;
			}
			else
			{
				temp1=temp;
				temp=temp->right;
			}
		}
		if(d > temp1->data)
			temp1->left=n;
		else
			temp1->right=n;
	}
}

//creates mirror of Btree * into Btree **
void makeMirror(Btree *root,Btree **m)
{
	if(root!=NULL)
	{
		insert(m,root->data,1);
		makeMirror(root->left,m);
		makeMirror(root->right,m);
	}
}
void levelWise(Btree *root,int option)
{
	int level=0;
	Btree *temp=root,*dummy=NULL;
	if(temp==NULL)
	{
		printf("\nTree is empty.");
		return;
	}
	addQ(temp);
	addQ(dummy);
	if(option==0)
		printf("\nLevel  %d : ",level);
	do
	{
		temp=delQ();
		if(option==0)
			if(temp!=dummy)
				printf("%6d ",temp->data);
		if(temp==dummy)
		{
			if(!isQEmpty())
			{
				level++;
				if(option==0)
					printf("\nLevel  %d : ",level);
				addQ(dummy);
			}
		}
		else
		{
			if(temp->left)
				addQ(temp->left);
			if(temp->right)
				addQ(temp->right);
		}

	}while(!isQEmpty());

	if(option==1)
		printf("\nThe height of tree : %d",level+1);
}
void countLeafNodes(Btree *root)
{
	if(root!=NULL)
	{
		countLeafNodes(root->left);
		if(root->left==NULL && root->right==NULL)
		{
			printf("%d ",root->data);
			countNode++;
		}
		countLeafNodes(root->right);
	}
}
