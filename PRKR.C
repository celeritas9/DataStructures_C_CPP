//using adjacency list
#include<stdio.h>
#include<conio.h>
#define MAX 10
#define INF 9999

typedef struct Vertices
{
	int v1,v2;
}Vertices;

void createAdjMat();
int Prims();

int G[MAX][MAX],cost[MAX][MAX],spanning[MAX][MAX];
int k;
Vertices Vert[MAX];
int n;

void main()
{
	int ch,i,j,total_cost;
	do
	{
		clrscr();
		printf("\n\n\t\tMENU");
		printf("\n\t\t----");
		printf("\n\t0. Exit");
		printf("\n\t1. Create Graph");
		printf("\n\t2. Display Adjacency Matrix");
		printf("\n\t3. Prim's Algorithm");
		printf("\n\t4. Kruskal's Algorithm");
		printf("\n\nChoice-> ");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:
					clrscr();
					printf("\n\t\tCreate Graph using Adjacency Matrix");
					printf("\n\t\t-----------------------------------\n\n");
					printf("\nEnter the number of vertices: ");
					scanf("%d",&n);
					printf("\n\tEnter the adjacency matrix(%d*%d) for the graph",n,n);
					printf("\n\t-----------------------------------------------\n");
					createAdjMat();
					break;
			case 2:
					clrscr();
					printf("\n\n\t\tAdjacency Matrix of cost of edges\n");
					printf("\t\t---------------------------------\n\n");
					printf("\t\tNote: 9999 indicates Infinity\n");
					printf("\t\t----\n\n");
					for(i=0;i<n;i++)
					{
						for(j=0;j<n;j++)
						{
							if(G[i][j]==0)
								cost[i][j]=INF;
							else
								cost[i][j]=G[i][j];
								printf("\t%d",cost[i][j]);
						}
						printf("\n");
					}
					getch();
					break;
			case 3:
					clrscr();
					printf("\n\tPrims Algorithm");
					printf("\n\t---------------\n\n");
					total_cost=Prims();
					printf("\n\nTotal Cost of the Spanning tree using Prim's Algorithm is: %d\n\n",total_cost);
					printf("\n\n\t\tMinimum Spanning tree Matrix\n");
					printf("\t\t----------------------------\n\n");
					for(i=0;i<n;i++)
					{
						for(j=0;j<n;j++)
						{
							printf("\t%d",spanning[i][j]);
						}
						printf("\n");
					}
					printf("\n\nEdges in minimum spanning are: \n\n");
					for(i=0;i<k;i++)
					{
						printf("\n%d->%d",Vert[i].v1,Vert[i].v2);
					}
					getch();
					break;
			case 4:
					clrscr();
					printf("\n\tKruskal's Algorithm");
					printf("\n\t-------------------\n\n");
					getch();
					break;
		}
	}while(ch!=0);
}
void createAdjMat()
{
	int i,j;
	int flag[MAX][MAX];

	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			flag[i][j]=0;

	printf("\nNote: If no direct path insert 0\n\n\n");
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			if(i!=j && (flag[i][j]==0 || flag[j][i]==0))
			{
				printf("Enter the distance from %d to %d : ",i,j);
				scanf("%d",&G[i][j]);
				G[j][i]=G[i][j];
				flag[i][j]=1;
				flag[j][i]=1;
			}
			if(i==j)
			{
				G[i][j]=0;
			}
		}
	}
}
int Prims()
{
	int visited[MAX],distance[MAX],from[MAX];
	int min_cost,min_d,u,v;
	int i,j,no_of_edges;

	visited[0]=1;
	distance[0]=0;
	from[0]=0;
	for(i=1;i<n;i++)
	{
		visited[i]=0;
		distance[i]=cost[0][i];
		from[i]=0;
	}
	min_cost=0;
	no_of_edges=n-1;
	k=0;
	while(no_of_edges>0)
	{
		//find the vertex at minimum distance from the tree
		min_d=INF;
		for(i=1;i<n;i++)
			if(visited[i]==0 && distance[i]<min_d)
			{
				v=i;
				min_d=distance[i];
			}
		u=from[v];
		//insert the edge in the tree
		spanning[u][v]=distance[v];
		spanning[v][u]=distance[v];
		Vert[k].v1=u;
		Vert[k].v2=v;
		no_of_edges--;
		visited[v]=1;
		//update the distance[] array
		//v is the recently added vertex
		for(i=1;i<n;i++)
			if(visited[i]==0 && cost[i][v]<distance[i])
			{
				distance[i]=cost[i][v];
				from[i]=v;
			}
		min_cost=min_cost+cost[u][v];
		k++;
	}
	return(min_cost);
}