#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double get_execution_time(const struct timespec b_time,
                          const struct timespec e_time)
{
  return (e_time.tv_sec-b_time.tv_sec) +
                   (e_time.tv_nsec-b_time.tv_nsec)/1E9;
};


#define min(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _b : _a; })

void insertion_sort(int *a, int n) 
// Insertion sort array a of length n
{
  for(int j = 1; j < n; j++) {
	int key = a[j];
	// insert a[j] in the correct position a[0...(j-1)]
	int i = j - 1;
	while ((i >= 0) && (a[i] > key)) {
	  a[i + 1] = a[i];
	  i--;
	}
	a[i+1] = key;
  }
}


int partition(int *a, int n, int x)
// Partition array a of length n around x;
// Return the number of elements to the left of the pivot.
{
  // First find the pivot and place at the end
  for(int i = 0; i < n; i++) {
	if(a[i] == x) {
	  a[i] = a[n-1];
	  a[n-1] = x;
    }
  }

  int i = 0;
  for(int j = 0; j < (n-1); j++) {
	if(a[j] <= x) {
	  int tmp = a[j];
	  a[j] = a[i];
	  a[i] = tmp;
	  i++;
	}
  }

  // Place the pivot in the correct position
  a[n-1] = a[i];
  a[i] = x;

  return i;
};

int Select_pivot(int *A,int start,int end){
        int mat[5][end/5];
        int delta=0;
        for(int i=0;i<end/5;i++){
                for(int j=0;j<5;j++){
                        mat[j][i]=A[start+j+delta];
                }
                delta+=5;
        }

        for(int j=0;j<end/5;j++){
                for (int i = 1; i < 5; i++){
            int key = mat[i][j];
            int k = i - 1;
            while (k >= 0 && mat[k][j] > key)
            {
                mat[k + 1][j] = mat[k][j];
                k--;
            }
            mat[k + 1][j] = key;
        }
        }


        int pivot[2][end/5];
      for(int j=0;j<end/5;j++) {
         pivot[0][j]=j;
         pivot[1][j]=mat[2][j];
      }

            for (int i = 0; i < end/5; i++){
            int key = pivot[1][i];
            int k = i - 1;
            while (k >= 0 && pivot[1][k] > key)
	 {
                pivot[1][k+1] = pivot[1][k];
                int temp=pivot[0][k];
                pivot[0][k]=pivot[0][k+1];
                pivot[0][k+1] = temp;
                k--;
            }
            pivot[1][k + 1]= key;
        }
        for(int i=0;i<2;i++){
		for(int j=0;j<end/5;j++){
			printf("%d",pivot[i][j]);
		}
		printf("\n");
	}
        int median=pivot[1][end/10-1];
        for(int j=end/10-1;j<end/5;j++) {
         int count=0;

         for(int i=0;i<5;i++){
                if(mat[i][pivot[0][j]]>median){count++;}
        }
        if(count>=3){median=5*pivot[0][j]+3;}
      }
	printf("%d\n",median);
        return median;

};

void printArray(int *A,int n){
  for (int i=0; i<n; i++) {
    printf("%d ",A[i]);
  }
  printf("\n");
};

int select(int *a, int i, int n){
  int n_meds = 0;
  for(int i = 0; i < n; i += 5) {
	int l = min(5, n - i);
	insertion_sort(a + i, l);
	int tmp = a[i/5];
	a[i/5] = a[i + l/2];
	a[i + l/2] = tmp;
	n_meds++;
  }

  int median_of_medians;
  if(n_meds > 1) {
    median_of_medians = select(a, n_meds/2, n_meds);
  }
  else {
	median_of_medians = a[0];
  }
  int k = partition(a, n, median_of_medians);

  if(k == i) {
	return median_of_medians;
  }
  else if (i < k) {
	return select(a, i, k);
  }
  else {
	return select(a + k, i - k, n - k);
  }
}

void fill_array(int arrat[],int s){
        srand(time(NULL));
        for(int i=0;i<s;i++){
             arrat[i]=(rand() % (100-1));
        }
};

int main(int argc, char *argv[])
{
	struct timespec b_time, e_time;
	for(int n=10;n<25;n+=10){

		int first_c[n];
                fill_array(first_c,n);
		printArray(first_c,n);
		//clock_gettime(CLOCK_REALTIME, &b_time);
		//select(first_c,n/2,n);	
		//clock_gettime(CLOCK_REALTIME, &e_time);
		printf("\n");
                select(first_c,n/2,n);
                printf("\n");
                printf("%d",n);
                //printf("\t%lf\n", get_execution_time(b_time, e_time));
		printArray(first_c,n);
		printf("\n");

	}
  return 0;
}
