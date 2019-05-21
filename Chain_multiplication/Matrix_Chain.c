#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <time.h>



double get_execution_time(const struct timespec b_time,
                          const struct timespec e_time)
{
  return (e_time.tv_sec-b_time.tv_sec) +
                   (e_time.tv_nsec-b_time.tv_nsec)/1E9;
}

int **allocate_matrix(size_t rows,size_t cols){
   int **A=(int **)malloc(sizeof(int *)*rows);

   for (size_t i=0; i<rows; i++) {
     A[i]=(int *)malloc(sizeof(int)*cols);
   }
   
   for (size_t i = 0; i < rows; i++) {
    for (size_t j = 0; j < cols; j++) {
      A[i][j]=0;
    }
  }
   return A;
};

void MatrixChainAux(int *P,int **m,int **s,int i,int j){
    m[i][j]=INT_MAX;
    int q=0;
    for(int k=i; k<j; k++){
       q=m[i][k]+m[k+1][j]+P[i]*P[k+1]+P[j+1];
       if(q<m[i][j]){
	  m[i][j]=q;
	  s[i][j-1]=k+1;
	}

    }
};


void MatrixChain(int *P,int n){
   int **m=allocate_matrix(n,n);
   int **s=allocate_matrix(n-1,n-1);
   for(int i=0; i<n; i++){
      m[i][i]=0;
   }
   for(int l=1; l<n; l++){
     for(int i=0; i<(n-l); i++){
        int j=i+l;
        MatrixChainAux(P,m,s,i,j);
       }

   }
   /*for (int i=0; i<n; i++){
    for(int c=0; c<n; c++){
         printf("%d     ", m[i][c]);
        }
    printf("\n");
    }
     printf("\n");  
    for (int i=0; i<n-1; i++){
    for(int c=0; c<n-1; c++){
         printf("%d     ", s[i][c]);
        }
    printf("\n");
    }*/
};

void fill_array(int arrat[],int s){
	srand(time(NULL));
	for(int i=0;i<s;i++){
		arrat[i]=rand();
	}
};


int main(){
  struct timespec b_time, e_time;
  for(int n=5;n<215;n+=10){
  	int first_c[n];
  	fill_array(first_c,n);
  	clock_gettime(CLOCK_REALTIME, &b_time);
  	MatrixChain(first_c,n);
  	clock_gettime(CLOCK_REALTIME, &e_time);  
  	printf("\n");
        printf("%d",n);
  	printf("\t%lf", get_execution_time(b_time, e_time));
  }
  return 0;



}

