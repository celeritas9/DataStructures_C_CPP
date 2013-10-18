#include<stdio.h>
#include<conio.h>
#define INF 9999
#define MAX 10

void create_adj_mat();
void dijkstra(int [MAX][MAX],int);
void show_smallest(int [MAX][MAX]);

int G[MAX][MAX];
int cost[MAX][MAX];
int n;

void main()
{
	int ch;
	do
	{
		clrscr();
		printf("\t\tDijkstra Shortest Path Algorithm\n");
		printf("\t\t--------------------------------");
		printf("\n\t\t0. Exit");
		printf("\n\t\t1. Create Adjacency Matrix");
		printf("\n\t\t2. Lowest cost adjacency Matrix");
		printf("\n\t\t3. Find smallest path between (u,v)\n");
		printf("\n\tYour Choice-> ");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:
					clrscr();
					create_adj_mat();
					break;
			case 2:
					clrscr();
					dijkstra(G,n);
					getch();
					break;
			case 3:
					clrscr();
					show_smallest(cost);
					getch();
					break;
		}
	}while(ch!=0);
}
void create_adj_mat()
{
	int i,j;
	printf("\nEnter the number of vertices: ");
	scanf("%d",&n);
	printf("\n\tEnter the adjacency matrix(%d*%d) for the graph",n,n);
	printf("\n\t-----------------------------------------------\n\n");
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			scanf("%d",&G[i][j]);
}
void dijkstra(int G[MAX][MAX],int n)
{
	int i,j,k;

	//all the operations are performed on cost
	printf("\n\n\t\tAdjacency Matrix of cost of edges\n");
	printf("\t\t---------------------------------\n\n");
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
	printf("\n\n\t\tAdjacency Matrix of lowest cost between vertices\n");
	printf("\t\t------------------------------------------------\n\n");
	for(k=0;k<n;k++)
	{
		for(i=0;i<n;i++)
		{
			for(j=0;j<n;j++)
			{
				if(cost[i][j] > cost[i][k]+cost[k][j])
					cost[i][j]=cost[i][k]+cost[k][j];
				if(k==n-1)
					printf("\t%d",cost[i][j]);
			}
			if(k==n-1)
				printf("\n");
		}
	}
}
void show_smallest(int cost[MAX][MAX])
{
	int u,v;
	printf("\n\nEnter the start and end vertex (u v): ");
	scanf("%d%d",&u,&v);

}