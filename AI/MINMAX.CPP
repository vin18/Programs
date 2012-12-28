#include<stdio.h>
#include<iostream.h>
#include<malloc.h>
#define MIN(a,b) ((a)>(b)?(b):(a))
#define MAX(a,b) ((a)<(b)?(b):(a))
int id=0;
FILE *fp;


typedef struct gamestate
{
	int state_id;
	int no_of_successors;
	gamestate *successors[10];
	int utility_value;
};

gamestate *root;


int MAX_value(gamestate *state,int alpha,int beta);
int MIN_value(gamestate *state,int alpha,int beta);
void read_from_file(gamestate *tmp);
void display(gamestate *tmp);


void main()
{int v,i;
gamestate *temp=root;
	fp=fopen("minmax.txt","r");
	root=( gamestate *)malloc(sizeof(gamestate));

	read_from_file(root);
	//display all

	printf("\n\n");
//	display(root);
	v=MAX_value(root,-999,+999);
	printf("\n\n MinMax Decision function returns %d",v);

	for(i=0;i<root->no_of_successors;i++)
		if(root->successors[i]->utility_value==v)
		{
			printf("\n Choose Successor %d State ID %d \n\n",i,root->successors[i]->state_id);
			return;
		}


	
	
}


int MAX_value(gamestate *state,int alpha,int beta)
{
int v,i=0;
gamestate *a;
	if(state->no_of_successors==0)
	{

		return(state->utility_value);
	}

	v=-999;
	a=state->successors[i];
	while(a!=NULL)
	{
		v=MAX(v,MIN_value(a,alpha,beta));
		if(v>=beta)
		{
			return v;
		}
		alpha=MAX(alpha,v);
		i++;
		
		a=state->successors[i];
	}

return v;
}

int MIN_value(gamestate *state,int alpha,int beta)
{
int v,i=0;
gamestate *a;
	if(state->no_of_successors==0)
	{

		return(state->utility_value);
	}

	v=999;
	a=state->successors[i];
	while(a!=NULL)
	{
		v=MIN(v,MAX_value(a,alpha,beta));
		if(v<=alpha)
		{


			return v;
		}
		beta=MIN(beta,v);
		i++;
		
		a=state->successors[i];
	}
return v;
}


void read_from_file(gamestate *tmp)
{//read file in bfs format
	int i=0;

	fscanf(fp,"%d",&tmp->utility_value);
	fscanf(fp,"%d",&tmp->no_of_successors);

	tmp->state_id=id++;

	//display read info::
	//printf("\n ID = %d Successors %d Utility %d",tmp->state_id,tmp->no_of_successors,tmp->utility_value);

	for(i=0;i<10;i++)
		tmp->successors[i]=NULL;

	for(i=0;i<tmp->no_of_successors;i++)
	{
		tmp->successors[i]=( gamestate *)malloc(sizeof(gamestate));
		read_from_file(tmp->successors[i]);
	}
}

void display(gamestate *tmp) 
{int i;
gamestate *temp;
printf("\n\n\n ID = %d Successors %d Utility %d",tmp->state_id,tmp->no_of_successors,tmp->utility_value);

	for(i=0;i<tmp->no_of_successors;i++)
	{
		temp=tmp->successors[i];
		printf("\n ID = %d Successors %d Utility %d",temp->state_id,temp->no_of_successors,temp->utility_value);
	
	}

	for(i=0;i<tmp->no_of_successors;i++)
		display(tmp->successors[i]);
	

}


/*
INPUT File::: 

0 3
0 3
3 0
12 0
8  0
0 3
2 0
4 0
6 0
0 3
14 0
5 0
2 0
*/


/*  OUTPUT




 MinMax Decision function returns 3
 Choose Successor 0 State ID 1 

Press any key to continue
*/