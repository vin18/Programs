#include<stdio.h>
#include<conio.h>
#include<math.h>

void nqueen(int k,int n);
int place(int k,int m);

int x[8];
void main()
{
	int i,j,k,no;
	int a[8][8];
	
	printf("\n Enter the no of queens: ");
	scanf("%d",&no);
	nqueen(1,no);
	getch();
}

void nqueen(int k,int n)
{
	int i;
	for(i=1;i<=n;i++)
	{
		if(place(k,i)==1)
		{
			x[k]=i;
			if(k==n)
			{
				printf("\n\n");
				printf("\nQUEEN\tCOLUMN\n");
				for(i=1;i<=n;i++)
				{
					printf("\n %d\t%d",i,x[i]);
				}
			}
			else
			{
				nqueen(k+1,n);
			}
		}
	}
}

int place(int k,int m)
{
	int j;
	for(j=0;j<=k-1;j++)
		if(x[j]==m || abs(x[j]-m)==abs(j-k))
		{
			return 0;
		}
			return 1;
}


/* OUTPUT

  
 Enter the no of queens: 4



QUEEN   COLUMN

 1      2
 2      4
 3      1
 4      3


QUEEN   COLUMN

 1      3
 2      1
 3      4
 4      2

*/
