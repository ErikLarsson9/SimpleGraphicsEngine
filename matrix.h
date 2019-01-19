/* 
    Created by: Erik Larsson 19/1-2019
*/
#include <stdlib.h>
#include <stdio.h>


#ifndef _MATRIX
#define _MATRIX

typedef struct matrix{
    int rows;
    int col;
    double **matrix;

} matrix;

//typedef double **matrix;

//typedef double *vector;


matrix creatematrixfromstring(char matrixstring[]);

void creatematrixfromarray(matrix *mat, int rows, int col, double array[rows][col]);

void initializematrix(matrix *mat, int rows, int col);


void matrixmult(matrix *a, matrix *b, matrix *c);

void printmatrix(matrix a); 

void freematrix(matrix *mat);

#endif
//double dotproduct(vector a, vector b);


