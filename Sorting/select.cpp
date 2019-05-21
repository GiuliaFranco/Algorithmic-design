#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

void Insertion_sort(int *A,int s,int n){
  for (int i =1+ s; i < n; i++)
        {
            int key = A[i];
            int j = i - 1;
            while (j >= 0 && A[j] > key)
            {
                A[j + 1] = A[j];
                j--;
            }
            A[j + 1] = key;
        }
};


void printArray(int* a,int n){
    int i;
    for (i=0; i <n; i++)
           cout<<a[i]<<endl;
    cout<<endl;
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int New_partition(int* a, int start, int end, int p)
{
  swap(&a[start],&a[p]);
  p = start;
  int i=start;
  int j=end;
  bool dup = 0;
  while (i <= j) {
    if (a[i] > a[p] ) {
      swap(&a[i], &a[j]);
      j--;
    }
    if(a[i] < a[p])  i++;
    if(a[i] == a[p] && dup){
		swap(&a[i], &a[j]);
        	j--;
    	}
    if(a[i] == a[p] && !dup){
	i++;
        dup=!dup;
    }
   
  }
  swap(&a[p],&a[j]);
  return j;
}

int Median_Five(int* a, int start, int end)
{
  int size=end - start + 1;
  int chunks = (size-1) / 5 + 1;
  if (size <6) {
    Insertion_sort(a, start, end);
    return (start + end) / 2;
  }

  int delta=5;
  for(int i=start+4;i<end-5;i+=delta){Insertion_sort(a,i-4,i);}
  int j=start+delta;
  int i=start;
  while(i<chunks){
	swap(&a[i],&a[(j + i * 5) / 2]);
	if(j+delta>=end) break;
	else j+=delta;
	i++;
   }
  int range=start + chunks;
  int median = Median_Five(a,start,range);
  return median;
}


int Quick_select(int* a, int i, int start, int end)
{

  int med = Median_Five(a, start, end);
  int piv = New_partition(a, start, end, med);
  if (i == piv+1)  return a[piv];
  if (i < piv+1)  return Quick_select(a, i,start, piv-1);
  else return Quick_select(a, i, piv + 1, end);

}


void fill_array(int* arrat,int s){
       for(int i=0;i<s;i++)
            arrat[i]=(rand() % 200);
};


int main()
{

    		for(int n=11;n<15;n+=10){
                int first_c[n];
                fill_array(first_c,n);
                printArray(first_c,n);
		clock_t begin = clock();
		for(int p=0;p<n;p++) cout<<Quick_select(first_c,p,0,n)<<endl;
		clock_t end = clock();
                cout<<n<<"  "<<double(end - begin) / CLOCKS_PER_SEC<<endl;
                }

		return 0;
}

