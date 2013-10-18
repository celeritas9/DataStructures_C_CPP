#include<stdio.h>
#include<conio.h>

typedef struct node        // structure for the linked list
{
  int data;
  struct node *next;
}node;

node *getnode(void)    // getnode function to create a new node
 {
  node *p;
  p=(node*)malloc(sizeof(node));   // dynamically allocate memory space
  p->next=NULL;
  scanf("%d",&p->data);     // read the data of the newly created node
  return p;
 }

node* create(node *root) // function to create the list
 {
  node *p=root;
  if(root==NULL)      // if root is null make new node for root
	root=getnode();
  else
  {
	p=root;
	while(p->next!=NULL)
		p=p->next;
	p->next=getnode();   // else go to last location & make new node there
  }
  return root;          // return the value of the root
 }

void display(node *root)  // display function for the list
 {
  node *p;
  for(p=root;p!=NULL;p=p->next)
	printf("  %d",p->data);
 }

node *divide(node *p)    // divide function to divide the list
{
  node *r,*q=p;
  r=p->next->next;
  //here r moves with double speed compared to q which gives half of the
  //list
  while(r!=NULL)         // loop until r not becomes null
  {
	r=r->next;
	q=q->next;
	if(r!=NULL)
	r=r->next;
  }
  r=q->next;
  q->next=NULL;
  return r;
}

node *merge(node *p,node *q)   // function to merge two lists
{
  node *head,*r;
  if(p->data<q->data)     // compare the data of the two lists
  {
	head=p;         // if first smaller then make it head
	p=p->next;
  }
  else
  {
	head=q;    // if second smaller then make it head
	q=q->next;
  }
  r=head;                     //head has been made permanent
  while(p!=NULL && q!=NULL)   // merge two lists until both lists are not empty
  {
	if(p->data<q->data)
	{
	  r->next=p;              //add immediate greater value
	  r=r->next;
	  p=p->next;
	}
	else
	{
	  r->next=q;              //add immediate greater value
	  r=r->next;
	  q=q->next;
	}
  }
  if(p!=NULL)                 //i.e q is NULL so add only remaining p
	r->next=p;
  else
	r->next=q;
  printf("\n\nThe list after merging :- ");
  display(head);          // the pass to display the current merged list
  return head;
}

node *sort(node *p)    // function sort to perform merge sort
{
  node *q,*head=p;     //head points to first list i.e p
  printf("\n\nThe divided list is :- ");
  display(head);      // display current divided list
  if(p!=NULL && p->next!=NULL)
  {
	q=divide(p);      // divide function returns address of second list
	p=sort(p);        // call recursive sort function for first divided list
	q=sort(q);        // call recursive sort function for secnd divided list
	head=merge(p,q);  // call merge function to merge two sorted list
  }
  return head;     // return the starting address of the merged list
}

int main(void)         // main function
{
  node *root=NULL;     // create root node of the list & make it NULL
  int ch;
  do
  {
	clrscr();
	printf("\n\nWhich operation do you want to perform...");
	printf("\n\n1.Enter the elements");
	printf("\n2.Sort using the merge sort.");
	printf("\n3.Exit");
	printf("\n\nEnter your choice :- ");
	scanf("%d",&ch);     // read the choice from the user
	switch(ch)   // go to appropriate case as per the user's choice
	{
	  case 1:
		 do
		 {
		   printf("\n\nEnter the elements :- ");
		   root=create(root);      		 // create the nodes of list
		   printf("\n\nPress y to enter the elements :- ");
		 }while(getche()=='y');
		 printf("\n\n\nThe entered elements are :- ");
		 display(root);
		 break;
	  case 2:
		 root=sort(root);    			 // call the sort function
		 printf("\n\nThe sorted elements are :- ");
		 display(root);
		 break;
	}
	getch();
  }while(ch!=3);
  return 0;
}