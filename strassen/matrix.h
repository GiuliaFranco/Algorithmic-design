#ifndef __MATRIX__
#define __MATRIX__


struct matrix{
	int rows; // number of rows
	int cols; // number of columns
	float **data; // a pointer to an array of n_rows pointers to rows
	int f_row; // element in the  top left corner: set to zero as default.
        int f_col;
};
typedef struct matrix Matrix;

int naive_matrix_mult( Matrix *C, Matrix  *A,  Matrix  *B,int n);

Matrix* allocate_matrix(int rows,int cols);

void deallocate_matrix(Matrix *A);

int same_matrix(Matrix *A,Matrix *B);

#endif // __MATRIX__
