#include<stdio.h>
#include<malloc.h>

typedef struct bTree
{
	struct bTree *left;
	int data;
	struct bTree *right;
}bTree;

bTree* getNode();
void insert(bTree **,int);
void del(bTree *);
void preorder(bTree *);
void inorder(bTree *);
void postorder(bTree *);
int search(bTree *,int);

void main()
{
	int ch,key,found;
	char c;
	bTree *root;
	root=NULL;
	do
	{
		printf("\t\tBinary Tree Program");
		printf("\n\t\t0. Exit");
		printf("\n\t\t1. Create Tree/Insert Node");
		printf("\n\t\t2. Delete Node");
		printf("\n\t\t3. Preorder Display");
		printf("\n\t\t4. Inorder Display");
		printf("\n\t\t5. Postorder Display");
		printf("\n\t\t6. Search");
		printf("\n\t\tYour Choice-> ");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:
				do{
					printf("\n\nEnter the data for new node in binary tree: ");
					scanf("%d",&key);
					insert(&root,key);
					printf("\nDo you want to continue?  ");
					scanf("%c", c);
				}while(c=='y' || c=='Y');
				break;
			case 2:
				del(root);
				break;
			case 3:
				printf("\nPreoder Printing\n\n");
				preorder(root);
				break;
			case 4:
				printf("\nInoder Printing\n\n");
				inorder(root);
				break;
			case 5:
				printf("\nPostoder Printing\n\n");
				postorder(root);
				break;
			case 6:
				printf("\nEnter the data to search\n");
				scanf("%d",&key);
				found=search(root,key);
				if(found==0)
					printf("\nNot Found");
				else
					printf("\nFound");
				break;
		}
	}while(ch!=0);
}
bTree* getNode()
{
	return (bTree *)malloc(sizeof(bTree));
}
void insert(bTree **n,int d)
{
	if(*n==NULL)
	{
		(*n)=getNode();
		(*n)->left=NULL;
		(*n)->data=d;
		(*n)->right=NULL;
	}
	else
	{
		if(d==(*n)->data)
			printf("\nValue already exist!!!");
		if(d < (*n)->data)
			insert(&(*n)->left,d);
		if(d > (*n)->data)
			insert(&(*n)->right,d);
	}
}
void inorder(bTree *n)
{
	if(n!=NULL)
	{
		inorder(n->left);
		printf("%d ",n->data);
		inorder(n->right);
	}
}
void preorder(bTree *n)
{
	if(n!=NULL)
	{
		printf("%d ",n->data);
		preorder(n->left);
		preorder(n->right);
	}
}
void postorder(bTree *n)
{
	if(n!=NULL)
	{
		postorder(n->left);
		postorder(n->right);
		printf("%d ",n->data);
	}
}
int search(bTree *n,int key)
{
	bTree *temp;
	temp=n;
	if(n==NULL)
	{
		printf("\nBinary tree is empty.");
		return 0;
	}
	else
	{
		while(temp!=NULL)
		{
			if(temp->data < key)
				temp=temp->right;
			else if(temp->data > key)
				temp=temp->left;
			else if(temp->data==key)
				return 1;
		}
	}
	return 0;
}
void del(bTree *root)
{
	int d;
	bTree *temp,*parent,*dp;

	if(root==NULL)
	{
		printf("Binary Tree is empty.");
		return;
	}
	inorder(root);
	printf("\nEnter the data u want to delete : ");
	scanf("%d",&d);
	parent=NULL;
	temp=root;

	while(temp!=NULL)
	{
		if(temp->data==d)
			break;
		parent=temp;
		if(d < temp->data)
			temp=temp->left;
		else
			temp=temp->right;
	}
	if(temp==NULL)
	{
		printf("\n%d Not Found.",d);
		return;
	}
	//follow the procedure of deletion for
//1. node having no children 2. node with 2 children 3. node with one child

	/*Deletion of node having no children*/
	if(temp->left==NULL && temp->right==NULL)
	{
		if(temp==root)
		{
			root=NULL;
			free(temp);
			return;
		}
		if(temp->data < parent->data)
			parent->left=NULL;
		else
			parent->right=NULL;

		free(temp);
		return;
	}

	/*node having 2 children*/
	if(temp->left!=NULL && temp->right!=NULL)
	{
		/*we have  found inorder successor*/
		//infact here node is not deleted but replaced by inorder successor
		dp=temp->right;
		if(dp->left==NULL)        //if left of dp is NULL i.e dp is in. succ.
		{
			temp->right=dp->right;
			temp->data=dp->data;
			free(dp);
		}
		else
		{
			while(dp->left!=NULL)
			{
				parent=dp;
				dp=dp->left;
			}
			parent->left=dp->right;               //as left of dp is NULL
			temp->data=dp->data;
			free(dp);
		}
		return;
	}

	/*node having 1 child*/
	if(temp->left!=NULL || temp->right!=NULL)
	{
		if(parent->data < temp->data)           //node to b deltd is at right
			if(temp->left!=NULL)                //if left child present
				parent->right=temp->left;
			else                                //right child present
				parent->right=temp->right;
		else
			if(temp->left!=NULL)                //node to b deltd is at left
				parent->left=temp->left;        //if left child present
			else
				parent->left=temp->right;       //right child present
		free(temp);
	}
}