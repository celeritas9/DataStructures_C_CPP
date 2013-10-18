#include<stdio.h>
#include<conio.h>
#define INF 9999
#define MAX 10

void createAdjMat();
void dijkstra(int [MAX][MAX],int,int);
void showSmallest(int [MAX][MAX]);

int G[MAX][MAX];
int cost[MAX][MAX];
int n;

void main()
{
	int ch,option;
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
					printf("\n\t\t1. Directed Graph");
					printf("\n\t\t2. Undirected Graph");
					printf("\n\tYour Choice-> ");
					scanf("%d",&option);
					createAdjMat();
					break;
			case 2:
					clrscr();
					if(option==1)
					{
						printf("\n\tDirected Graph");
						printf("\n\t--------------\n");
					}
					if(option==2)
					{
						printf("\n\tUndirected Graph");
						printf("\n\t----------------\n");
					}
					dijkstra(G,n,option);
					getch();
					break;
			case 3:
					clrscr();
					showSmallest(cost);
					getch();
					break;
		}
	}while(ch!=0);
}
void createAdjMat()
{
	int i,j;
	printf("\nEnter the number of vertices: ");
	scanf("%d",&n);
	printf("\n\tEnter the adjacency matrix(%d*%d) for the graph",n,n);
	printf("\n\t-----------------------------------------------\n\n");
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
			scanf("%d",&G[i][j]);
}
void dijkstra(int G[MAX][MAX],int n,int option)
{
	int i,j,k;
	//all the operations are performed on cost
	printf("\n\n\t\tAdjacency Matrix of cost of edges\n");
	printf("\t\t---------------------------------\n\n");
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
		{
			if(G[i][j]==0)
				cost[i][j]=INF;
			else
				cost[i][j]=G[i][j];
			if(option==2 && i==j)
			{
				cost[i][j]=INF;
			}
			printf("\t%d",cost[i][j]);
		}
		printf("\n");
	}
	printf("\n\n\t\tAdjacency Matrix of lowest cost between vertices\n");
	printf("\t\t------------------------------------------------\n\n");
	for(k=1;k<=n;k++)
	{
		for(i=1;i<=n;i++)
		{
			for(j=1;j<=n;j++)
			{
				if(cost[i][j] > cost[i][k]+cost[k][j])
				{
					cost[i][j]=cost[i][k]+cost[k][j];
				}
				if(k==n)                            //helps for printing
				{
					if(option==2 && i==j)
						cost[i][j]=INF;
					printf("\t%d",cost[i][j]);
				}
			}
			if(k==n)                                //helps for printing
				printf("\n");
		}
	}
}
void showSmallest(int cost[MAX][MAX])
{
	int u;
START:
	printf("\n\nEnter the start vertex (u v): ");
	scanf("%d",&u);
	if(u>=n)
	{
		printf("\nEnter the correct start vertex!!!");
		goto START;
	}

}