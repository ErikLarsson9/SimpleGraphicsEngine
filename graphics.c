/* 
    Created by: Erik Larsson 19/1-2019
*/

#include "graphics.h"
#include "matrix.h"

double cubepoints[4][8] = {{1, 1,-1,-1, 1, 1,-1,-1},
                           {1,-1,-1, 1, 1,-1,-1, 1},
                           {-1, -1, -1, -1, 1, 1, 1, 1},
                           {1, 1, 1, 1, 1, 1, 1, 1}
                          };


double cubeadjpoints[8][8] = {{0,1,0,1,1,0,0,0},
                              {1,0,1,0,0,1,0,0},
                              {0,1,0,1,0,0,1,0},
                              {1,0,1,0,0,0,0,1},
                              {1,0,0,0,0,1,0,1},
                              {0,1,0,0,1,0,1,0},
                              {0,0,1,0,0,1,0,1},
                              {0,0,0,1,1,0,1,0}
                             };


void createcube(matrix *cube, matrix *adjacencymatrix){
            creatematrixfromarray(cube, 4, 8, cubepoints);
            creatematrixfromarray(adjacencymatrix, 8, 8, cubeadjpoints);           
}

void createtorus(double radius, int numt, int nums, matrix *torus, matrix *adjacencymatrix){
            
            initializematrix(torus, 4, nums*numt);        
            initializematrix(adjacencymatrix, nums*numt, nums*numt);


            for(int t = 0; t < numt; t++){
                for(int s = 0; s < nums; s++){
                    int pointnumber = t * nums + s;
                    
  
                    double modulot = t % numt;
                    double modulos = s % nums;
                    double tradian = (double) (2 *modulot * M_PI)/ (double) numt;
                    double sradian = (double) (2 *modulos * M_PI)/ (double) nums;                   

                    torus->matrix[0][pointnumber] = radius*cos(tradian) + cos(sradian)*cos(tradian);
                    torus->matrix[1][pointnumber] = radius*sin(tradian) +sin(tradian)*cos(sradian);
                    torus->matrix[2][pointnumber] = sin(sradian);
                    torus->matrix[3][pointnumber] = 1;
                    //If's to avoid marking a point with itself in adjacency matrix
                    if((t+1)%numt != t){
                        adjacencymatrix->matrix[pointnumber][((t+1)%numt)*nums+s] = 1;

                    }
                    //t-1+numt, plus numt is to avoid negative number which isn't handled properly by c modulo
                    if((t-1+numt)%numt != t){
                         //printf("t: %d, numt: %d, (t-1) mod%%numt: %d\n", t, numt,(t-1+numt)%numt);
                         adjacencymatrix->matrix[pointnumber][((t-1+numt)%numt)*nums+s] = 1;

                    }
                    if((s+1)%nums != s){
                        adjacencymatrix->matrix[pointnumber][t*nums+(s+1)%nums] = 1;

                    }
                    if((s-1+nums)%nums != s){
                        
                            adjacencymatrix->matrix[pointnumber][t*nums+(s-1+nums)%nums] = 1;
                    }

                    
                 }
            }
            

}


//void translation(matrix *mat, matrix *translated, double h, double k, double l)
void translation(matrix *mat, double h, double k, double l){
    matrix *translation = malloc(sizeof(matrix));
    translation->rows = 4;
    translation->col = 4;
    translation->matrix = malloc(sizeof(double *)*translation->rows);
    for(int i = 0; i<translation->rows; i++){
        translation->matrix[i] = malloc(sizeof(double)*translation->col); 
    }
    for(int i = 0; i<translation->rows; i++){
        for(int j = 0; j<translation->col; j++){
            if(i == j){
                translation->matrix[i][j] = 1;
            }
            else{ 
                translation->matrix[i][j] = 0;
            }
        }
    }

    translation->matrix[0][3] = h;
    translation->matrix[1][3] = k;
    translation->matrix[2][3] = l;
    matrix *translated = malloc(sizeof(matrix));
    matrixmult(translation, mat, translated);
    freematrix(mat);
    mat->rows = translated->rows;
    mat->col = translated->col;
    mat->matrix = translated->matrix;
    free(translated);
    freematrix(translation);
    free(translation);
    




}

