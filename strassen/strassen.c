#include <stdlib.h>

#include "matrix.h"


void sum_matrix_blocks(Matrix *C,const size_t C_row,const size_t C_col, Matrix *A,const size_t A_row,const size_t A_col, Matrix *B,const size_t B_row,const size_t B_col,const size_t n)
{
  // for all the rows in the blocks
  for (size_t i=0; i<n; i++) {

    // for all the cols in the blocks
    for (size_t j=0; j<n; j++) {

      	C->data[C->f_row+i][C->f_col+j] = A->data[A->f_row+i][A->f_col+j] + B->data[B->f_row+i][B->f_col+j];

    }
  }
}

void sub_matrix_blocks(Matrix *C,const size_t C_row,const size_t C_col, Matrix *A,const size_t A_row,const size_t A_col, Matrix *B,const size_t B_row,const size_t B_col,const size_t n)
{
  // for all the rows in the blocks
  for (size_t i=0; i<n; i++) {

    // for all the cols in the blocks
    for (size_t j=0; j<n; j++) {
      C->data[C->f_row+i][C->f_col+j] = A->data[A->f_row+i][A->f_col+j] -
                                B->data[B->f_row+i][B->f_col+j];
    }
  }
}

void naive_aux(Matrix *C, Matrix *A, Matrix *B,const size_t n)
{
   for (size_t i=0; i<n; i++) {
     for (size_t j=0; j<n; j++) {
       C->data[C->f_row+i][C->f_col+j] = 0.0;
       for (size_t k=0; k<n; k++) {
         C->data[C->f_row+i][C->f_col+j] += (A->data[A->f_row+i][A->f_col+k]*
                                     B->data[B->f_row+k][B->f_col+j]);
       }
     }

   }
}

void strassen_aux(Matrix *C,const size_t C_row,const size_t C_col, Matrix *A,const size_t A_row,const size_t A_col, Matrix *B,const size_t B_row,const size_t B_col, const size_t n)
{
  if (n < (1<<6)) {
    naive_aux(C,A,B,n);
    return;
  }
  Matrix *S[2];
//no more 10
 for (int i=0; i<2; i++) {
          S[i]=allocate_matrix(n/2, n/2);
       }
  Matrix *P[7];

  for (int i=0; i<7; i++) {
          P[i]=allocate_matrix(n/2, n/2);
       }
  //the multiplications are just considering at most 2 S_i matrixes at the time so we don't really need all 10 of them.

  // S1 = B12 - B22
  sub_matrix_blocks(S[0],0,0,B,B->f_row,B->f_col + n/2,B,B->f_row + n/2,B->f_col + n/2,n/2);
  // P1 = A11 x S1
  strassen_aux(P[0], 0, 0,A, A->f_row, A->f_col,S[0], 0, 0,n/2);
  // S2 = A11 + A12
  sum_matrix_blocks(S[0],0,0,A,A->f_row,A->f_col,A,A->f_row,A->f_col + n/2,n/2);
  // P2 = S2 x B22
  strassen_aux(P[1], 0, 0,S[0], 0, 0,B,  B->f_row + n/2, B->f_col + n/2,n/2);
  // S3 = A21 + A22
  sum_matrix_blocks(S[0],0,0,A,A->f_row + n/2,A->f_col,A,A->f_row + n/2,A->f_col + n/2,n/2);
  // P3 = S3 x B11
  strassen_aux(P[2], 0, 0,S[0], 0, 0,B, B->f_row, B->f_col,n/2);
  // S4 = B21 - B11
  sub_matrix_blocks(S[0],0,0,B,B->f_row + n/2,B->f_row,B,B->f_row, B->f_col,n/2);
  // P4 = A22 x S4
  strassen_aux(P[3], 0, 0,A, A->f_row + n/2, A->f_col + n/2,S[0], 0, 0,n/2);
  // S5 = A11 + A22
  sum_matrix_blocks(S[0],0,0,A,A->f_row,A->f_col,A,A->f_row + n/2,A->f_col + n/2,n/2);
  // S6 = B11 + B22
  sum_matrix_blocks(S[1],0,0,B,B->f_row,B->f_col,B,B->f_row + n/2,B->f_col + n/2,n/2);
  // P5 = S5 x S6
  strassen_aux(P[4], 0, 0,S[0], 0, 0,S[1], 0, 0,n/2);
  // S7 = A12 - A22 (there was a bug here A21 - A22)
  sub_matrix_blocks(S[0],0,0,A,A->f_row, A->f_col + n/2,A,A->f_row + n/2,A->f_col + n/2,n/2);
  // S8 = B21 + B22 (there was a bug here B21 - B22)
  sum_matrix_blocks(S[1],0,0,B,B->f_row + n/2, B->f_col,B,B->f_row + n/2,B->f_col + n/2,n/2);
  // P6 = S7 x S8
  strassen_aux(P[5], 0, 0,S[0], 0, 0,S[1], 0, 0,n/2);
  // S9 = A11 - A21
  sub_matrix_blocks(S[0],0,0,A,A->f_row,A->f_col,A,A->f_row + n/2,A->f_col,n/2);

  // S10 = B11 + B12
  sum_matrix_blocks(S[1],0,0,B,B->f_row,B->f_col,B,B->f_row,B->f_col + n/2,n/2);
  // P7 = S9 x S10
  strassen_aux(P[6], 0, 0,S[0], 0, 0,S[1], 0, 0,n/2);

// C11 = (P5 + P4) - P2 + P6
  sum_matrix_blocks(C, C->f_row, C->f_col,P[4], 0, 0,P[3], 0, 0,n/2);

  sub_matrix_blocks(C, C->f_row, C->f_col,C, C->f_row, C->f_col,P[1], 0, 0,n/2);

  sum_matrix_blocks(C, C->f_row, C->f_col,C,  C->f_row, C->f_col,P[5], 0, 0,n/2);

  // C12 = P1 + P2
  sum_matrix_blocks(C, C->f_row, C->f_col + n/2,P[0], 0, 0,P[1], 0, 0,n/2);

  // C21 = P3 + P4
  sum_matrix_blocks(C, C->f_row + n/2, C->f_col,P[2], 0, 0,P[3], 0, 0,n/2);

  // C22 = P5 + P1 - P3 - P7
  sum_matrix_blocks(C, C->f_row + n/2, C->f_col + n/2,P[4], 0, 0,P[0], 0, 0,n/2);

  sub_matrix_blocks(C, C->f_row + n/2, C->f_col + n/2,C, C->f_row + n/2, C->f_col + n/2,P[2], 0, 0,n/2);

  sub_matrix_blocks(C, C->f_row + n/2, C->f_col + n/2,C, C->f_row + n/2, C->f_col + n/2,P[6], 0, 0,n/2);


   for (int i=0; i<2; i++) {
         deallocate_matrix(S[i]);
       }

       for (int i=0; i<7; i++) {
         deallocate_matrix(P[i]);
       }
}

void strassen(Matrix *C,Matrix *A, Matrix *B, const size_t n)
{
  strassen_aux(C,C->f_row,C->f_col,A,A->f_row,A->f_col,B,B->f_row,B->f_col,n);
}
