#include<stdio.h>
#include<stdbool.h>
#include<string.h>
const short int pc1[56]={
			56,48,40,32,24,16,8,
			0,57,49,41,33,25,17,
			9,1,58,50,42,34,26,
			18,10,2,59,51,43,35,
			62,54,46,38,30,22,14,
			6,61,53,45,37,29,21,
			13,5,60,52,44,36,28,
			20,12,4,27,19,11,3
			};
const short int pc2[56]={
			13,16,10,23,0,4,2,27,
			14,5,20,9,22,18,11,3,
			25,7,15,6,26,19,12,1,
			40,51,30,36,46,54,29,39,
			50,44,32,47,43,48,38,55,
			33,52,45,41,49,35,28,31
			};
const short int cls_value[16]={1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};
const short int ip[64]=	{
			57,49,41,33,25,17,9,1,
			59,51,43,35,27,19,11,3,
			61,53,45,37,29,21,12,5,
			63,55,47,39,31,23,15,7,
			56,48,40,32,24,16,8,0,
			58,50,42,34,26,18,10,2,
			60,52,44,36,28,20,12,4,
			62,54,46,38,30,22,14,6
			};

const short int e[48]= {
			31,0,1,2,3,4,
			3,4,5,6,7,8,
			7,8,9,10,11,12,
			11,12,13,14,15,16,
			15,16,17,18,19,20,
			19,20,21,22,23,24,
			23,24,25,26,27,28,
			27,28,29,30,31,0
			};
const short int p[32]=	{
			15,6,19,20,28,11,27,16,
			0,14,22,25,4,17,30,9,
			1,7,23,13,31,26,2,8,
			18,12,29,5,21,10,3,24
			};			

void cls(bool key[],int c)
{
	int i=0;
	bool buffer[5];
	//shift ck, the left part
	for(i=0;i<c;i++)
		buffer[i]=key[i];
	for(i=0;i<28-c;i++)
		key[i]=key[i+c];
	for(i=28-c;i<28;i++)
		key[i]=buffer[i+c-28];
	//shift dk, the right part
	for(i=0;i<c;i++)
		buffer[i]=key[i+28];
	for(i=28;i<56-c;i++)
		key[i]=key[i+c];
	for(i=56-c;i<56;i++)
		key[i]=buffer[i+c-56];
}
bool xor(bool a,bool b)
{
	if(a==b)
		return false;
	else
		return true;
}	
	
		
int main(int argc,char *argv[])
{
	if(argc!=3)
	{
		printf("Syntax: <executable> <input file> <key>\n");
		return 1;
	}
	if(strlen(argv[2])<8)
	{
		printf("Length of key %s is less than 8 bytes\n",argv[2]);
		return 1;
	}
	char *key=argv[2];
	bool key_bin[64];
	bool key_permuted[56];
	bool k[16][48];
	int i,j;
	if(strlen(argv[2])>8)
	{
		printf("Length of key %s is more than 8 bytes..\nTruncating extra symbols\n",argv[2]);
		key[8]=0;
	}
	printf("input key : %s\n",key);
	//generate key in binary
	for(i=0;i<8;i++)
	{
		for(j=i*8;j<(i+1)*8;j++)
			key_bin[j]=0;
		int t=key[i];
		int k=(i+1)*8-1;
		while(t)
		{
			key_bin[k]=t%2;
			k--;
			t=t/2;
		}
	}
	printf("Key in binary(64) : \n");
	for(i=0;i<64;i++)
	{
		if(i&&i%8==0)
			printf(" ");
		printf("%d",key_bin[i]);
	}
	for(i=0;i<56;i++)
	{
		key_permuted[i]=key_bin[pc1[i]];
	}
	printf("\nKey after pc1(56) : \n");
	printf("C-1 : ");
	for(i=0;i<28;i++)
		printf("%d",key_permuted[i]);
	printf("\nD-1 : ");
	for(i=28;i<56;i++)
		printf("%d",key_permuted[i]);
	printf("\nKey generation process\n");
	for(i=0;i<16;i++)
	{
		printf("\nRound %d\n",i);
		cls(key_permuted,cls_value[i]);
		printf("Key after  %d cls : \n",cls_value[i]);
		printf("C%d  : ",i);
		for(j=0;j<28;j++)
			printf("%d",key_permuted[j]);
		printf("\nD%d  : ",i);
		for(j=28;j<56;j++)
			printf("%d",key_permuted[j]);
		for(j=0;j<48;j++)
			k[i][j]=key_permuted[pc2[j]];
	}
	printf("\n48 bit keys are\n");
	for(i=0;i<16;i++)
	{
		printf("\nRound %d \n",i);
		for(j=0;j<48;j++)
		{
			if(j&&!(j%8))
				printf(" ");
			printf("%d",k[i][j]);
		}
	}
	//read message from file
	char message[1024];
	bool message_conv[1024*8];
	FILE *ptr=fopen(argv[1],"r");
	if(ptr==NULL)
	{
		printf("Could not open file %s\n",argv[1]);
		return 1;
	}
	i=0;
	while(!feof(ptr))
		fscanf(ptr,"%c",&message[i++]);
	message[i]=0;
	printf("Message text : \n%s[eom]\n",message);
	//perform padding
	if(strlen(message)%8!=0)
	{
		printf("Perform padding\n");
		for(i=strlen(message);i%8!=0;i++)
		{
			message[i]='0';
		}
		message[i]=0;
		printf("Message after padding : \n%s\n",message);
	}
	for(i=0;i<strlen(message)/8;i++)
	{
		bool m[64];
		for(j=0;j<64;j++)
			m[j]=0;
		for(j=i*8;j<(i+1)*8;j++)
		{
			int t=message[j];
			int k=(j-i*8)*8+7;
			while(t)
			{
				m[k]=t%2;
				t=t/2;
				k--;
			}
		}
		//debugging print
		printf("\n");
		for(j=i*8;j<(i+1)*8;j++)
			printf("%c",message[j]);
		printf(" ");
		for(j=0;j<64;j++)
		{
			if(j&&!(j%8))
				printf(" ");
			printf("%d",m[j]);
		}
		//perform conversion
		for(j=0;j<16;j++)
		{
			printf("Round 1\nMessage\n");
			bool mr[48];
			int l=0;
			for(l=0;l<48;l++)
			{
				mr[l]=m[e[l]];
			}
			for(l=0;l<48;l++)
				mr[l]=xor(mr[l],k[j][l]);
			bool t[32];
			for(l=0;l<32;l++)
				t[l]=
	}
		

		
	printf("\n");
	return 0;
}
		
	
