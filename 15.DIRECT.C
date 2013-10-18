#include<stdio.h>
#include<conio.h>

typedef struct student
{
	int emp_no,sal,iChain;
	char name[20];

}emp;

void display(FILE *);

void search(FILE *fp,emp s)
{
	emp s1;
	int iVal,size,size1,iChain;
	iVal=s.emp_no%10;
	size=sizeof(s);
	iVal=iVal*sizeof(s);
	fp=fopen("DATA.txt","r+");
	fseek(fp,iVal,0);
	do
	{
		fread(&s1,size,1,fp);
		if(s.emp_no==s1.emp_no)
		{
			printf("\n\nRECORD EXISTS !!!");
			printf("\n\n%d\t%s\t%d",s1.emp_no,s1.name,s1.sal);
			break;
		}
		else if(s1.iChain!=-1)
		{
			size1=s1.iChain*size;
			fseek(fp,size1,0);
		}
		else
		{
			printf("\n\nRECORD DOES NOT EXISTS !!!");
			break;
		}
	}while(s.emp_no!=s1.emp_no);
	fclose(fp);
}

void add(emp s,FILE *fp)
{
	emp s1,s2;
	int iVal,size,iCount=0,size1,iVal1,iVal2;
	iVal2=s.emp_no%10;
	iCount=iVal2;
	size=sizeof(s);
	iVal=iVal2*sizeof(s);
	fp=fopen("DATA.txt","r+");
	fseek(fp,iVal,0);
	fread(&s1,size,1,fp);
	fseek(fp,iVal,0);
	do
	{
		if(s1.emp_no==0)
		{
			fwrite(&s,size,1,fp);
			break;
		}
		else if(s1.iChain==-1)
		{
			s2.emp_no=s1.emp_no;
			strcpy(s2.name,s1.name);
			s2.sal=s1.sal;
			fseek(fp,iVal,0);
			while(s1.emp_no!=0)
			{
				iCount++;
				fread(&s1,size,1,fp);
			}
			fseek(fp,-size,1);
			fwrite(&s,size,1,fp);
			s1.emp_no=s2.emp_no;
			strcpy(s1.name,s2.name);
			s1.sal=s2.sal;
			iCount--;
								s1.iChain=iCount;
			fseek(fp,iVal,0);
			fwrite(&s1,size,1,fp);
			break;
		}
		else
		{
			while(s1.iChain!=-1)
			{
				iCount=s1.iChain;
				fseek(fp,(s1.iChain*size),0);
				iVal=s1.iChain*size;
				iCount++;
				fread(&s1,size,1,fp);
			}
			iCount--;
		}
	}while(1);
	fclose(fp);
}

void display(FILE *fp)
{
	emp s;
	int size,iCount=0;
	fp=fopen("DATA.txt","r");
	size=sizeof(s);
	while(fread(&s,size,1,fp)==1&&iCount<10)
	{
			printf("\n\n%d\t%s\t%d\t%d",s.emp_no,s.name,s.sal,s.iChain);
			iCount++;
	}
	fclose(fp);
}

void main()
{
	FILE *fp;
	emp s;
	int iLoop1=0,size,iCh,iMax,iFlag=0;
	clrscr();
	fp=fopen("DATA.txt","w+");
	if(fp==NULL)
	printf("error");
	size=sizeof(s);
	for(iLoop1=0;iLoop1<10;iLoop1++)
	{
		s.emp_no=0;
		s.iChain=-1;
		strcpy(s.name,"NULL");
		fwrite(&s,size,1,fp);
	}
	fclose(fp);
	do
	{
		printf("\n\n1.ADD\n\n2:SEARCH\n\n3:DISPLAY\n\n4:EXIT");
		printf("\n\nENTER THE CHOICE :");
		scanf("%d",&iCh);
		switch(iCh)
		{
			case 1:
					printf("\n\nHOW MANY DATA'S :");
					scanf("%d",&iMax);
					for(iLoop1=0;iLoop1<iMax;iLoop1++)
					{
							printf("\n\nENTER THE EMPLYEE NO NAME & SALARY :");
							scanf("%d%s%d",&s.emp_no,s.name,&s.sal);
							s.iChain=-1;
							add(s,fp);
					}
					break;
			case 2:
					printf("\n\nENTER THE EMPLOYEE NO:");
					scanf("%d",&s.emp_no);
					search(fp,s);
					break;
			case 3:
					display(fp);
					break;
			case 4: exit(0);
			default:
					iFlag=1;
					break;
		}
	}while(iFlag!=1);
	getch();
}
/*-----------------------------------------*/
/*OUTPUT:

1.ADD

2:SEARCH

3:DISPLAY

4:EXIT

ENTER THE CHOICE :3
ENTER THE EMPLYEE NO NAME & SALARY:51
shreyas
27000


ENTER THE EMPLYEE NO NAME & SALARY :39
vineet
27000


1.ADD

2:SEARCH

3:DISPLAY

4:EXIT

ENTER THE CHOICE :3


0       NULL    0       -1

51      shreyas 27000   -1

0       NULL    0       -1

0       NULL    0       -1

0       NULL    0       -1

0       NULL    0       -1

0       NULL    0       -1

0       NULL    0       -1

0       NULL    0       -1

39      vineet  27000   -1

1.ADD

2:SEARCH

3:DISPLAY

4:EXIT

ENTER THE CHOICE :4

*/