void scalexyz(matrix *mat, double scalingfactor){
    for(int i = 0; i<mat->rows -1; i++){
        for(int j = 0; j<mat->col; j++){
            mat->matrix[i][j] = scalingfactor*mat->matrix[i][j];
        }

    }

}

void projectpoints(matrix* mat, matrix *projectedmat, double b, double c, double d){
    matrix * projectionmatrix = malloc(sizeof(matrix));
    projectionmatrix->rows = 4;
    projectionmatrix->col = 4;
    projectionmatrix->matrix = malloc(sizeof(double *)*projectionmatrix->rows);
    for(int i = 0; i<projectionmatrix->rows; i++){
        projectionmatrix->matrix[i] = malloc(sizeof(double)*projectionmatrix->col);
    }
    projectionmatrix->matrix[0][0] = 1;
    projectionmatrix->matrix[0][1] = 0;
    projectionmatrix->matrix[0][2] = -b/d;
    projectionmatrix->matrix[0][3] = 0;
    projectionmatrix->matrix[1][0] = 0;
    projectionmatrix->matrix[1][1] = 1;
    projectionmatrix->matrix[1][2] = -c/d;
    projectionmatrix->matrix[1][3] = 0;
    projectionmatrix->matrix[2][0] = 0;
    projectionmatrix->matrix[2][1] = 0;
    projectionmatrix->matrix[2][2] = 0;
    projectionmatrix->matrix[2][3] = 0;
    projectionmatrix->matrix[3][0] = 0;
    projectionmatrix->matrix[3][1] = 0;
    projectionmatrix->matrix[3][2] = -1/d;
    projectionmatrix->matrix[3][3] = 1;


 
    matrixmult(projectionmatrix, mat, projectedmat);
    freematrix(projectionmatrix);
    free(projectionmatrix);


}

void projectionpoints2d(matrix *projectionpoints, matrix *projectionpointsxy){
    projectionpointsxy->rows = 2;
    projectionpointsxy->col = projectionpoints->col;
    projectionpointsxy->matrix = malloc(sizeof(double*)*projectionpointsxy->rows);
    for(int i = 0; i<projectionpointsxy->rows; i++){
        projectionpointsxy->matrix[i] = malloc(sizeof(double)*projectionpointsxy->col); 
    }
    for(int i = 0; i<projectionpointsxy->rows; i++){
        for(int j = 0; j <projectionpointsxy->col; j++){
           projectionpointsxy->matrix[i][j] = projectionpoints->matrix[i][j];
           //scale points? /projectionpoints->matrix[3][j];
        }

    }

}

//void rotate(matrix *mat, matrix *rotmat, double rotx, double roty, double rotz){
void rotate(matrix *mat, double rotx, double roty, double rotz){
    matrix *xrotationmatrix = malloc(sizeof(matrix));
    initializematrix(xrotationmatrix, 4, 4);
   
    xrotationmatrix->matrix[0][0] = 1;
    xrotationmatrix->matrix[0][1] = 0;
    xrotationmatrix->matrix[0][2] = 0;
    xrotationmatrix->matrix[0][3] = 0;
    xrotationmatrix->matrix[1][0] = 0;
    xrotationmatrix->matrix[1][1] = cos(rotx);
    xrotationmatrix->matrix[1][2] = -sin(rotx);
    xrotationmatrix->matrix[1][3] = 0;
    xrotationmatrix->matrix[2][0] = 0;
    xrotationmatrix->matrix[2][1] = sin(rotx);
    xrotationmatrix->matrix[2][2] = cos(rotx);
    xrotationmatrix->matrix[2][3] = 0;
    xrotationmatrix->matrix[3][0] = 0;
    xrotationmatrix->matrix[3][1] = 0;
    xrotationmatrix->matrix[3][2] = 0;
    xrotationmatrix->matrix[3][3] = 1;

    matrix *rotmat = malloc(sizeof(matrix));

    matrixmult(xrotationmatrix, mat, rotmat);
    freematrix(mat);

    mat->rows = rotmat->rows;
    mat->col = rotmat->col;
    mat->matrix = rotmat->matrix;
    free(rotmat);
    //printf("rows: %d, col: %d\n", mat->rows, mat->col);
    //printf("mat: %f\n", mat->matrix[0][0]);
    freematrix(xrotationmatrix);
    free(xrotationmatrix);




}

