#include<stdio.h>
#include<conio.h>
struct binaryTree
{
	struct binaryTree *left;
	int data;
	struct binaryTree *right;
};
struct binaryTree* getNode();
void insert(struct binaryTree **);
void del(struct binaryTree *);
void preorder(struct binaryTree *);
void inorder(struct binaryTree *);
void postorder(struct binaryTree *);
struct binaryTree* search(struct binaryTree *,int);
void main()
{
	int ch,key;
	struct binaryTree *root,*found;
	root=NULL;
	do
	{
		clrscr();
			printf("\t\tBinary Tree Program");
			printf("\n\t\t0. Exit");
			printf("\n\t\t1. Insert Node");
			printf("\n\t\t2. Delete Node");
			printf("\n\t\t3. Display in preorder");
			printf("\n\t\t4. Display in inorder");
			printf("\n\t\t5. Display in postorder");
			printf("\n\t\t6. Search");
			printf("\n\t\tYour Choice : ");
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
struct binaryTree* getNode()
{
	return (struct binaryTree *)malloc(sizeof(struct binaryTree));
}
void insert(struct binaryTree **n)
{
	struct binaryTree *temp,*temp1,*temp2;
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
		while(temp2!=NULL)
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
void inorder(struct binaryTree *n)
{
	if(n!=NULL)
	{
		inorder(n->left);
		printf("%d ",n->data);
		inorder(n->right);
	}
}
void preorder(struct binaryTree *n)
{
	if(n!=NULL)
	{
		printf("%d ",n->data);
		preorder(n->left);
		preorder(n->right);
	}
}
void postorder(struct binaryTree *n)
{
	if(n!=NULL)
	{
		postorder(n->left);
		postorder(n->right);
		printf("%d ",n->data);
	}
}
struct binaryTree* search(struct binaryTree *n,int key)
{
		struct binaryTree *temp,*temp1;
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
void del(struct binaryTree *root)
{
	int d;
	struct binaryTree *temp,*parent,*dp;

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