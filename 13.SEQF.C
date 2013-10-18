#include<stdio.h>
#include<conio.h>
typedef struct student
{
	int rn;
	char name[10];
	float per;
}st;
st student;
int total;          		//stores total no. of records

void insert(FILE *);
void display(FILE *);
void search(FILE *);
void del(FILE *);
void modify(FILE *);
void sort(FILE *);

void main()
{
	FILE *fp;
	int ch,x,y;
	do
	{
		clrscr();
		fp=fopen("STUDENT.txt","rb");
		printf("\t\tSequential File Operations\n");
		printf("\t\t--------------------------\n");
		x=wherex();
		y=wherey();
		gotoxy(1,25);
		fseek(fp,0,2);
		total=ftell(fp)/sizeof(st);
		printf("\nTotal records: %1d",total);
		gotoxy(x,y);
		fclose(fp);
		printf("\n\t\t0. Exit");
		printf("\n\t\t1. Insert record");
		printf("\n\t\t2. Display records");
		printf("\n\t\t3. Search");
		printf("\n\t\t4. Delete record");
		printf("\n\t\t5. Modify record\n");
		printf("\n\tYour Choice-> ");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:
					fp=fopen("STUDENT.txt","ab+");
					insert(fp);
					fclose(fp);
					break;
			case 2:
					clrscr();
					fp=fopen("STUDENT.txt","rb+");
					if(fp==NULL)
					{
						printf("\nFile can't be opened!!!");
						getch();
						break;
					}
					sort(fp);
					display(fp);
					getch();
					fclose(fp);
					break;
			case 3:
					fp=fopen("STUDENT.txt","rb");
					if(fp==NULL)
					{
						printf("\nFile can't be opened!!!");
						getch();
						break;
					}
					search(fp);
					getch();
					fclose(fp);
					break;
			case 4:
					del(fp);
					getch();
					break;
			case 5:
					modify(fp);
					getch();
					break;
		}
	}while(ch!=0);
}
void insert(FILE *fp)
{
	int rollno;
	printf("\nEnter the roll no: ");
	scanf("%d",&rollno);
	//move fp at start of file as this is append mode and fp is at EOF
	rewind(fp);
	while(fread(&student,sizeof(st),1,fp))
	{
		if(student.rn==rollno)
		{
			printf("\nThis roll no. already exist!!!");
			getch();
			return;
		}
	}
	student.rn=rollno;
	printf("\nEnter name: ");
	scanf("%s",&student.name);
	printf("\nEnter percentage: ");
	scanf("%f",&student.per);
	fwrite(&student,sizeof(st),1,fp);  //same call as that of the fread
}
void display(FILE *fp)
{
	if(total==0)
	{
		printf("\nDatabase Empty!!!");
		return;
	}
	printf("--------------------------------------");
	printf("\n\n\tROLL NO\t  NAME\t    PERCENTAGE\n");
	printf("--------------------------------------\n");
	//set fp at start of file rewind can also be used instead of fseek
	fseek(fp,0,SEEK_SET);
	rewind(fp);
	while(fread(&student,sizeof(st),1,fp))
	{
		printf("\n\t%d\t  %s\t%.2f",student.rn,student.name,student.per);
	}
	printf("\n--------------------------------------");
}
void search(FILE *fp)
{
	int rno;
	if(total==0)
	{
		printf("\nDatabase Empty!!!");
		return;
	}
	printf("\nEnter the roll no search: ");
	scanf("%d",&rno);
	while(fread(&student,sizeof(st),1,fp))
	{
		if(student.rn==rno)
		{
			printf("\nRoll No. found!!\n\n");
			printf("--------------------------------------");
			printf("\n\n\tROLL NO\t  NAME\t    PERCENTAGE\n");
			printf("--------------------------------------\n");
			printf("\n\t%d\t  %s\t%.2f",student.rn,student.name,student.per);
			printf("\n--------------------------------------");
			return;
		}
	}
	printf("\nRoll No. doesn't exist!!!");
}
void del(FILE *fp)
{
	int rno,flag=0;
	FILE *temp;
	if(total==0)
	{
		printf("\nDatabase Empty!!!");
		return;
	}
	temp=fopen("TEMP.txt","wb");
	fp=fopen("STUDENT.txt","rb");
	if(fp==NULL)
	{
		printf("\nCreate the records file first!!!");
		return;
	}
	printf("\nEnter the roll no. to delete: ");
	scanf("%d",&rno);
	while(fread(&student,sizeof(st),1,fp))
	{
		if(student.rn==rno)
		{
			printf("\nRoll No. %d successfully deleted!!!",rno);
			flag=1;
		}
		else
		{
			fwrite(&student,sizeof(student),1,temp);
		}
	}
	fclose(fp);
	fclose(temp);
	temp=fopen("TEMP.txt","rb");
	fp=fopen("STUDENT.txt","wb");
	while(fread(&student,sizeof(st),1,temp))
	{
		fwrite(&student,sizeof(student),1,fp);
	}
	fclose(fp);
	fclose(temp);
	if(flag==0)
		printf("\nRoll No. doesn't exist!!!");
}
void modify(FILE *fp)
{
	int rno,rno1,flag=0,r=0;
	if(total==0)
	{
		printf("\nDatabase Empty!!!");
		return;
	}
	printf("\nEnter the roll no. to modify: ");
	scanf("%d",&rno);
	fp=fopen("STUDENT.txt","rb+");
	while(fread(&student,sizeof(st),1,fp))
	{
		r++;
		if(rno==student.rn)
		{
			printf("\nEnter New Roll No.: ");
			scanf("%d",&rno1);
			rewind(fp);
			while(fread(&student,sizeof(st),1,fp))
			{
				if(student.rn==rno1)
				{
					printf("\nThis roll no. already exist!!!");
					fclose(fp);
					return;
				}
			}
			student.rn=rno1;
			printf("\nEnter New name: ");
			scanf("%s",&student.name);
			printf("\nEnter New percentage: ");
			scanf("%f",&student.per);
			//first go to starting of file then move to (r-1)th record
			fseek(fp,(r-1)*sizeof(st),SEEK_SET);
			fwrite(&student,sizeof(student),1,fp);
			printf("\nRoll No. %d successfully modified!!!",rno);
			flag=1;
		}
	}
	fclose(fp);
	if(flag==0)
		printf("\nRoll No. doesn't exist!!!");
}
void sort(FILE *fp)  // function to sort the records
{

	int i,j,count;
	st student1,student2;

	fseek(fp,0,2);
	count=ftell(fp)/sizeof(st);
	for(i=0;i<count;i++)
	{
		for(j=i+1;j<count;j++)   		// just apply sorting algorithm
		{
			fseek(fp,sizeof(st)*i,0);
			fread(&student1,sizeof(st),1,fp);
			fseek(fp,sizeof(st)*j,0);
			fread(&student2,sizeof(st),1,fp);
			if(student1.rn>student2.rn) 		// if first record is greater than second,swap them
			{
				fseek(fp,sizeof(st)*i,0);
				fwrite(&student2,sizeof(st),1,fp);
				fseek(fp,sizeof(st)*j,0);
				fwrite(&student1,sizeof(st),1,fp);
			}
		}
	}
}
