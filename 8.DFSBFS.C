//using Adjacency list

#include<stdio.h>
#include<conio.h>
#define MAX 10

typedef struct node
{
	int vertex;
	struct node *next;
}node;

node *arr_ptr[MAX];
int visited[MAX],q[MAX];
int n,e,front,rear;

//Q required for bfs
void addQ(int);
int delQ();
int isQempty();

void create();
void insert(int,int);
void DFS(int);
void BFS(int);

void main()
{
	int v,ch,i;
	do
	{
		clrscr();
		printf("\n\n\t\tMENU");
		printf("\n\t\t----");
		printf("\n\t0. Exit");
		printf("\n\t1. Create Graph");
		printf("\n\t2. DFS");
		printf("\n\t3. BFS");
		printf("\n\nChoice-> ");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:
					clrscr();
					printf("\n\t\tCreate Graph using Adjacency List");
					printf("\n\t\t---------------------------------\n\n");
					create();
					break;
			case 2:
					clrscr();
					printf("\n\tDepth First Search Algorithm");
					printf("\n\t----------------------------\n\n");
					if(n==1 || e==0)
					{
						printf("  %d",arr_ptr[0]->vertex);
						getch();
						break;
					}
					for(v=0;v<=n;v++)
						visited[v]=0;
					printf("\nEnter the starting vertex: ");
					scanf("%d",&v);
					printf("\n\n");
					DFS(v);
					for(i=0;i<n;i++)
						if(visited[i]==0)
						{
							printf("\nGraph is not connected graph");
							break;
						}
					getch();
					break;
			case 3:
					clrscr();
					printf("\n\tBreadth First Search Algorithm");
					printf("\n\t------------------------------\n\n");
					if(n==1 || e==0)
					{
						printf("  %d",arr_ptr[0]->vertex);
						getch();
						break;
					}
					for(v=0;v<=n;v++)
						visited[v]=0;
					printf("\nEnter the starting vertex: ");
					scanf("%d",&v);
					printf("\n\n");
					BFS(v);
					for(i=0;i<n;i++)
						if(visited[i]==0)
						{
							printf("\nGraph is not connected graph");
							break;
						}
					getch();
					break;
		}
	}while(ch!=0);
}
void create()
{
	node *p;
	int i,v1,v2,v;
	printf("\nEnter the no of vertices: ");
	scanf("%d",&n);
	/* initialize array of pointers */
	for(i=0;i<=n;i++)
		arr_ptr[i]=NULL;
	printf("\nEnter the no of edges: ");
	scanf("%d",&e);
	printf("\n");
	if(n==1 || e==0)
	{
		printf("\nEnter the vertex: ");
		scanf("%d",&v);
		p=(node *)malloc(sizeof(node));
		p->vertex=v;
		p->next=NULL;
		arr_ptr[0]=p;
		return;
	}
	else if(e>n*(n-1)/2)
	{
		printf("\nError : No. of edges exceed!!!\n");
		printf("\nHint  : Complete Bipartite Graph of %d vertices have atmost %d edges!",n,n*(n-1)/2);
		getch();
		return;
	}
	for(i=0;i<e;i++)
	{
		printf("\nEnter an edge(u,v): ");
		scanf("%d%d",&v1,&v2);
		insert(v1,v2);
		insert(v2,v1);
	}
}
void insert(int v1,int v2)
{
	node *p,*q;
	p=(node *)malloc(sizeof(node));
	p->vertex=v2;
	p->next=NULL;
	if(arr_ptr[v1]==NULL)
		arr_ptr[v1]=p;
	else
	{
		q=arr_ptr[v1];
		while(q->next!=NULL)
			q=q->next;
		q->next=p;
	}
}
void DFS(int v)
{
	node *p;

	printf("  %d",v);
	p=arr_ptr[v];
	visited[v]=1;
	while(p!=NULL)
	{
		v=p->vertex;
		if(!visited[v])        //if already visited go to next
			DFS(v);
		p=p->next;
	}
}
void addQ(int v)
{
	if(rear==MAX-1)
	{
		printf("\n\n\t\tError 41: Queue Overflow!!!");
		return;
	}
	rear++;
	q[rear]=v;

	if(front==-1)
		front=0;
}
int delQ()
{
	int data;

	if(front==-1)
	{
		printf("\n\n\t\tError 56: Queue Underflow!!!");
		return NULL;
	}
	data=q[front];
	if(front==rear)
		front=rear=-1;
	else
		front++;

	return data;
}
int isQempty()
{
	if(front==-1)
		return 1;
	return 0;
}
void BFS(int v)
{
	node *p;

	visited[v]=1;
	printf("  %d",v);
	front=rear=-1;
	addQ(v);
	while(!isQempty())                            //while q not empty
	{
		v=delQ();
		p=arr_ptr[v];
		while(p!=NULL)
		{
			if(!visited[p->vertex])
			{
				addQ(p->vertex);
				visited[p->vertex]=1;
				printf("  %d",p->vertex);
			}
			p=p->next;
		}
	}
}