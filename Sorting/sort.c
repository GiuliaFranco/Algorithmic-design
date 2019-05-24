#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdlib.h>

double get_execution_time(const struct timespec b_time,
                          const struct timespec e_time)
{
  return (e_time.tv_sec-b_time.tv_sec) +
                   (e_time.tv_nsec-b_time.tv_nsec)/1E9;
};

void printArray(int *A,int n){
  for (int i=0; i<n; i++) {
    printf("%d ",A[i]);
  }
  printf("\n");
};

void Insertion_sort(int *a,int n){
  int i=1;
  while(i < n)
        {
            int x = a[i];
            while (i >= 1 && a[i-1]>x)
            {
                a[i] = a[i-1];
                i--;

            }
            a[i] = x;
	    i++;
        }
};
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int Partition(int *a, int l, int r, int x)
{
    int search=0;
    int i = 0;
    for (i=l; i<r; i++)
        if (a[i] == x) search=i;
    swap(&a[search], &a[r]);
    i = l;
    int j=l;
    while(j <= r - 1)
    {
        if (a[j] <= x)
        {
            swap(&a[i], &a[j]);
            i++;
        }
        j++;
    }
    swap(&a[i], &a[r]);
    return i;
};
//Bool==0 -> worst case
//Bool==1 -> best case

// select a pivot and partition the array. Repeat on the subarrays until the whole array is sorted.
void QuickSort(int *a, int start, int end,int Bool)
{
    int i;
    int j=0;
    if(Bool==0){
	j=a[end];	
    }
    if(Bool==1){j=a[(start+end)/2];}
    if (start < end)
    {
        i = Partition(a, start, end,j);
 
        QuickSort(a, start, i - 1,Bool);
        QuickSort(a, i + 1, end,Bool);
    }
};

//counting the occurrence of A values in an array. NOT in-place.
void counting_sort(int *A,int A_len,int *B,int k){
	int C[k];
	for(int i=0; i<k;i++){
		C[i]=0;
	} 

	for(int j=0;j<A_len;j++){
		C[A[j]]=C[A[j]]+1;
	}

	for(int j=1;j<k;j++){
                C[j]=C[j]+C[j-1]; // sums the values in C and reorder A into B 
        }

	for(int j=A_len-1;j>=0;j--){  //backward placing for preserving the order of equivalent elements.
                B[C[A[j]]-1]=A[j];
		C[A[j]]=C[A[j]]-1;
        }
};
//we can sort each element of the array digit by digit.
void radixSort(int * A, int size){
  // Base 10 is used since array's values are the random generated till 350.
  int i;
  int *B=(int*)malloc(sizeof(int)*size);
  int basis=10;
  int max = 0,unit=1;
  for(i = 0; i < size; i++){
    if(A[i] >= max)
      max = A[i];
  }
  while (max / unit > 0){   
    int *C=(int*)malloc(sizeof(int)*basis);
    for(i = 0; i < basis; i++) C[i]=0;
    for (i = 0; i < size; i++)
      	C[(A[i] / unit) % basis]++; //count frequencies
    for(i = 1; i < basis; i++)
	      C[i] += C[i - 1];  //cumulates
    
    // Use the bucket to fill a "semiSorted" array
    for (i = size - 1; i >= 0; i--)
      B[--C[(A[i] / unit) % basis]] = A[i];   //move records
      C[(A[i] / unit) % basis]--;
    
    for (i = 0; i < size; i++)
      A[i] = B[i]; //copy back
    
    free(C);
    unit *= 10;
  }  
  free(B);
};


void bucketSort(int * A,int n)
{
    int num_buckets=5;   //max el 350
    int *freq=(int*)malloc(sizeof(int) * num_buckets);
    for (int i = 0; i < num_buckets; i++){  freq[i]=0;}
    int **list=(int**)malloc(sizeof(int*)*num_buckets);
    for (int i = 0; i < num_buckets; i++){
        list[i]=(int*)malloc(sizeof(int) * n);
    }
    for (int i = 0; i < n; i++){
        if (A[i] <= 70){  list[0][freq[0]++] = A[i]; }
        if (A[i] > 70 && A[i] <=140){ list[1][freq[1]++] = A[i];}
	if (A[i] > 140 && A[i] <=210){ list[2][freq[2]++] = A[i];}
	if (A[i] > 210 && A[i] <=280){ list[3][freq[3]++] = A[i];}
	if (A[i] > 280){ list[4][freq[4]++] = A[i];}
    }
   int count=0;
   for (int i = 0; i < num_buckets; i++){  
      // now using Insertion sort to sort the elements of bucket
        Insertion_sort(list[i], freq[i]);
    	for (int j = 0; j < freq[i]; j++)
        {
            A[count + j] = list[i][j];
        }
        count += freq[i];
        free(list[i]);
    }
   free(list);
}
 

