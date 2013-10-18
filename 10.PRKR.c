#include<stdio.h>
#include<conio.h>
#define MAX 10
#define INF 9999

typedef struct Vertices
{
	int vertex;
	int weight;
	struct Vertices *next;
}Vertices;

//used to create sorted list for kruskal by weights
typedef struct KruskalList
{
	int v1,v2,weight;
	struct KruskalList *next;
}KList;

void createGraph(Vertices **,int,int);
void addVertex(Vertices **,int,int,int);

void prims(Vertices **,int,int);

int found(KList *,int,int);
void createKruskalList(KList **,int,int,int);
void kruskal(Vertices **,int);

void main()
{
	int ch,source;
	Vertices *graph[MAX];
	int v,e;
	do
	{
		clrscr();
		printf("\n\t\t\t0. Exit");
		printf("\n\t\t\t1. Create graph using Adjacency list");
		printf("\n\t\t\t2. Prims Algorithm");
		printf("\n\t\t\t3. Kruskal Algorithm");
		printf("\n\t\t\tYour choice : ");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:
				clrscr();
				printf("\nNote: Any one vertex in graph should be 0");
				printf("\n----");
				printf("\nEnter the number of vertices : ");
				scanf("%d",&v);
				printf("\nEnter the number of edges :");
				scanf("%d",&e);
				printf("\n");
				if(e>v*(v-1)/2)
				{
					printf("\nError : No. of edges exceed!!!\n");
					printf("\nHint  : Complete Bipartite Graph of %d vertices have atmost %d edges!",v,v*(v-1)/2);
					getch();
					break;
				}
				else if(v==0 || v==1 || e==0 || e==1)
				{
					printf("\nError : Minimum no. of vertices should be 3!!!\n");
					printf("\nHint  : Renter no. of edges and no. of vertices");
					getch();
					break;
				}
				else
					createGraph(graph,v,e);
				break;
			case 2:
				clrscr();
				printf("\nEnter the source vertex : ");
				scanf("%d",&source);
				prims(graph,v,source);
				getch();
				break;
			case 3:
				clrscr();
				kruskal(graph,v);
				getch();
				break;

		}
	}while(ch!=0);
}
void addVertex(Vertices **graph,int v1,int v2,int wt)
{
	Vertices *q,*temp;

	temp=graph[v1];

	q=(Vertices *)malloc(sizeof(Vertices));
	q->vertex=v2;
	q->weight=wt;
	q->next=NULL;

	if(graph[v1]==NULL || graph[v1]->weight > wt)
	{
		graph[v1]=q;
		graph[v1]->next=temp;
	}
	else
	{
		while(temp!=NULL)
		{
			if(temp->weight <= wt && (temp->next->weight > wt || temp->next==NULL))
			{
				q->next=temp->next;
				temp->next=q;
				return;
			}
			temp=temp->next;
		}
	}
}
//checks for repetition of edges
int found(KList *list,int start,int end)
{
	KList *temp=list;
	while(temp!=NULL)
	{
		if(temp->v1==start && temp->v2==end)
			return 1;
		temp=temp->next;
	}
	return 0;
}
void createKruskalList(KList **list,int v1,int v2,int wt)
{
	KList *q,*temp=*list;

	q=(KList *)malloc(sizeof(KList));
	q->v1=v1;
	q->v2=v2;
	q->weight=wt;
	q->next=NULL;
	if(*list==NULL || (*list)->weight > wt)
	{
		(*list)=q;
		(*list)->next=temp;
	}
	else
	{
		while(temp!=NULL)
		{
			if(temp->weight <= wt && (temp->next->weight > wt || temp->next==NULL))
			{
				q->next=temp->next;
				temp->next=q;
				return;
			}
			temp=temp->next;
		}
	}
}
void createGraph(Vertices **graph,int v,int e)
{
	int i,v1,v2,w;

	for(i=0;i<v;i++)
		graph[i]=NULL;
	for(i=0;i<e;i++)
	{
		printf("Enter the edge (v1,v2) : ");
		scanf("%d%d",&v1,&v2);
		printf("Enter the weight of edge (%d,%d) : ",v1,v2);
		scanf("%d",&w);
		//undirected graph
		addVertex(graph,v1,v2,w);
		addVertex(graph,v2,v1,w);
	}
}
void prims(Vertices **graph,int n,int source)
{
	int i,edges=n-1,min_dist,u,k=0;
	int visited[MAX],distance[MAX],from[MAX];
	Vertices *v;

	// initialization
	for(i=0;i<n;i++)
	{
		visited[i]=0;
		distance[i]=INF;
		from[i]=source;
	}

	v=graph[source];
	visited[source]=1;

	while(v!=NULL)
	{
		distance[v->vertex]=v->weight;
		v=v->next;
	}
	printf("\nPrim's Algorithm");
	printf("\n\nMinimum cost spanning tree\n\n");
	while(edges>0)
	{
		min_dist=INF;
		for(i=0;i<n;i++)
			if(!visited[i] && distance[i] < min_dist)
			{
				source=i;
				min_dist=distance[i];
			}
		u=from[source];
		printf("\n(%d,%d)=%d",u,source,distance[source]);
		k=k+distance[source];
		edges--;

		visited[source]=1;
		v=graph[source];

		while(v!=NULL)
		{
			if(!visited[v->vertex] && v->weight < distance[v->vertex])
			{
				distance[v->vertex]=v->weight;
				from[v->vertex]=source;
			}
			v=v->next;
		}
	}
	printf("\n\tCost of minimum spanning tree: %d",k);
}
void kruskal(Vertices **graph,int n)
{
	Vertices *v;
	KList *list=NULL;
	int i,belongs[MAX],cv1,cv2,min_wt=0;

	for(i=0;i<n;i++)
		belongs[i]=i;

	for(i=0;i<n;i++)
	{
		v=graph[i];
		while(v!=NULL)
		{	//found() reduces repeated elements i.e.
			//if edge (2,3) with weight 5 is added then
			//it will not allow edge (3,2) to be inserted in list
			if(!found(list,v->vertex,i))
				createKruskalList(&list,i,v->vertex,v->weight);
			v=v->next;
		}
	}
	printf("\nKruskal's Algorithm");
	printf("\n\nMinimum cost spanning tree\n\n");
	while(list!=NULL)
	{
		cv1=belongs[list->v1];
		cv2=belongs[list->v2];
		//checks whether both vertex are belongs to different sets
		if(cv1!=cv2)
		{
			printf("(%d,%d)=%d\n",list->v1,list->v2,list->weight);
			min_wt=min_wt+list->weight;
			for(i=0;i<n;i++)
				//vertex cv2 is added to set cv1
				if(belongs[i]==cv2)
					belongs[i]=cv1;
		}
		list=list->next;
	}
	printf("\n\nMinimum weight of the Spanning tree: %d",min_wt);
}