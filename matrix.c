/* 
    Created by: Erik Larsson 19/1-2019
*/
#include "matrix.h"

void matrixmult(matrix *a, matrix *b, matrix *c){

        int matarows = a->rows;
        int matacol = a->col;
        int matbrows = b->rows;
        int matbcol = b->col;

    
        if(matacol != matbrows){
            printf("The number of columns of the first matrix doesn't match with the number of columns of the second matrix\n");
                
        }
        int matcrows = matarows;
        int matccol = matbcol;
        c->matrix = malloc(sizeof(double*)*matcrows);
        c->rows = matcrows;
        c->col = matccol;
        for(int i = 0; i<matcrows; i++){
           c->matrix[i] = malloc(sizeof(double)*matccol);
        }
        for(int i = 0; i<matcrows; i++){

            for(int j = 0; j<matccol; j++){
                double element = 0;
                for(int k = 0; k<matbrows; k++){
                    element = element + a->matrix[i][k]*b->matrix[k][j];
                }
                c->matrix[i][j] = element;


            }
        }
        




}

void printmatrix(matrix a){
    //printf("size a: %d", (int) sizeof(double));
    int rows = a.rows;
    int col = a.col;
    printf("Number of rows: %d\n", rows);
    printf("Number of columns: %d\n\n", col); 
    
    for(int i = 0; i<rows; i++){
        printf("[ ");
        for(int j = 0; j<col; j++){
            printf("%f ",a.matrix[i][j]);
        }
        printf("]\n");
    }


}



//
matrix creatematrixfromstring(char matrixstring[]){


}

void creatematrixfromarray(matrix *mat, int rows, int col, double array[rows][col]){
    mat->rows = rows;
    mat->col = col;
    mat->matrix = malloc(sizeof(double)*rows);
    for(int i = 0; i<rows; i++){
        mat->matrix[i] = malloc(sizeof(double)*col);
        for(int j = 0; j<col; j++){
            mat->matrix[i][j] = array[i][j];
             
        }

    }

}

void initializematrix(matrix *mat, int rows, int col){
    mat->rows = rows;
    mat->col = col; 
    mat->matrix = malloc(sizeof(double *)*mat->rows);
        for(int i = 0; i<mat->rows; i++){
            mat->matrix[i] = malloc(sizeof(double)*mat->col);
            for(int j = 0; j<mat->col; j++){
                mat->matrix[i][j] = 0; 
            }
        }
}
//free matrix datastructures 
void freematrix(matrix *mat){
    for(int i = 0; i<mat->rows; i++){
        free(mat->matrix[i]);
    }
    free(mat->matrix);

    //free(mat);
}



