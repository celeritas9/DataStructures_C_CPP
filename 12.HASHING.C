#include<stdio.h>
#include<conio.h>
#define MAX 10

typedef struct hashkey
{
	int key,chain;
}hashkey;

int hash(int);
void insert1();
void insert2();
void display(int);
int search1(int);
int search2(int);
void del1(int);
void del2(int);

int hashtable[MAX];
int status[MAX];
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
		status[i]=0;
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
							index=search1(keyval);
							if(index!=-1)
								printf("\n\tKey found at: %d",index);
							else
								printf("\n\tKey not found!!!");
							getch();
							break;
					case 3:
							printf("\nEnter the key to delete: ");
							scanf("%d",&keyval);
							del1(keyval);
							break;
					case 4:
							display(1);
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
							clrscr();
							printf("\nEnter the key to search: ");
							scanf("%d",&keyval);
							index=search2(keyval);
							if(index!=-1)
								printf("\n\tKey found at: %d",index);
							else
								printf("\n\tKey not found!!!");
							getch();
							break;
					case 3:
							printf("\nEnter the key to delete: ");
							scanf("%d",&keyval);
							del2(keyval);
							break;
					case 4:
							display(2);
							getch();
							break;
				}
			}while(ch1!=0);
			break;				//break for case 2
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
		status[index]=0;
		return;
	}
	else
	{
		current=index;
		//search until empty field comes
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
		status[index]=0;
	}
}
void insert2()
{
	int val,index,current,deletedkey,deletedchain,i=0;
	int current1,flag=0;
	printf("\nEnter the key to insert: ");
	scanf("%d",&val);
	index=hash(val);
	//initially for the first element

	if(hashstruct[index].key==-1)
	{
		hashstruct[index].key=val;
		return;
	}
	//if hashed location doesn't contain a synonym
	if(hash(val)!=hash(hashstruct[index].key))
	{
		current=index;
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
		//search for the key having chain=current to modify the chain
		while(hashstruct[i].chain!=current && i<MAX)
		{
			i++;
		}
		hashstruct[i].chain=index;
		hashstruct[index].key=deletedkey;
		hashstruct[index].chain=deletedchain;
		return;
	}
	current=index;
	//checks for the next empty location
	while(hashstruct[index].key!=-1)
	{
		if(hashstruct[index].chain==-1 && hashstruct[index+1].key==-1 && hash(hashstruct[index].key)==current)
		{
			hashstruct[index].chain=index+1;
			index++;
			hashstruct[index].key=val;
			return;
		}
		index++;
		if(hashstruct[index].chain==-1 && flag==0)
		{
			current1=index;
			flag++;
		}
		if(index==current || current==0)
		{
			printf("\n\n\t\tHash table is Full!!!");
			getch();
			return;
		}
		if(index==MAX)
			index=0;
	}
	hashstruct[index].key=val;
	if(hashstruct[current].chain==-1)
		hashstruct[current].chain=index;
	else
		hashstruct[current1].chain=index;
}
void display(int ch)
{
	int i;
	printf("\n\t\tHash table");
	printf("\n\t\t----------");
	if(ch==1)
	{
		printf("\nNote1: Status maintains whether key is deleted or not(1-deleted,0-not deleted)");
		printf("\n-----");
		printf("\nNote2: -1 indicates element not inserted yet!!!");
		printf("\n-----");
		printf("\n\n");
		printf("\t\tIndex   Key   Status\n");
		printf("\t\t-----   ---   ------\n");
		for(i=0;i<MAX;i++)
			printf("\t\t(%d)     %d     %d\n",i,hashtable[i],status[i]);
		return;
	}
	else
	{
		printf("\n\n");
		printf("\t\tIndex   Key   Chain\n");
		printf("\t\t-----   ---   -----\n");
		for(i=0;i<MAX;i++)
			printf("\t\t(%d)\t%d\t%d\n",i,hashstruct[i].key,hashstruct[i].chain);
	}
}
int search1(int keyval)
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
int search2(int keyval)
{
	int index;
	index=hash(keyval);
	if(hashstruct[index].key==keyval)
	{
		return index;
	}
	else if(hashstruct[index].chain!=-1)
	{
		while(hashstruct[index].key!=keyval && hashstruct[index].chain!=-1)
		{
			index=hashstruct[index].chain;
		}
		if(hashstruct[index].key==keyval)
		{
			return index;
		}
	}
	return -1;
}
void del1(int keyval)
{
	int index,current;
	index=hash(keyval);
	if(keyval==hashtable[index])
	{
		hashtable[index]=-1;
		status[index]=1;
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
			status[index]=1;
			printf("\n\n\t\tElement successfully deleted!!!");
			getch();
			return;
		}
	}while(index!=current);
	printf("\nElement doesn't exist!!!");
	getch();
}
void del2(int keyval)
{
	int index,chain,current;
	index=hash(keyval);
	if(hashstruct[index].key==keyval)
	{
		if(hashstruct[index].chain==-1)
		{
			hashstruct[index].key=-1;
			printf("\n\nKey deleted suyccessfully!!!");
			getch();
			return;
		}
		else if(hashstruct[index].chain!=-1)
		{
			//search element to be deleted if not present at index
			while(hashstruct[index].key!=keyval && hashstruct[index].chain!=-1)
			{
				current=index;
				index=hashstruct[index].chain;
			}
			//has no chain
			if(hashstruct[index].key==keyval && hashstruct[index].chain==-1)
			{
				hashstruct[index].key=-1;
				hashstruct[current].chain=-1;
				printf("\n\nKey deleted suyccessfully!!!");
				getch();
				return;
			}
			//has chain
			else if(hashstruct[index].key==keyval && hashstruct[index].chain!=-1)
			{
				while(hashstruct[index].chain!=-1)
				{
					chain=hashstruct[index].chain;
					hashstruct[index].key=hashstruct[chain].key;
					current=index;
					index=chain;
//					if(index==MAX)
//						index=0;
				}
				if(index==chain)
					hashstruct[current].chain=-1;
				hashstruct[index].key=hashstruct[index].chain=-1;
				printf("\n\nKey deleted successfully!!!");
				getch();
				return;

			}
			//think no need of following else
			else
			{
				while(hashstruct[index].chain!=-1)
				{
					chain=hashstruct[index].chain;
					hashstruct[index]=hashstruct[chain];
					index++;
					if(index==MAX)
						index=0;
				}
				hashstruct[index].key=hashstruct[index].chain=-1;
				printf("\n\nKey deleted suyccessfully!!!");
				getch();
				return;
			}
		}
	}
	//think no need of this else if
	else if(hashstruct[index].chain!=-1)
	{
		while(hashstruct[index].key!=keyval && hashstruct[index].chain!=-1)
		{
			current=index;
			index=hashstruct[index].chain;
		}
		if(hashstruct[index].key==keyval && hashstruct[index].chain!=-1)
		{
			while(hashstruct[index].chain!=-1)
			{
				chain=hashstruct[index].chain;
				hashstruct[index].key=hashstruct[chain].key;
				current=index;
				index=chain;
				if(index==MAX)
					index=0;
			}
			if(index==chain)
				hashstruct[current].chain=-1;
			hashstruct[index].key=hashstruct[index].chain=-1;
			printf("\n\nKey deleted suyccessfully!!!");
			getch();
			return;
		}
		else if(hashstruct[index].key==keyval && hashstruct[index].chain==-1)
		{
			hashstruct[index].key=-1;
			hashstruct[current].chain=-1;
			printf("\n\nKey deleted suyccessfully!!!");
			getch();
			return;
		}
	}
	printf("\n\nKey Not Found!!!");
	getch();
}