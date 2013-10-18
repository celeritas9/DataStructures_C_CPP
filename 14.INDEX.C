#include<stdio.h>
#include<conio.h>

typedef struct stud
{
	int rno;
	char name[20];
	int m1;
}s;
s temp;
typedef struct index
{
	int roll;
	int rec;
}r;
r ind;

FILE *fp,*fp1;

void disp();
void sortindex()  // function to sort the records
{
	r s1,s2;
	int i,j,count;

	fp=fopen("f.txt","rb");
	fp1=fopen("f1.txt","rb+");
	fseek(fp,0,2);
	count=ftell(fp)/sizeof(temp);
	for(i=0;i<count;i++)
	{
		for(j=i+1;j<count;j++)   		// just apply sorting algorithm
		{
			fseek(fp1,sizeof(r)*i,0);
			fread(&s1,sizeof(r),1,fp1);
			fseek(fp1,sizeof(r)*j,0);
			fread(&s2,sizeof(r),1,fp1);
			if(s1.roll>s2.roll) 		// if first record is greater than second,swap them
			{
				fseek(fp1,sizeof(r)*i,0);
				fwrite(&s2,sizeof(r),1,fp1);
				fseek(fp1,sizeof(r)*j,0);
				fwrite(&s1,sizeof(r),1,fp1);
			}
		}
	}
	fclose(fp);     // close the file
	fclose(fp1);
}

void create()
{
	int count;
	fp=fopen("f.txt","wb");
	fp1=fopen("f1.txt","wb");
	printf("\nEnter roll no:\t");
	scanf("%d",&temp.rno);
	printf("\nEnter the name\t");
	scanf("%s",temp.name);
	printf("\nEnter marks:\t");
	scanf("%d",&temp.m1);
	ind.roll=temp.rno;
	ind.rec=0;
	fwrite(&temp,sizeof(temp),1,fp);
	fwrite(&ind,sizeof(ind),1,fp1);
	flushall();
	fclose(fp);
}
void disp()
{
	fp=fopen("f.txt","rb");
	fp1=fopen("f1.txt","rb");
	fseek(fp,0,SEEK_SET);
	printf("\n******************Database File***********************************************\n");
	printf("\n\nRoll No:\t\tName\t\tMarks");

	while(fread(&temp,sizeof(temp),1,fp))
	{
		if(temp.rno==-1)
		{
			printf("\n\nRecord Already Deleted!!!");
			continue;
		}
		printf("\n\n%d\t\t\t%s\t\t%d",temp.rno,temp.name,temp.m1);
	}
	printf("\n\n******************Index File**************************************************\n");
	printf("\n\nRoll No:\t\tRecord No.");
	while(fread(&ind,sizeof(ind),1,fp1))
	{
		printf("\n\n%d\t\t\t%d",ind.roll,ind.rec);
	}
	fclose(fp1);
	fclose(fp);
}
int search(int x,int *i)                  //linear search algorithm
{
	int r;
	*i=0;                          //i is required only for modify function()
	fp1=fopen("f1.txt","rb");
	fseek(fp1,0,SEEK_SET);
	while(fread(&ind,sizeof(ind),1,fp1)!=0)
	{
		(*i)++;
		if(ind.roll==x)
		{
			return(ind.rec);
		}
	}
	fclose(fp1);
	return(-1);
}
void app()
{
	int count;
	fp=fopen("f.txt","ab");
	fp1=fopen("f1.txt","ab");
	printf("\nEnter roll no:\t");
	scanf("%d",&temp.rno);
	printf("\nEnter the name\t");
	scanf("%s",temp.name);
	printf("\nEnter marks:\t");
	scanf("%d",&temp.m1);
	ind.roll=temp.rno;
	fseek(fp,0,2);
	count=ftell(fp)/sizeof(temp);
	ind.rec=count;
	fwrite(&temp,sizeof(temp),1,fp);
	fwrite(&ind,sizeof(ind),1,fp1);
	flushall();
	fclose(fp);
	fclose(fp1);
}
int del()
{
	int x,flag=0,c=0,temp_int;
	printf("\n Enter the no to be deleted:\t");
	scanf("%d",&x);
	fp1=fopen("f1.txt","rb+");
	fp=fopen("f.txt","rb+");
	fseek(fp,0,SEEK_SET);        //set pointer at beginning
	fseek(fp1,0,SEEK_SET);
	while(fread(&ind,sizeof(ind),1,fp1)!=0)
	{
		c++;
		if(ind.roll==x)
		{
			flag=1;
			ind.roll=-1;
			temp_int=ind.rec;
			ind.rec=-1;
			fseek(fp1,(c-1)*sizeof(ind),SEEK_SET);
			fwrite(&ind,sizeof(ind),1,fp1);
			//goto  that locn in record file by moving fp
			fseek(fp,(temp_int)*sizeof(temp),SEEK_SET);
			temp.rno=-1;
			strcpy(temp.name,'\0');
			temp.m1=0;
			fwrite(&temp,sizeof(temp),1,fp);
		}
	}
	if(flag==0)
		printf("\n The entered Roll no not present");
	fclose(fp);
	fclose(fp1);
	return 0;
}
void modify()
{
	int n,v,i;
	printf("\n enter the roll no.to be modified: ");
	scanf("%d",&n);
	v=search(n,&i);
	if(v!=-1)
	{
		fp=fopen("f.txt","rb+");
		fseek(fp,v*sizeof(temp),SEEK_SET);
		printf("\nEnter roll no:\t");
		scanf("%d",&temp.rno);
		printf("\nEnter the name\t");
		scanf("%s",&temp.name);
		printf("\nEnter marks:\t");
		scanf("%d",&temp.m1);
		fwrite(&temp,sizeof(temp),1,fp);
		fclose(fp);
		fp1=fopen("f1.txt","rb+");
		fseek(fp1,(i-1)*sizeof(ind),SEEK_SET);
		ind.roll=temp.rno;
		ind.rec=ind.rec;
		fwrite(&ind,sizeof(ind),1,fp1);
		fclose(fp1);
	}
	else
		printf("\n NO SUCH RECORD PRESENT");
}
void main()
{
	int ch,x,r;
	clrscr();
	do
	{
		printf("\n\n\tMenu \n 1:Create \n 2:modify \n 3:Search \n 4:Append \n 5:delete \n 6:display \n 7:quit");
		printf("\nEnter your choice:\t");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:
				   create();
				   break;
			case 2:
				   modify();
				   sortindex();
				   break;
			case 3:
				   printf("\n Enter the no to be searched:\t");
				   scanf("%d",&x);
				   r=search(x,&ch);              //ch is garbage
				   if(r==-1)
						printf("\n Record not found");
				   else
				   {
						fp=fopen("f.txt","rb");
						fseek(fp,r*sizeof(temp),SEEK_SET);
						fread(&temp,sizeof(temp),1,fp);
						printf("\n\nRoll No:\t\tName\t\tMarks");
						printf("\n\n%d\t\t\t%s\t\t%d",temp.rno,temp.name,temp.m1);
						fclose(fp);
				   }
				   break;
			case 4:
					app();
					sortindex();
					break;
			case 5:
					del();
					break;
			case 6:
					sortindex();
					disp();
					break;
			case 7:
					exit(0);
		}
	}while(ch!=7);
	getch();
}