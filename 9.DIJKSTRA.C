#include<stdio.h>
#include<conio.h>
#define INF 9999
#define MAX 10

void dijkstra(int G[MAX][MAX],int,int,int ch);

void main()

{
	int ch;
	int G[MAX][MAX],i,j,n,u;
	do
	{
	clrscr();
	printf("\n\t1. Directed Graph");
	printf("\n\t2. Undirected Graph");
	printf("\nEnter choice: ");
	scanf("%d",&ch);
	printf("\nEnter no. of vertices: ");
	scanf("%d",&n);
	if(n==1 || n==2)
	{
		printf("\nError: Not applicable!!!");
		printf("\nProgram would terminate now!!!");
		getch();
		exit(1);
	}
	printf("\nEnter adjacency matrix:\n\n");
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
		{
			scanf("%d",&G[i][j]);
		}
	printf("\nEnter the starting node: ");
	scanf("%d",&u);
	while(u>=n)
	{
		printf("\nEnter the correct starting node!!!\n\n");
		scanf("%d",&u);
	}
	dijkstra(G,n,u,ch);
	getch();
	flushall();
	printf("\nDo you want to continue? ");
	}while(getche()=='y' || getche()=='Y');
}

void dijkstra(int G[MAX][MAX],int n,int startnode,int ch)
{
	int cost[MAX][MAX],distance[MAX],pred[MAX];
	int visited[MAX],count,mindistance,nextnode;
	int i,j,k,desti;
	//pred[] stores the predecessor of each node
	//count gives the number of nodes seen so far

	//create the cost matrix
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			if(G[i][j]==0)
				cost[i][j]=INF;
			else
				cost[i][j]=G[i][j];
		}
	}
	//initialize
	for(i=0;i<n;i++)
	{
		distance[i]=cost[startnode][i];
		pred[i]=startnode;
		visited[i]=0;
	}
	distance[startnode]=0;
	visited[startnode]=1;
	count=1;
	while(count<n-1)
	{
		mindistance=INF ;
		// nextnode is the node at minimum distance
		// checks for mindistance in distance array
		for(i=0;i<n;i++)
		{
			if((distance[i] < mindistance) && !visited[i])
			{
				mindistance=distance[i];
				nextnode=i;
			}
		}
		//check if a better path exist through nextnode
		visited[nextnode]=1;
		for(i=0;i<n;i++)
		{
			if(!visited[i])
			{
				if(mindistance+cost[nextnode][i] < distance[i])
				{
					distance[i]=mindistance+cost[nextnode][i];
					pred[i]=nextnode;
				}
			}
		}
		count++;
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
				if(k==n-1)                            //helps for printing
				{
					if(i==j && ch==2)
						cost[i][j]=INF;
					printf("\t%d",cost[i][j]);
				}
			}
			if(k==n-1)                                //helps for printing
				printf("\n");
		}
	}

	printf("\ndesti: ");
	scanf("%d",&desti);
	//print the path and distance of each node
	for(i=0;i<n;i++)
	{
		if(i!=startnode && i==destination)
		{
			printf("\n");
			printf("\n Distance(%d,%d) = %d\n ",startnode,i,distance[i]);
			printf("\n Path = %d",i);
			j=i;
			do
			{
				j=pred[j];
				printf("<-%d",j);
			}while(j!=startnode);
		}
		printf("\n");
	}
}