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
			61,53,45,37,29,21,13,5,
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
const short int s[8][4][16]={
				{
					{14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
					{0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
					{4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
					{15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}
				},
				{
					{15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
					{3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
					{0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
					{13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}
				},
				{
					{10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
					{13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
					{13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
					{1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}
				},
				{
					{7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
					{13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
					{10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
					{3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14},
				},
				{
					{2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
					{14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
					{4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
					{11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3},
				},
				{
					{12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
					{10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
					{9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
					{4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}
				},
				{
					{4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
					{13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
					{1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
					{6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12},
				},
				{
					{13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
					{1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
					{7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
					{2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11},
				}
			
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
	if(argc!=4)
	{
		printf("Syntax: <executable> <input file> <key> <output file>\n");
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
	int i,j,l;
	if(strlen(argv[2])>8)
	{
		printf("Length of key %s is more than 8 bytes..\nTruncating extra symbols\n",argv[2]);
		key[8]=0;
	}
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
	for(i=0;i<56;i++)
	{
		key_permuted[i]=key_bin[pc1[i]];
	}
	for(i=0;i<16;i++)
	{
		cls(key_permuted,cls_value[i]);
		for(j=0;j<48;j++)
		{
			k[i][j]=key_permuted[pc2[j]];
		}
	}
	//read message from file
	char message[1024];
	bool message_bin[8192];
	FILE *ptr=fopen(argv[1],"r");
	if(ptr==NULL)
	{
		printf("Could not open file %s\n",argv[1]);
		return 1;
	}
	i=0;
	while(!feof(ptr))
		fscanf(ptr,"%c",&message[i++]);
	message[i-1]=0;
	fclose(ptr);
	printf("\nMessage text : \n%s[eom]\n",message);
	//convert message to binary
	for(i=0;i<strlen(message);i++)
	{
		for(j=i*8;j<(i+1)*8;j++)
			message_bin[j]=0;
		l=(i+1)*8-1;
		int t=message[i];
		while(t)
		{
			message_bin[l]=t%2;
			t=t/2;
			l--;
		}
	}
	int len=strlen(message)*8;
	//perform padding
	if((len%64)!=0)
	{
		while((len%64)!=0)
		{
			message_bin[len]=0;
			len++;
		}
	}
	
	ptr=fopen(argv[3],"w");
	for(i=0;i<len/64;i++)
	{
		bool block[64];
		for(j=i*64;j<(i+1)*64;j++)
		{
			block[j-i*64]=message_bin[j];
		}
		//perform initial permutation
		printf("block in binary\n");
		for(j=0;j<64;j++)
			printf("%d",block[j]);
		printf("\n");
		bool t_bin[64];
		for(j=0;j<64;j++)
			t_bin[j]=block[ip[j]];
		printf("Message after initial permutation\n");
		for(j=0;j<64;j++)
		{
			if(j&&!(j%8))
				printf(" ");
			printf("%d",t_bin[j]);
		}
		for(j=0;j<16;j++)
		{
			printf("\nRound %d\n",j);
			printf("Input message\n");
			for(l=0;l<64;l++)
			{
				if(l&&!(l%32))
					printf(" ");
				printf("%d",t_bin[l]);
			}
			bool mr[32];
			//seperate right part
			for(l=32;l<64;l++)
				mr[l-32]=t_bin[l];
			printf("\nRight part\n");
			for(l=0;l<32;l++)
			{
				if(l&&!(l%4))
					printf(" ");
				printf("%d",mr[l]);
			}
			//expand right part
			bool mre[48];
			for(l=0;l<48;l++)
				mre[l]=mr[e[l]];
			printf("\nExpanded right\n");
			for(l=0;l<48;l++)
			{
				if(l&&!(l%6))
					printf(" ");
				printf("%d",mre[l]);
			}
			printf("\nKey\n");
			for(l=0;l<48;l++)
			{
				if(l&&!(l%6))
					printf(" ");
				printf("%d",k[j][l]);
			}
			//perform xor operation
			for(l=0;l<48;l++)
				mre[l]=xor(mre[l],k[j][l]);
			printf("\nAfter xor operation\n");
			for(l=0;l<48;l++)
			{
				if(l&&!(l%6))
					printf(" ");
				printf("%d",mre[l]);
			}
			bool f[32];
			for(l=0;l<8;l++)
			{
				int a;
				bool sip[6];
				for(a=l*6;a<(l+1)*6;a++)
					sip[a-l*6]=mre[a];
				int x=sip[0]*2+sip[5];
				int y=0;
				for(a=1;a<5;a++)
					y=y*2+sip[a];
				int z=s[l][x][y];
				for(a=l*4;a<(l+1)*4;a++)
					f[a]=0;
				a=(l+1)*4-1;
				while(z)
				{
					f[a]=z%2;
					z=z/2;
					a--;
				}
			}
			printf("\nOutput of sbox\n");
			for(l=0;l<32;l++)
			{
				if(l&&!(l%4))
					printf(" ");
				printf("%d",f[l]);
			}
			bool f_permuted[32];
			for(l=0;l<32;l++)
				f_permuted[l]=f[p[l]];
			printf("\nPermuted output of sbox\n");
			for(l=0;l<32;l++)
			{
				if(l&&!(l%4))
					printf(" ");
				printf("%d",f_permuted[l]);
			}
			for(l=0;l<32;l++)
				t_bin[l+32]=xor(t_bin[l],f_permuted[l]);
			for(l=0;l<32;l++)
				t_bin[l]=mr[l];
			printf("\nOutput message\n");
			for(l=0;l<64;l++)
			{
				if(l&&!(l%4))
					printf(" ");
				printf("%d",t_bin[l]);
			}
			
		}
		//exchange left and right
		bool temp;
		for(j=0;j<32;j++)
		{
			temp=t_bin[j];
			t_bin[j]=t_bin[j+32];
			t_bin[j+32]=temp;
		}
		//perform reverse ip
		for(j=0;j<64;j++)
			block[ip[j]]=t_bin[j];
		printf("\nFinal encrypted message\n");
		for(j=0;j<64;j++)
		{
			if(j&&!(j%4))
				printf(" ");
			printf("%d",block[j]);
			fprintf(ptr,"%d",block[j]);
		}
		
	}	
			
		
		
	fclose(ptr);
	printf("\n");
	return 0;
}
		
	
