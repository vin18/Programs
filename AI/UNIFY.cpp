#include<stdio.h>
#include<conio.h>
#include<string.h>

char line1[100],line2[100],theta[100];
int i;


void read_line(char buf[]);
void unify(char x[],char y[]);
void unify_var(char var[],char x[]);

char *rest(char a[]);
char *first(char a[]);
char *op(char a[]);
char *arg(char a[]);
char *search_val(char a[],int l);

int ispresent(char a[]);
int iscompound(char a[]);
int islist(char a[]);
int isvariable(char a[]);


void main()
{char temp[100];
	
	printf("\nAll small single letters will be considered as variables");
	printf("\nCompounds inside Main Compound can have only one variable\n\n");


	printf("\nEnter the Main Compound 1\n");
	scanf("%s",&line1);
	printf("\nEnter the Main Compound 2\n");
	scanf("%s",&line2);

	
	sprintf(theta,"");

	unify(line1,line2);

	printf("\nUnification gives::\n%s\n",theta);

}


void unify(char x[],char y[])
{char a[100],b[100];
	
	if(strcmp(theta,"FAILURE")==0)
		return;

	if(strcmp(x,y)==0)
		return;

	else if(isvariable(x))
		unify_var(x,y);

	else if(isvariable(y))
		unify_var(x,y);

	else if(iscompound(x) && iscompound(y))
	{
		
		strcpy(a,arg(x));
		strcpy(b,arg(y));
		unify(a,b);

		strcpy(a,op(x));
		strcpy(b,op(y));
		unify(a,b);

	}

	else if(islist(x) && islist(y))
	{

		strcpy(a,rest(x));
		strcpy(b,rest(y));
		unify(a,b);
		
		strcpy(a,first(x));
		strcpy(b,first(y));
		unify(a,b);

	}
	
	else 
		sprintf(theta,"FAILURE",theta);

	


return;

}

char *first(char a[])
{char r[100];
sscanf(a+1,"%[^,]s",&r);
if(strcmp(a+1,r)==0)
	{sscanf(a+1,"%s",&r);
		r[strlen(r)-1]='\0';
	}
return r;
}

char *rest(char a[])
{char r[100],c[100];
sscanf(a+1,"%[^,]s",&r);
if(strcmp(r,a+1)==0)
	sprintf(r,"()");
else
	strcpy(r+1,a+strlen(r)+2);
r[0]='(';
return r;
}

char *op(char a[])
{char r[100];
sscanf(a,"%[^(]s",&r);
return r;
}


char *arg(char a[])
{char r[100];
sscanf(a,"%[^(]s",&r);
strcpy(r,a+strlen(r));
return r;
}

int islist(char a[])
{
	if(a[0]=='(' && a[strlen(a)-1]==')' && (strlen(a)>2))
		return 1;

return 0;
}

int iscompound(char a[])
{
	if(a[0]!='(' && a[strlen(a)-1]==')')
		return 1;
return 0;
}

int isvariable(char a[])
{
	if(strlen(a)==1 && a[0]>'a')
		return 1;
return 0;
}

void unify_var(char var[],char x[])
{char val[100],a[100];


i=0;
sprintf(a,"%s/",var);
	while(i<strlen(theta))
	{
		
		strcpy(val,search_val(a,i));
		if(strlen(val)>0)
			unify(val,x);

		i=i+strlen(a)-1;


	}

i=0;
sprintf(a,"%s/",x);

	while(i<strlen(theta))
	{
		strcpy(val,search_val(a,i));
		if(strlen(val)>0)
			unify(var,val);
		i=i+strlen(a)-1;

	}
sprintf(val,"%s/%s;",var,x);
if(ispresent(val))
	return;

sprintf(theta+strlen(theta)-1," %s",val);

}


char *search_val(char a[],int l)
{char val[100],*b;

sprintf(val,"");

	if(strlen(theta+l)>strlen(a))
	{
		
		b=strstr(theta+l,a);
		sprintf(val,"%s",b);
		if(strcmp(val,"(null)")==0)
			sprintf(val,"");
		else
			sprintf(val,"%[^;]s",val);

	}
return val;
}

int ispresent(char a[])
{char *b,tmp[100];
	if(strlen(theta)>strlen(a))
	{
		b=strstr(theta,a);
		sprintf(tmp,"%s",b);
		if(strcmp(tmp,"(null)")==0)
			return 0;
		else return 1;

	}

return 0;

}
/*
INPUT

5

0 1 1 0 1
1 0 1 1 0
1 1 0 1 1
0 1 1 0 1
1 0 1 1 0

*/
/*

All small single letters will be considered as variables
Compounds inside Main Compound can have only one variable


Enter the Main Compound 1
happy(x)

Enter the Main Compound 2
happy(Me)

Unification gives::
x/Me;
Press any key to continue


All small single letters will be considered as variables
Compounds inside Main Compound can have only one variable


Enter the Main Compound 1
knows(john,x)

Enter the Main Compound 2
knows(y,mother(y))

Unification gives::
x/mother(y) john/y;
Press any key to continue
*/