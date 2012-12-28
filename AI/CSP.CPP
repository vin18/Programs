#include<stdio.h>
#include<conio.h>
#include<math.h>


void cspbacktracking(int node);
int constraint_valid(int node,int color);
int edge[10][10];
int assigned_color[10],n,ncolor,flag=0,id=0;
void read_from_file();
char palette[20][20]={"RED","GREEN","BLUE","YELLOW","WHITE","ORANGE","PURPLE"
					"CYAN","CHROME","PINK"};

FILE *fp;
void main()
{	
	printf("\n Enter the no of colors to use: ");
	scanf("%d",&ncolor);
	read_from_file();

	cspbacktracking(0);
	if(!flag)
		printf("Too few colors to color graph");
	getch();
}

void cspbacktracking(int node)
{
	int i;
	for(i=0;i<ncolor;i++)//consider all colors
	{
		if(constraint_valid(node,i)==1)
		{
			assigned_color[node]=i;
			//assign k-node color i as it is not conflicting

			if(node == (n-1))
			{//all nodes are assigned a color 
				printf("\n\n");
				printf("\nValid Coloring Sequence %d \n",++id);
				flag++;//atleast one valid answer
				for(i=0;i<n;i++)
				{
					printf("\n %d\t%s",i,palette[assigned_color[i]]);
				}
				if(flag%5==0)//max 5 to show on screen
					getch();
			}
			else
			{
				cspbacktracking(node+1);
			}
		}
	}
}

int constraint_valid(int node,int color)
{
	int j;
	
	if(node==0)
		return 1;

	for(j=0;j<node;j++)
		if(edge[node][j]>0 &&  assigned_color[j]==color)
		{
			return 0;
		}

return 1;
}
void read_from_file()
{int i,j;
	fp=fopen("csp.txt","r");
	fscanf(fp,"%d",&n); //read n

	//read edge matrix
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			fscanf(fp,"%d",&edge[i][j]);
		}
	}

	printf("\n Constraints are: \n");
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
			if(edge[i][j]>0)
				printf("  %d--%d",i,j);

		printf("\n");

	}
}

/*
OUTPUT


 Enter the no of colors to use: 3

 Constraints are:
  0--1  0--2  0--4
  1--0  1--2  1--3
  2--0  2--1  2--3  2--4
  3--1  3--2  3--4
  4--0  4--2  4--3



Valid Coloring Sequence 1

 0      RED
 1      GREEN
 2      BLUE
 3      RED
 4      GREEN


Valid Coloring Sequence 2

 0      RED
 1      BLUE
 2      GREEN
 3      RED
 4      BLUE


Valid Coloring Sequence 3

 0      GREEN
 1      RED
 2      BLUE
 3      GREEN
 4      RED


Valid Coloring Sequence 4

 0      GREEN
 1      BLUE
 2      RED
 3      GREEN
 4      BLUE


Valid Coloring Sequence 5

 0      BLUE
 1      RED
 2      GREEN
 3      BLUE
 4      RED


Valid Coloring Sequence 6

 0      BLUE
 1      GREEN
 2      RED
 3      BLUE
 4      GREEN
 Press any key to continue
*/