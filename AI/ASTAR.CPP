#include<stdio.h>
#include<iostream.h>
#include<malloc.h>

typedef struct node
{   int node_index;
	int fn;
	int gn;
	int hn;
	node *parent;
	node *child;
	node *next;

};
node *start,*leaf[50];
FILE *fp;

int expanded[20];

void read_graph();
void read_from_file();
void extend_leaf(int l,node *add,int leafindex);
void search_min_fn();
void find_best_path();
int is_extend_over();





int edge[10][10],leaf_ptr,hn[10],destination,source;
int i,j,n;
void main()
{ int count=0;
  node *temp;
 
  read_from_file();
  start=(node *)malloc(sizeof(node));
  start->gn=0;
  start->node_index=source;
  start->fn=hn[source];

	for(i=0;i<n;i++)
			expanded[i]=0;
	expanded[source]=1;
  extend_leaf(source,start,-1);
  
  //display
  cout<<"\n The details are::\n";
  for(i=0;i<n;i++)
  {
	  cout<<hn[i]<<"\t";
	  for(j=0;j<n;j++)
		  cout<<" "<<edge[i][j];
	  cout<<"\n";
  }
  
  
  while(!is_extend_over())
  {	
	search_min_fn();

  }

  find_best_path();			 
	
}

void read_from_file()
{
	fp=fopen("details.txt","r");
	fscanf(fp,"%d",&n); //read n

	//read edge matrix
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			fscanf(fp,"%d",&edge[i][j]);
		}
	}
	
	//read heuristic func
	for(i=0;i<n;i++)
	{
		fscanf(fp,"%d",&hn[i]);
	}
	//source dest
	fscanf(fp,"%d",&source);
	fscanf(fp,"%d",&destination);
}
void read_graph()
{
	cout<<"\n Enter no of edges";
	cin>>n;
	cout<<"\n Enter weight of edges"
	<<"\n Enter a negative no if no edge present";


	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			cin>>edge[i][j];
		}
	}
	
}

void extend_leaf(int l,node *add,int leafindex)
{
int gn,j,k;
//remove add from leaf if not start
expanded[l]=1;
cout<<"\n EXPANDING NODE "<<l;
if(add!=start)
{
for(i=leafindex;i<leaf_ptr;i++)
	leaf[i]=leaf[i+1];
leaf_ptr--;
}
gn=add->gn;
j=0;

while(edge[l][j]<=0 && j<n)
	j++;

if(j<n)
{
add->child=(node *)malloc(sizeof(node));
add->child->parent=add;
add=add->child;
add->gn=gn+edge[l][j];
add->fn=gn+hn[j];
add->node_index=j;
add->child=NULL;
add->next=NULL;
//add in leaf
leaf[leaf_ptr++]=add;
j++;

}


for(;j<n;j++)
{	
	if(edge[l][j]>0)
	{	add->next=(node *)malloc(sizeof(node));
		add->next->parent=add->parent;
		add=add->next;
		add->gn=gn+edge[l][j];
		add->fn=gn+hn[j];
		add->child=NULL;
		add->node_index=j;
		add->next=NULL;
		leaf[leaf_ptr++]=add;
		//add in leaf
	}
	
}

//make edge[l][j]<0 for all j as it is visited
for(j=0;j<n;j++)
	edge[l][j]=-1;
//make edge[j][l]<0 for all j as it is visited
for(j=0;j<n;j++)
	edge[j][l]=-1;
}

void search_min_fn()
{int min_fn=0;	
i=0;

min_fn=i;
	for(;i<leaf_ptr;i++)
	{	
		if(leaf[i]->fn<leaf[min_fn]->fn)
		{
			min_fn=i;		
		}
	}

if(leaf[min_fn]->node_index!=destination)
	extend_leaf(leaf[min_fn]->node_index,leaf[min_fn],min_fn);
}

int is_extend_over()
{

	for(i=0;i<leaf_ptr;i++)
	{
		if(leaf[i]->node_index!=destination)
		{
			for(j=0;j<n;j++)
				if(edge[leaf[i]->node_index][j]>0)
					return 0;		
		}
		
	}

return 1;
}
void find_best_path()
{
node *temp;
int best_path=-1;
i=0;

	while(i<leaf_ptr && leaf[i]->node_index!=destination)
		i++;
  if(i<leaf_ptr)
	best_path=i;

  for(;i<leaf_ptr;i++)
	{	
		if(leaf[i]->node_index==destination && leaf[i]->fn<leaf[best_path]->fn)
			best_path=i;
	}

if(best_path!=-1)
	{ 
		temp=leaf[best_path];
		cout<<"\n A* Search returns \n";
		while(temp!=start)
		{ cout<<" "<<temp->node_index;
		  temp=temp->parent;
		}
		cout<<" "<<temp->node_index<<"\n";
	}
else
	cout<<"\n No Path Found";

   cout<<"\n There are "<<n<<"nodes"<<"\n All leaf paths found are\n";
	for(i=0;i<leaf_ptr;i++)
	{
		temp=leaf[i];
		cout<<"\t("<<leaf[i]->gn + hn[leaf[i]->node_index]<<")";
		while(temp!=start)
		{ cout<<" "<<temp->node_index;
		  temp=temp->parent;
		}
		cout<<" "<<temp->node_index<<"\n";

	}
}

/*OUTPUT
 
   
	 
 EXPANDING NODE 0
 The details are::
18       -1 -1 -1 -1 -1 -1 -1
11       -1 -1 10 6 -1 -1 -1
2        -1 10 -1 18 9 -1 -1
9        -1 6 18 -1 -1 70 -1
1        -1 -1 9 -1 -1 7 12
6        -1 -1 -1 70 7 -1 15
0        -1 -1 -1 -1 12 15 -1

 EXPANDING NODE 1
 EXPANDING NODE 2
 EXPANDING NODE 3
 EXPANDING NODE 4
 EXPANDING NODE 5
 A* Search returns
 6 4 2 1 0

 There are 7nodes
 All leaf paths found are
        (45) 3 2 1 0
        (40) 5 4 2 1 0
        (39) 6 4 2 1 0
        (99) 6 5 3 1 0
Press any key to continue




*/
