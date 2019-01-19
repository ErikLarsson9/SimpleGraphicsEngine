/* 
    Created by: Erik Larsson 19/1-2019
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "matrix.h"
#ifndef _GRAPHICS
#define _GRAPHICS
void createtorus(double radius, int numt, int nums, matrix *torus, matrix *adjacencymatrix);
//void translation(matrix *mat, matrix *translated, double h, double k, double l);
void translation(matrix *mat, double h, double k, double l);
void scalexyz(matrix *mat, double scalingfactor);
void projectpoints(matrix* mat, matrix *projectedmat, double b, double c, double d);


void projectionpoints2d(matrix *projectionpoints, matrix *projectionpointsxy);
//void rotate(matrix *mat, matrix *rotmat, double rotx, double roty, double rotz);
void rotate(matrix *mat, double rotx, double roty, double rotz);
void createcube(matrix *cube, matrix *adjacencymatrix);


#endif