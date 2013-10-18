#include<stdio.h>
#include<conio.h>

typedef struct bTree
{
	struct bTree *left;
	int data;
	struct bTree *right;
}bTree;

bTree* getNode();
void insert(bTree **);
void del(bTree *);
void preorder(bTree *);
void inorder(bTree *);
void postorder(bTree *);
bTree* search(bTree *,int);

void main()
{
	int ch,key;
	bTree *root,*found;
	root=NULL;
	do
	{
		clrscr();
		printf("\t\tBinary Tree Program");
		printf("\n\t\t0. Exit");
		printf("\n\t\t1. Insert Node");
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
				insert(&root);
				break;
			case 2:
				clrscr();
				del(root);
				getch();
				break;
			case 3:
				clrscr();
				printf("\nPreoder Printing\n\n");
				preorder(root);
				getch();
				break;
			case 4:
				clrscr();
				printf("\nInoder Printing\n\n");
				inorder(root);
				getch();
				break;
			case 5:
				clrscr();
				printf("\nPostoder Printing\n\n");
				postorder(root);
				getch();
				break;
			case 6:
				printf("\nEnter the data to search\n");
				scanf("%d",&key);
				found=search(root,key);
				if(found==NULL)
					printf("\nNot Found");
				else
					printf("\nFound");
				getch();
				break;
		}
	}while(ch!=0);
}
bTree* getNode()
{
	return (bTree *)malloc(sizeof(bTree));
}
void insert(bTree **n)
{
	bTree *temp,*temp1,*temp2;
	int d;
	clrscr();
	printf("\nEnter the data for new node in binary tree \n");
	scanf("%d",&d);
	temp=getNode();
	temp1=*n;
	temp->left=NULL;
	temp->data=d;
	temp->right=NULL;

	if(*n==NULL)
	{
		*n=temp;
	}
	else
	{
		temp2=temp1;
		while(temp2!=NULL) //this condi is useful whn node is deleted
		{
			if(temp2->data<d)
			{
				temp1=temp2;
				temp2=temp2->right;
			}
			else
			{
				temp1=temp2;
				temp2=temp2->left;
			}
		}
		if(temp1->data<d)
		{
			temp1->right=temp;
		}
		else
		{
			temp1->left=temp;
		}
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
bTree* search(bTree *n,int key)
{
		bTree *temp,*temp1;
		temp=n;
		if(n==NULL)
		{
			printf("\nBinary tree is empty.");
			getch();
			return NULL;
		}
		else
		{
			while(temp!=NULL)
			{
				if(temp->data<key)
				{
					temp=temp->right;
				}
				else if(temp->data>key)
				{
					temp=temp->left;
				}
				else if(temp->data==key)
				{
					return temp;
				}
			}
		}
		return NULL;
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
	parent=NULL;                     //parent is parent of node to be deleted
	temp=root;                       //temp used to traverse to right node

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

	/*Deletion of node having no children*/
	if(temp->left==NULL && temp->right==NULL)
	{
		if(temp==root)
		{
			root=NULL;
			free(temp);
			return;
		}
		if(temp->data < parent->data)    //if left child is being deleted
			parent->left=NULL;
		else
			parent->right=NULL;          //if right child is being deleted

		free(temp);
		return;
	}
	/*node having 2 children*/
	if(temp->left!=NULL && temp->right!=NULL)
	{
		/*we have found inorder predecessor	*/
		dp=temp->left;
		if(dp->right==NULL)
		{
			temp->left=dp->left;
			temp->data=dp->data;
			free(dp);
		}
		else
		{
			while(dp->right!=NULL)
			{
				parent=dp;
				dp=dp->right;
			}
			parent->right=dp->left;
			temp->data=dp->data;
			free(dp);
		}
		return;
	}
	/*node having 1 child*/
	if(temp->left!=NULL || temp->right!=NULL)
	{
		if(parent->data<temp->data)
			if(temp->left!=NULL)
				parent->right=temp->left;
			else
				parent->right=temp->right;
		else
			if(temp->left!=NULL)
				parent->left=temp->left;
			else
				parent->left=temp->right;
		free(temp);
	}

}