#include<stdio.h>
#include<conio.h>

typedef struct sll
{
	struct tree *data;
	struct sll *next;
}node;

typedef struct tree
{
	char ch;
	int freq;
	struct tree *left;
	struct tree *right;
}tree;

tree* gettree();
node* getnode();

void preorder(tree *,int,char);
node* insert(node *,tree *);
node* huff(node*);

char msg[10],msg1[50];

void main()
{
	int option,i,len,f;
	char cch,str[10],ch;
	node *head=NULL;
	tree *temp;
	do
	{
		clrscr();
		printf("\n\n\t\tHuffman's Algotrithm");
		printf("\n\t\t--------------------");
		printf("\n\t0. Exit");
		printf("\n\t1. Create Huffman tree");
		printf("\n\t2. Encode a message");
		printf("\nEnter your choice: ");
		scanf("%d",&option);
		switch(option)
		{
			case 1:
					clrscr();
					do
					{
						printf("\nEnter the character: ");
						flushall();
						scanf("%c",&ch);
						if(!isExist(head,ch))
						{
							printf("\nEnter the frequency: ");
							scanf("%d",&f);
							while(f<0)
							{
								printf("\nEnter the +ve frequency: ");
								scanf("%d",&f);
							}
							temp=gettree();
							temp->ch=ch;
							temp->freq=f;
							//sort while inserting
							head=insert(head,temp);
						}
						printf("\n\nDo you want to continue? ");
					}while(getche()=='y' || getche()=='Y');
					break;
			case 2:
					clrscr();
					flushall();
					head=huff(head);
					//important condition
					temp=head->data;
					printf("\nEnter the message to be encoded: ");
					flushall();
					scanf("%s",str);
					strcpy(msg,NULL);
					strcpy(msg1,NULL);
					i=0;
					printf("\nCharacter \t Bit Pattern \t Frequency");
					printf("\n--------- \t ----------- \t ---------");
					len=strlen(str);
					do
					{
						cch=str[i];
						preorder(temp,0,cch);
						i++;
					}while(len!=i);
					printf("\n\nThe coded message is: %s",msg1);
					flushall();
					getch();
					exit(0);
					break;
		}
	}while(option!=0);
}
tree* gettree()
{
	tree *p;
	p=(tree*)malloc(sizeof(tree));
	p->left=p->right=NULL;
	return p;
}
node* getnode()
{
	node *p;
	p=(node*)malloc(sizeof(node));
	p->next=NULL;
	return p;
}
int isExist(node *head,char ch)
{
	node *temp;
	if(head==NULL)
		return 0;
	else
	{
		temp=head;
		while(temp!=NULL)
		{
			if(temp->data->ch==ch)
			{
				printf("\nThis character already exist!!!\n");
				getch();
				return 1;
			}
			temp=temp->next;
		}
	}
	return 0;
}

void preorder(tree *temp,int i,char cch)
{
	if(temp!=NULL)
	{
		if(temp->ch==cch)
		{
			msg[i]='\0';
			printf("\n%c \t\t %s \t\t %d",cch,msg,temp->freq);
			strcat(msg1,msg);
			return;
		}
		msg[i]='0';
		preorder(temp->left,i+1,cch);
		msg[i]='1';
		preorder(temp->right,i+1,cch);
	}
}
node* insert(node *head,tree *temp)
{
	node *head1,*temp1;

	if(head==NULL || head->data->freq > temp->freq)
	{
		temp1=getnode();
		temp1->data=temp;
		temp1->next=head;
		head=temp1;
	}
	else
	{
		head1=head;
		while(head1!=NULL)
		{
			if(head1->data->freq <= temp->freq && (head1->next->data->freq > temp->freq || head1->next==NULL))
			{
				temp1=getnode();
				temp1->data=temp;
				temp1->next=head1->next;
				head1->next=temp1;
				break;
			}
			head1=head1->next;
		}
	}
	return head;
}
node* huff(node* head)
{
	tree *temp;
	do
	{
		temp=gettree();
		temp->left=head->data;
		temp->right=head->next->data;
		head=head->next->next;
		temp->freq=temp->left->freq+temp->right->freq;
		temp->ch='0';
		head=insert(head,temp);
	}while(head->next!=NULL);
	return head;
}