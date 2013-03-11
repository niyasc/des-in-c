#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>
#include<ctype.h>
bool notin(int key_plus[],int t)
{
	bool result=true;
	int i;
	for(i=0;i<56&&key_plus[i]!=56;i++)
	{
		if(t==key_plus[i])
		{
			result=false;
			break;
		}
	}
	return result;
}
bool isnumber(char seed[])
{
	int i;
	bool ok=true;
	for(i=0;seed[i]!=0;i++)
	{
		if(!isdigit(seed[i]))
		{
			ok=false;
			break;
		}
	}
	return ok;
}
int main(int argc,char *argv[])
{
	if(argc!=2)
	{
		printf("Syntax: <executable> seed_value\n");
		return 1;
	}
	if(!isnumber(argv[1]))
	{
		printf("Syntax: <executable> seed_value\n");
		return 1;
	}
	int i,j;
	int seed=0;
	for(i=0;argv[1][i]!=0;i++)
		seed=seed*10+(int )(argv[1][i]-48);
	printf("Seed : %d\n",seed);
	int key_plus[56];
	for(i=0;i<56;i++)
		key_plus[i]=56;
	srandom(seed);
	i=0;
	while(i<56)
	{
		int t=random()%55;
		if(t%8!=7&&notin(key_plus,t))
		{
			key_plus[i]=t;
			i++;
		}
		else if(t%8!=7&&notin(key_plus,t+1))
		{
			key_plus[i]=t+1;
			i++;
		}
	}
	printf("Key Plus \n");
	for(i=0;i<56;i++)
		printf("%d ",key_plus[i]);
	printf("\n");
	//printf("Key is %s\n",key);
	return 0;
}
	
	
