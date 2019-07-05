#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int Left(int* m,int i){return 2*i+1;};
int Right(int* m,int i){return 2*i+2;};
int Parent(int* m,int i){return (i-1)/2;};
int GetRoot(int* m){return m[0];};
bool IsRoot(int* m,int i){
	if(m[0]==i) return true;
	else return false;
};

bool IsValidNode(int n,int i){
	if(i>=n) false;
        if(i<n) true;
};

void Heapify(int* a,int n,int i){
    int m=i;
    int left=Left(a,i);
    int right=Right(a,i);   
    if(IsValidNode(n,left) && a[left]>a[m]){m=left;}
    if(IsValidNode(n,right) && a[right]>a[m]){m=right;}
    if(m!=i){
	swap(&a[i],&a[m]);
	Heapify(a,n,m);
    } 
};

void Build_Heap(int* a,int n){
       int par=Parent(a,n-1);
        for(int j=par;j>=0;j--){
                Heapify(a,n,j);
        }
};

double get_execution_time(const struct timespec b_time,
                          const struct timespec e_time)
{
  return (e_time.tv_sec-b_time.tv_sec) +
                   (e_time.tv_nsec-b_time.tv_nsec)/1E9;
};


void fill_array(int arrat[],int s){
        srand(time(NULL));
        for(int i=0;i<s;i++){
                arrat[i]=rand() % (20-1);
        }
};

void Remove_min(int a[],int n){
    a[0]=a[n-1];
    Heapify(a,0,n-1);
};


void Decrease(int a[],int i, int v){
    if(a[i]>=v) printf ("error!");
    a[i]=v;
    while( !(  IsRoot(a,i) || a[Parent(a,i)]>=a[i] )){
        swap(&a[i],&a[Parent(a,i)]);
        i=Parent(a,i);
    }

};


int* Insert(int a[], int v,int n){
    int newsize=n+1;
    int* newHeap=(int*)malloc(sizeof(int)*newsize);
    for(size_t i = 0; i < newsize-1; i++)
    {
        newHeap[i]=a[i];
    }
    newHeap[newsize]=-INT_MAX;
    Decrease(newHeap,newsize,v);
    free(a);
    return newHeap;
};


void HeapSort(int* a,int n){
	Build_Heap(a,n);
	for (int i=n-1; i>=0; i--) 
        { 
	    swap(&a[0], &a[i]);
            Heapify(a, i, 0); 
        }

};

void printArray(int arr[], int n) 
{ 
    for (int i=0; i<n; ++i) 
        printf("%d\n",arr[i]); 
    printf("\n");
};
int main(){
	struct timespec b_time, e_time;
        for(int n=5;n<250;n+=10){
                int a[n];
		fill_array(a,n);
                clock_gettime(CLOCK_REALTIME, &b_time);
		Build_Heap(a,n);
          	HeapSort(a,n);
	        clock_gettime(CLOCK_REALTIME, &e_time);
                printf("\n");
                printf("%d",n);
                printf("\t%lf", get_execution_time(b_time, e_time));
        }

	return 0;
}
