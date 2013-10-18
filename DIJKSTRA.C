#include<stdio.h>
#include<string.h>
#define INF 9999

int cost[10][10];
int paths[10][10];
void getVertices(int,char [10][10]);
void createAdjMatrix(int,int [10][10]);
void putCostTable(int,char [10][10],int [10][10]);
void shortPaths(int,char [10][10],int [10][10]);

void main()
{
	int choice,n;
	char cityNames[10][10];
	int distances[10][10];
	do
	{
		clrscr();
		printf("\n\t\t\t0.Exit");
		printf("\n\t\t\t1.Enter vertices");
		printf("\n\t\t\t2.Enter Adjacency Matrix");
		printf("\n\t\t\t3.Display cities with distances");
		printf("\n\t\t\t4.Short Paths");
		printf("\n\t\t\tYour choice : ");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
				clrscr();
				printf("\nHow much vertices : ");
				scanf("%d",&n);
				getVertices(n,cityNames);
				break;
			case 2:
				createAdjMatrix(n,distances);
				break;
			case 3:
				putCostTable(n,cityNames,distances);
				getch();
				break;
			case 4:
				shortPaths(n,cityNames,distances);
				getch();
				break;
		 }
	}while(choice!=0);
}
void getVertices(int n,char cities[10][10])
{
	int i;
	for(i=1;i<=n;i++)
		scanf("%s",&cities[i][i]);
}
void putCostTable(int n,char cities[10][10],int distances[10][10])
{
	int i,j;
	for(i=1;i<=n;i++)
		if((strlen(&cities[i][i]))<=4)
			printf(" \t\t%s",&cities[i][i]);
		else
			printf(" \t%s",&cities[i][i]);
	printf("\n");

	for(i=1;i<=n;i++)
	{
		printf(" %s ",&cities[i][i]);
		for(j=1;j<=n;j++)
		{
			printf("\t\t%d",distances[i][j]);
		}
		printf("\n");
	}

}
void createAdjMatrix(int n,int distances[10][10])
{
	int i,j;
	printf("\nEnter the adjacency matrix\n");

	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
			scanf("%d",&distances[i][j]);

}
void shortPaths(int n,char cities[10][10],int distances[10][10])
{
	int i,j,k;
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
		{
			if(distances[i][j]==0)
			{
				cost[i][j]=INF;
			}
			else
			{
				cost[i][j]=distances[i][j];
				paths[i][j]=10*i+j;
			}

		}
	for(k=1;k<=n;k++)
		for(i=1;i<=n;i++)
			for(j=1;j<=n;j++)
				if(i!=j)
				{
				 if(cost[i][j]>cost[i][k]+cost[k][j])
				 {
					cost[i][j]=cost[i][k]+cost[k][j];
					paths[i][j]=paths[i][j]*10+i;
					paths[i][j]=paths[i][j]*10+k;
					paths[i][j]=paths[i][j]*10+j;
				 }
				}
				else
					cost[i][j]=0;

	printf("\n\t\t\tCosts Table");
	printf("\n\t\t\t-----------\n");
	putCostTable(n,cities,cost);
	printf("\n\t\t\tPaths Table");
	printf("\n\t\t\t-----------\n");
	putCostTable(n,cities,paths);
}
