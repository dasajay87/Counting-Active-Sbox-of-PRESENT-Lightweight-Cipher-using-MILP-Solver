#include<stdio.h>
int next = 0; /* next unused state variable index */
int dummy = 0; /* next unused dummy variable index */
const int ROUNDS=5; /* number of rounds */
//int DBN=3;	/* DBN for PRESENT SBOX */
int i,j,r;
int dummy1=0;

	
void sbox(int a[][8]);

void permutation(int a[][8]);

//function for bits permutation....
void permutation(int a[8][8])
{
	int temp[64],j=0;
	for(int i=0;i<8;i++)
	{
			temp[j++]=a[0][i];
			temp[j++]=a[2][i];
			temp[j++]=a[4][i];
			temp[j++]=a[6][i];
		
	}
	for(int i=0;i<8;i++)
	{
			temp[j++]=a[1][i];
			temp[j++]=a[3][i];
			temp[j++]=a[5][i];
			temp[j++]=a[7][i];
		
	}
	int k=0;
	for(int i=0;i<8;i++)
		for(int j=0;j<8;j++)
			a[i][j]=temp[k++];
}

//function for sbox operation
void sbox(int a[8][8])
{
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<4;j++)
		{
			printf("x%i - a%i <= 0 \n", a[i][j], dummy);
		}
		printf("x%i + x%i + x%i + x%i - a%i >= 0 \n", a[i][0], a[i][1], a[i][2], a[i][3],dummy);
			
		printf("4 x%i + 4 x%i + 4 x%i + 4 x%i - x%i - x%i - x%i - x%i >= 0\n",a[i][0],a[i][1],a[i][2],a[i][3],next,next+1,next+2,next+3);
		printf("4 x%i + 4 x%i + 4 x%i + 4 x%i - x%i - x%i - x%i - x%i >= 0\n",next,next+1,next+2,next+3,a[i][0],a[i][1],a[i][2],a[i][3]);
		
		//Constraints for Differential Branch number... 
		printf("x%i + x%i + x%i + x%i + x%i + x%i + x%i + x%i - 3 d%i >= 0\n",a[i][0],a[i][1],a[i][2],a[i][3],next,next+1,next+2,next+3, dummy1);
		
		
		printf("d%i - x%i >= 0\n", dummy1,a[i][0]);
		printf("d%i - x%i >= 0\n", dummy1,a[i][1]);
		printf("d%i - x%i >= 0\n", dummy1,a[i][2]);
		printf("d%i - x%i >= 0\n", dummy1,a[i][3]);
		printf("d%i - x%i >= 0\n", dummy1,next);
		printf("d%i - x%i >= 0\n", dummy1,next+1);
		printf("d%i - x%i >= 0\n", dummy1,next+2);
		printf("d%i - x%i >= 0\n", dummy1,next+3);
		
		dummy++;
		dummy1++;
		for(int j=4;j<8;j++)
		{
			printf("x%i - a%i <= 0 \n", a[i][j], dummy);
		}
		printf("x%i + x%i + x%i + x%i - a%i >= 0 \n", a[i][4],a[i][5],a[i][6],a[i][7],dummy);
			
		printf("4 x%i + 4 x%i + 4 x%i + 4 x%i - x%i - x%i - x%i - x%i >= 0\n",a[i][4],a[i][5],a[i][6],a[i][7],next+4,next+5,next+6,next+7);
		printf("4 x%i + 4 x%i + 4 x%i + 4 x%i - x%i - x%i - x%i - x%i >= 0\n",next+4,next+5,next+6,next+7,a[i][4],a[i][5],a[i][6],a[i][7]);
		
		//Constraints for Differential Branch number... 
		printf("x%i + x%i + x%i + x%i + x%i + x%i + x%i + x%i - 3 d%i >= 0\n",a[i][4],a[i][5],a[i][6],a[i][7],next+4,next+5,next+6,next+7, dummy1);
		
		
		printf("d%i - x%i >= 0\n", dummy1,a[i][4]);
		printf("d%i - x%i >= 0\n", dummy1,a[i][5]);
		printf("d%i - x%i >= 0\n", dummy1,a[i][6]);
		printf("d%i - x%i >= 0\n", dummy1,a[i][7]);
		printf("d%i - x%i >= 0\n", dummy1,next+4);
		printf("d%i - x%i >= 0\n", dummy1,next+5);
		printf("d%i - x%i >= 0\n", dummy1,next+6);
		printf("d%i - x%i >= 0\n", dummy1,next+7);
		
		for(int j=0;j<8;j++)
			a[i][j]=next++;
		
		dummy1++; 
		dummy++;
		
	}
	
}



int main() 
{
  	int a[8][8]; /* the bits of the sypher004 input */
  	for (i = 0; i < 8; i++)
    		for (j = 0; j < 8; j++)
      			a[i][j] = next++; /* initialize variable indices */
  

  printf("Minimize\n"); /* print objective function */
  
  for (i=0; i<16*ROUNDS-1;i++)
  {
  	printf("a%i + ", i);
  }
  printf("a%i\n\n",i);
 
  /* round function constraints */
  printf("Subject To\n"); 
  for (r = 0; r<ROUNDS; r++) { sbox(a); permutation(a);}
  
  for(int i=0;i<63;i++)
  	printf("x%i + ", i);
  printf("x63 >= 1\n");

  printf("Binary\n"); /* binary constraints */
  for (i = 0; i < 64*ROUNDS+64; i++) printf("x%i\n", i);
  for (i = 0; i < 16*ROUNDS; i++) printf("a%i\n",i);
  for (i = 0; i < 16*ROUNDS; i++) printf("d%i\n",i);
  printf ("End\n");

	return 0;
}


