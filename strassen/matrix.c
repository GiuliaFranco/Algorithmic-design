#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"

int naive_matrix_mult( Matrix *C,  Matrix  *A,  Matrix  *B, int n)
{
  if (A->cols != B->rows) {
     return -1;
  }

  // for all rows in A
  for (size_t i=0; i<n; i++) {

     // for all cols in B
     for (size_t j=0; j<n; j++) {

       // reset C[i][j]
       C->data[i][j] = 0.0;

       // sum all the element mults
       for (size_t k=0; k<n; k++) {
        C->data[i][j] += (A->data[i][k]*B->data[k][j]);
       }
     }
  }

  return 0;
}

Matrix* allocate_matrix(int rows,int cols)
{
   Matrix *A=malloc(sizeof(Matrix));
   A->cols=cols;
   A->rows=rows;
   A->f_row=0;
   A->f_col=0;
   A->data= malloc(sizeof(float*) * rows);
   for (size_t i=0; i<rows; i++) {
     A->data[i] = calloc(cols,sizeof(float));
   }
   return A;
}

void deallocate_matrix(Matrix *A)
{
  for (size_t i=0; i<A->rows; i++) {
    free(A->data[i]);
  }

  free(A->data);
}

int same_matrix(Matrix *A,Matrix *B)
{
   if ((A->rows != B->rows) || (A->cols != B->cols)) {
     return 2;
   }

   for (size_t i=0; i<A->rows; i++) {
     for (size_t j=0; j<A->cols; j++) {
        if (A->data[i][j] != B->data[i][j]) {
	         return 0;
        }
     }
   }

   return 1;
}
