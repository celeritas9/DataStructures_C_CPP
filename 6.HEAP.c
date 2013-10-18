#include <stdio.h>
#include <conio.h>
#define MAX 20

void makeheap(int [],int);
void heapsort(int [],int);

void main()
{
	int arr[MAX],i,n ;
	clrscr();
	printf("Heap Sort\n");
	printf("---------\n");
	printf("How many elements to sort->\t");
	scanf("%d",&n);
	if(MAX<n)
	{
		printf("\nError: Array would overflow, change array size!!!");
		printf("\n\n       Program would now terminate!!!");
		getch();
		exit();
	}
	printf("\n\nEnter the elements: ");
	for(i=0;i<n;i++)
		scanf("%d",&arr[i]);

	makeheap(arr,n);         //initially heap created

	printf ("\n\nInitially heap:\n");
	for(i=0;i<n;i++)
		printf("%d  ",arr[i]);

	heapsort(arr,n);        //process of sorting starts
	printf("\n\n------------------------------------------------------------");
	printf("\n\nAfter Sorting:\n");
	for(i=0;i<n;i++)
		printf("%d  ",arr[i]);
	getch();
}

void makeheap(int x[],int n)
{
	int i,val,s,f;
	for(i=1;i<n;i++)
	{
		val=x[i];
		s=i;                    //son is (assumed) at s
		f=(s-1)/2;              //checks for father of s
		while(s>0 && x[f]<val)
		{
			x[s]=x[f];
			s=f;
			f=(s-1)/2;
		}
		x[s]=val;
	}
}

void heapsort(int x[],int n)
{
	int i,p,temp,pass=1;
	for(i=n-1;i>0;i--)
	{
		temp=x[0];
		x[0]=x[i];
		x[i]=temp;
		makeheap(x,i);
		printf("\n\nHeap after pass %d  ->  ",pass);
		pass++;
		for(p=0;p<n;p++)
			printf("%d  ",x[p]);
	}
}