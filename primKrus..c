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

void createGraph(Vertices **,int,int *);
void prims(Vertices **,Vertices **,int,int);

int search(KList *,int,int);
void createKruskalList(KList **,int,int,int);
void kruskal(Vertices **,Vertices **,int);


void addVertex(Vertices **,int,int,int);
void display(Vertices **,int);
void main()
{
	int ch,source;
	Vertices *graph[MAX],*spanning[MAX];
	int v,e;
	do
	{
		printf("\n\t\t\t0. Exit");
		printf("\n\t\t\t1. Read graph");
		printf("\n\t\t\t2. Prims");
		printf("\n\t\t\t3. Kruskal");
		printf("\n\t\t\tYour choice : ");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:
				printf("\nEnter the number of vertices : ");
				scanf("%d",&v);
				createGraph(graph,v,&e);
				break;
			case 2:
				printf("\nEnter the source vertex : ");
				scanf("%d",&source);
				prims(graph,spanning,v,source);
				break;
			case 3:
				kruskal(graph,spanning,v);
				break;
			case 4:
				break;

		}
	}while(ch!=0);
}
void display(Vertices **graph,int v)
{
	int i;
	Vertices *v1;
	printf("\n");
	for(i=0;i<v;i++)
	{
		v1=graph[i];
		while(v1!=NULL)
		{
			printf(" (%d,%d)=%d",i,v1->vertex,v1->weight);
			v1=v1->next;
		}
		printf("\n");
	}

}
void addVertex(Vertices **graph,int v1,int v2,int wt)
{
	Vertices *p,*q,*temp=graph[v1];

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
int search(KList *list,int start,int end)
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
void createGraph(Vertices **graph,int v,int *edge)
{
	int i,e,v1,v2,w;
	for(i=0;i<v;i++)
		graph[i]=NULL;

	for(i=0;i<v;i++)
	{
		printf("\nEnter the number of edges :");
		scanf("%d",&e);
		*edge=e;
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
		break;
	}
}
void prims(Vertices **graph,Vertices **spanning,int n,int source)
{
	int i,edges=n-1,min_dist,u;
	int visited[MAX],distance[MAX],from[MAX];
	Vertices *v,*v1;

	for(i=0;i<n;i++)
	{
		visited[i]=0;
		distance[i]=INF;
		from[i]=source;
		spanning[i]=NULL;
	}

	v=graph[source];
	visited[source]=1;

	while(v!=NULL)
	{
		distance[v->vertex]=v->weight;
		v=v->next;
	}

	while(edges>0)
	{
		min_dist=INF;
		for(i=0;i<n;i++)
			if(visited[i]==0 && distance[i] < min_dist)
			{
				source=i;
				min_dist=distance[i];
			}
		u=from[source];
		addVertex(spanning,u,source,distance[source]);
		addVertex(spanning,source,u,distance[source]);
		edges--;

		visited[source]=1;
		v=graph[source];

		while(v!=NULL)
		{
			if(visited[v->vertex]==0 && v->weight < distance[v->vertex])
			{
				distance[v->vertex]=v->weight;
				from[v->vertex]=source;
			}
			v=v->next;
		}
	}
	display(spanning,n);
}
void kruskal(Vertices **graph,Vertices **spanning,int n)
{
	Vertices *v;
	KList *list=NULL;
	int i,belongs[MAX],cv1,cv2;

	for(i=0;i<n;i++)
		belongs[i]=i;

	for(i=0;i<n;i++)
	{
		v=graph[i];
		while(v!=NULL)
		{	//search is reduces repeated elements i.e.
			// if edge (2,3) with weight 5 is added then
			//it will not allow edge (3,2) to be inserted in list
			if(search(list,v->vertex,i)==0)
				createKruskalList(&list,i,v->vertex,v->weight);
			v=v->next;
		}
	}
	printf("\n");
	while(list!=NULL)
	{
		cv1=belongs[list->v1];
		cv2=belongs[list->v2];
		//checks whether both vertex are belongs to different sets
		if(cv1!=cv2)
		{
			printf("(%d,%d)=%d ",list->v1,list->v2,list->weight);
			addVertex(spanning,list->v1,list->v2,list->weight);
			addVertex(spanning,list->v2,list->v1,list->weight);
			for(i=0;i<n;i++)
				//vertex cv2 is added to set cv1
				if(belongs[i]==cv2)
					belongs[i]=cv1;
		}
		list=list->next;
	}
}