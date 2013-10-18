#include<stdio.h>
#include<conio.h>
void quicksort(int [],int,int);
int pivot(int [],int,int);
int pass=1;
void main()
{
	int x[20],n,i;
	clrscr();
	printf("\nEnter no of elements-");
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		printf("\nEnter element-");
		scanf("%d",&x[i]);
	}
	printf("\nArray before sorting\n");
	for(i=0;i<n;i++)
	{
		printf("%d  ",x[i]);
	}
	quicksort(x,0,n-1);
	printf("\nArray after sorting\n");
	for(i=0;i<n;i++)
	{
		printf("%d  ",x[i]);
	}
	getch();
}
void quicksort(int x[30],int lb,int ub)
{
	int i;
	if(ub>lb)
	{
		i=pivot(x,lb,ub);
		quicksort(x,lb,i-1);
		quicksort(x,i+1,ub);
	}
}
int pivot(int x[30],int lb,int ub)
{
	int i,down,up,temp,c;
	i=x[lb];
	down=lb+1;
	up=ub;
	while(up>=down)
	{
		while(x[down]<=i)
			down++;
		while(x[up]>i)
			up--;

		if(up>down)
		{
			temp=x[down];
			x[down]=x[up];
			x[up]=temp;
		}
	}
	temp=x[lb];
	x[lb]=x[up];
	x[up]=temp;
	printf("\nAfter pass %d\n",pass);

	for(c=0;c<10;c++)
	{
		printf("%d ",x[c]);
	}
	printf("\n");
	pass++;
	return up;
}
