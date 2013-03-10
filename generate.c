#include<stdio.h>
int main(int argc,char *argv[])
{
	if(argc==1)
	{
		printf("Syntax: generate key\n");
		return 1;
	}
	if(strlen(argv[1])<8)
	{
		printf("Key %s should be of length 8 bytes\n",argv[1]);
		return 1;
	}
	char *key=argv[1];
	if(strlen(argv[1]>8)
	{
		printf("Key %s length is more than 8 bytes\nTruncating extra characters\n",argv[1]);
		key[8]=0;
	}
	printf("Key is %s\n",key);
	return 0;
}
	
	