void fill_array(int arrat[],int s){
        srand(time(NULL));
        for(int i=0;i<s;i++){
             arrat[i]=(rand() % (350-1));
	}
};

void rvereseArray(int arr[], int n){
	int elem=n;
	for(int i=0;i<=n;i++){
		arr[i]=elem;
		elem--;
	} 
};

//Insertion: best case (array already sorted), worst case (array in deacreasing order).
//Quick_sort: worst case (array already sorted-> pivot at the end), best case(pivot->median).


int main(){

	struct timespec b_time, e_time;
	printf("#elem  Insertion_sort (best case)\n");
  	for(int n=10;n<250;n+=10){
        	int first_c[n];
		fill_array(first_c,n);
		Insertion_sort(first_c,n);
		clock_gettime(CLOCK_REALTIME, &b_time);
		Insertion_sort(first_c,n);
		clock_gettime(CLOCK_REALTIME, &e_time);
		printf("\n");
                printf("%d",n);
                printf("\t%lf", get_execution_time(b_time, e_time));
	}
	struct timespec b_time_w, e_time_w;
        printf("\n#elem  Insertion_sort (worst case)\n");
        for(int n=10;n<250;n+=10){
                int first_c[n];
                fill_array(first_c,n);
                rvereseArray(first_c,n);
                clock_gettime(CLOCK_REALTIME, &b_time_w);
                Insertion_sort(first_c,n);
                clock_gettime(CLOCK_REALTIME, &e_time_w);
                printf("\n");
                printf("%d",n);
                printf("\t%lf", get_execution_time(b_time_w, e_time_w));
        }
	struct timespec b_time_quick, e_time_quick;
	printf("\n#elem  Quick_sort (best case)\n");
	for(int n=10;n<250;n+=10){
                int first_c[n];
                fill_array(first_c,n);
                clock_gettime(CLOCK_REALTIME, &b_time_quick);
		QuickSort(first_c,0,n-1,1);
		clock_gettime(CLOCK_REALTIME, &e_time_quick);
                printf("\n");
                printf("%d",n);
                printf("\t%lf", get_execution_time(b_time_quick, e_time_quick));

	}
	struct timespec b_time_quick_w, e_time_quick_w;
        printf("\n#elem  Quick_sort (worst case)\n");
        for(int n=10;n<250;n+=10){
                int first_c[n];
                fill_array(first_c,n);
		Insertion_sort(first_c,n);
                clock_gettime(CLOCK_REALTIME, &b_time_quick_w);
                QuickSort(first_c,0,n-1,0);
                clock_gettime(CLOCK_REALTIME, &e_time_quick_w);
                printf("\n");
                printf("%d",n);
                printf("\t%lf", get_execution_time(b_time_quick_w, e_time_quick_w));

        }
	
	struct timespec b_time_count, e_time_count;
        printf("\n#elem  Counting sort\n");
	for(int n=10;n<250;n+=10){
                int first_c[n];
                fill_array(first_c,n);
		int max=first_c[0];
                for(int i=1;i<n;i++){ if(first_c[i]>max) max=first_c[i];}
                int B[n];
                for(int i=0; i<n;i++){B[i]=0;}
		clock_gettime(CLOCK_REALTIME, &b_time_count);
		counting_sort(first_c,n,B,max+1);
		clock_gettime(CLOCK_REALTIME, &e_time_count);
		printf("\n");
                printf("%d",n);
                printf("\t%lf", get_execution_time(b_time_count, e_time_count));
	}

	struct timespec b_time_radix, e_time_radix;
        printf("\n#elem Radix sort\n");
	for(int n=10;n<250;n+=10){
                int first_c[n];
                fill_array(first_c,n);
		clock_gettime(CLOCK_REALTIME, &b_time_radix);
		radixSort(first_c,n);
		clock_gettime(CLOCK_REALTIME, &e_time_radix);
                printf("\n");
                printf("%d",n);
                printf("\t%lf", get_execution_time(b_time_radix, e_time_radix));

	}

	struct timespec b_time_bucket, e_time_bucket;
        printf("\n#elem Bucket sort\n");
        for(int n=10;n<250;n+=10){
                int first_c[n];
                fill_array(first_c,n);
                clock_gettime(CLOCK_REALTIME, &b_time_bucket);
		bucketSort(first_c,n);
                clock_gettime(CLOCK_REALTIME, &e_time_bucket);
                printf("\n");
                printf("%d",n);
                printf("\t%lf", get_execution_time(b_time_bucket, e_time_bucket));

        }

	return 0;
}
