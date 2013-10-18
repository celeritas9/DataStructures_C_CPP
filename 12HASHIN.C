#include<stdio.h>
#include<conio.h>
#define MAX 10

typedef struct hashkey
{
	int key,chain,status;                   //status maintains whether key
											//is deleted or not
}hashkey;

int hash(int);
void insert1();
void insert2();
void display();
int search(int);
void del(int);

int hashtable[MAX];
hashkey hashstruct[MAX];

void main()
{
	int ch,ch1,i,index,keyval;
	for(i=0;i<MAX;i++)
	{
		hashtable[i]=-1;
		hashstruct[i].key=-1;
		hashstruct[i].chain=-1;
	}
	for(i=0;i<MAX;i++)
	{
		hashstruct[i].status=0;
	}

	do
	{
		clrscr();
		printf("\t\tHashing Program : Linear Probing\n");
		printf("\t\t--------------------------------\n");
		printf("\n\t\t0. Exit");
		printf("\n\t\t1. Without Chaining/Without Replacement");
		printf("\n\t\t2. With Chaining/With Replacement");
		printf("\n\tYour Choice-> ");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:
				do
				{
					clrscr();
					printf("\t\tLinear Probing : Without Chaining/Without Replacement\n");
					printf("\t\t-----------------------------------------------------\n");
					printf("\n\t\t0. Exit");
					printf("\n\t\t1. Insert");
					printf("\n\t\t2. Search");
					printf("\n\t\t3. Delete");
					printf("\n\t\t4. Display");
					printf("\n\tYour Choice-> ");
					scanf("%d",&ch1);
					switch(ch1)
					{
						case 1:
								clrscr();
								insert1();
								break;
						case 2:
								clrscr();
								printf("\nEnter the key to search: ");
								scanf("%d",&keyval);
								index=search(keyval);
								if(index!=-1)
									printf("\n\tKey found at: %d",index);
								else
									printf("\n\tKey not found!!!");
								getch();
								break;
						case 3:
								printf("\nEnter the key to delete: ");
								scanf("%d",&keyval);
								del(keyval);
								break;
						case 4:
								display();
								getch();
								break;
					}
				}while(ch1!=0);
				break;
			case 2:
				do
				{
					clrscr();
					printf("\t\tLinear Probing : With Chaining/With Replacement\n");
					printf("\t\t-----------------------------------------------\n");
					printf("\n\t\t0. Exit");
					printf("\n\t\t1. Insert");
					printf("\n\t\t2. Search");
					printf("\n\t\t3. Delete");
					printf("\n\t\t4. Display");
					printf("\n\tYour Choice-> ");
					scanf("%d",&ch1);
					switch(ch1)
					{
						case 1:
								clrscr();
								insert2();
								break;
						case 2:
								break;
						case 3:
								break;
						case 4:
								break;
					}
				}while(ch1!=0);
				break;
		}
	}while(ch!=0);
}
int hash(int val)
{
	int index;
	index=val%MAX;
	return index;
}
void insert1()
{
	int val,index,current;
	printf("\nEnter the key to insert: ");
	scanf("%d",&val);
	index=hash(val);
	if(hashtable[index]==-1)
	{
		hashtable[index]=val;
	}
	else
	{
		current=index;
		while(hashtable[index]!=-1)
		{
			index++;
			if(index==current)
			{
				printf("\n\n\t\tHash table is Full!!!");
				getch();
				return;
			}
			if(index==MAX)
				index=0;
		}
		hashtable[index]=val;
	}
}
void insert2()
{
	int val,index,current,deletedkey,deletedchain;
	printf("\nEnter the key to insert: ");
	scanf("%d",&val);
	index=hash(val);
	if(hashstruct[index].key==-1)
	{
		hashstruct[index].key=val;
		return;
	}
	while(hashstruct[index].key!=-1)
	{
		current=index;
		if(hash(hashstruct[index].key)==index && hashstruct[index].chain==-1 && hashstruct[index+1].key==-1)
		{
			while(hashstruct[index].key!=-1)
			{
				index++;
				if(index==MAX)
					index=0;
			}
			index--;
			hashstruct[index].chain=index+1;
			index++;
			hashstruct[index].key=val;
			return;
		}
		//if already a wrong value in index
		else if(hash(val)!=hash(hashstruct[index].key))
		{
			deletedkey=hashstruct[index].key;
			hashstruct[index].key=val;
			deletedchain=hashstruct[index].chain;
			hashstruct[index].chain=-1;
			//search for the next empty slot to insert deleted value
			while(hashstruct[index].key!=-1)
			{
				index++;
				if(index==MAX)
					index=0;
			}
			hashstruct[current-1].chain=index;
			hashstruct[index].key=deletedkey;
			hashstruct[index].chain=deletedchain;
		}
/*		if(hashstruct[index].chain==-1 && hashstruct[index+1].key==-1)
		{
			hashstruct[index].chain=index+1;
			index++;
			hashstruct[index].key=val;
			return;
		}
*/
		index++;
		if(index==current)
		{
			printf("\n\n\t\tHash table is Full!!!");
			getch();
			return;
		}
		if(index==MAX)
			index=0;
	}
}

void display()
{
	int i;
	printf("\n\t\tHash table");
	printf("\n\t\t----------");
	printf("\n\tNote: -1 indicates element not inserted yet!!!");
	printf("\n\t-----");
	printf("\n\n");
	for(i=0;i<MAX;i++)
		printf("\t\t(%d)     %d\n",i,hashtable[i]);
}
int search(int keyval)
{
	int index,current;
	index=hash(keyval);
	if(keyval==hashtable[index])
		return index;
	current=index;
	do
	{
		if(index==MAX)
			index=0;
		else
			index++;
		if(hashtable[index]==keyval)
			return index;
	}while(index!=current);
	return -1;
}
void del(int keyval)
{
	int index,current;
	index=hash(keyval);
	if(keyval==hashtable[index])
	{
		hashtable[index]=-1;
		printf("\n\n\t\tElement successfully deleted!!!");
		getch();
		return;
	}
	current=index;
	do
	{
		if(index==MAX)
			index=0;
		else
			index++;
		if(hashtable[index]==keyval)
		{
			hashtable[index]=-1;
			printf("\n\n\t\tElement successfully deleted!!!");
			getch();
			return;
		}
	}while(index!=current);
	printf("\nElement doesn't exist!!!");
	getch();
}