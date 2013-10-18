#include<stdio.h>
#include<string.h>
#define INF 9999

int cost[10][10];
int paths[10][10];
void getCityNames(int,char [10][10]);
void getCityDistances(int,char [10][10],int [10][10]);
void putCityNames(int,char [10][10],int [10][10]);
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
		printf("\n\t\t\t1.Enter city names");
		printf("\n\t\t\t2.Enter the distances");
		printf("\n\t\t\t3.Display cities with distances");
		printf("\n\t\t\t4.Short Paths");
		printf("\n\t\t\tYour choice : ");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
				clrscr();
				printf("\nHow much cities : ");
				scanf("%d",&n);
				getCityNames(n,cityNames);
				break;
			case 2:
				clrscr();
				getCityDistances(n,cityNames,distances);
				getch();
				break;
			case 3:
				clrscr();
				putCityNames(n,cityNames,distances);
				getch();
				break;
			case 4:
				clrscr();
				shortPaths(n,cityNames,distances);
				getch();
				break;
		}
	}while(choice!=0);
}
void getCityNames(int n,char cities[10][10])
{
	int i;
	for(i=1;i<=n;i++)
		scanf("%s",&cities[i][i]);
}
void putCityNames(int n,char cities[10][10],int distances[10][10])
{
	int i,j;
	for(i=1;i<=n;i++)
		if((strlen(&cities[i][i]))<=4)
			printf("\t%s",&cities[i][i]);
		else
			printf("\t%s",&cities[i][i]);
	printf("\n");

	for(i=1;i<=n;i++)
	{
		printf(" %s ",&cities[i][i]);
		for(j=1;j<=n;j++)
		{
			printf("\t%d",distances[i][j]);
		}
		printf("\n");
	}

}
void getCityDistances(int n,char cities[10][10],int distances[10][10])
{
	int i,j;
	int flag[10][10];

	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
			flag[i][j]=0;

	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
		{
			if(i!=j && (flag[i][j]==0 || flag[j][i]==0))
			{
				printf("Enter the distance from %s to %s : ",&cities[i][i],&cities[j][j]);
				scanf("%d",&distances[i][j]);
				distances[j][i]=distances[i][j];
				flag[i][j]=1;
				flag[j][i]=1;
			}
			if(i==j)
			{
				distances[i][j]=0;
			}
		}
	}
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
						paths[i][j]=100*i+10*k+j;
					}
				}
				else
					cost[i][j]=0;

	printf("\n\t\t\tCosts Table");
	printf("\n\t\t\t-----------\n");
	putCityNames(n,cities,cost);
	printf("\n\t\t\tPaths Table");
	printf("\n\t\t\t-----------\n");
	putCityNames(n,cities,paths);


}
