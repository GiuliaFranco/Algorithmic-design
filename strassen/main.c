#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "matrix.h"
#include "strassen.h"

#define MAX_ELEM_VALUE 25

void randomly_fill_matrix(Matrix *A)
{
   for (size_t i=0; i< A->rows; i++) {
     for (size_t j=0; j< A->cols; j++) {
   	   A->data[i][j]=rand()%(2*MAX_ELEM_VALUE)-MAX_ELEM_VALUE;
     }
   }
}
void clean_matrix(Matrix *A)
{
   A->rows=0;
   A->cols=0;
   for (size_t i=0; i< A->rows; i++) {
     for (size_t j=0; j< A->cols; j++) {
           A->data[i][j]=0;
     }
   }
}
double get_execution_time(const struct timespec b_time,
                          const struct timespec e_time)
{
  return (e_time.tv_sec-b_time.tv_sec) +
                   (e_time.tv_nsec-b_time.tv_nsec)/1E9;
}

int main(int argc, char *argv[]) {
    const size_t n=1<<11;
    Matrix *C0=allocate_matrix(n,n);
    Matrix *C1=allocate_matrix(n,n);
    Matrix *A=allocate_matrix(n,n);
    Matrix *B=allocate_matrix(n,n);
  
    srand(10);
    randomly_fill_matrix(A);
    randomly_fill_matrix(B);
  
    struct timespec b_time, e_time;

     for (size_t i=1; i<=n; i*=2) {
       printf("%ld", i);

       clock_gettime(CLOCK_REALTIME, &b_time);
       naive_matrix_mult(C0, A, B,i);
       clock_gettime(CLOCK_REALTIME, &e_time);

       printf("\t%lf", get_execution_time(b_time, e_time));

       clock_gettime(CLOCK_REALTIME, &b_time);
       strassen(C1, A, B, i);
       clock_gettime(CLOCK_REALTIME, &e_time);

       printf("\t%lf", get_execution_time(b_time, e_time));

       printf("\t%d\n", same_matrix(C0,C1));
       clean_matrix(C0);
       clean_matrix(C1);
  }


  deallocate_matrix(C0);
  deallocate_matrix(C1);
  deallocate_matrix(A);
  deallocate_matrix(B);

  return 0;
}
