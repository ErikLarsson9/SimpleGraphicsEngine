/* 
    Created by: Erik Larsson 19/1-2019
    Contains Boilerplate  code for X11 provided by Brian Hammond 2/9/96 
    
*/
    



/* Boilerplate code for X11 provided by Brian Hammond 2/9/96 */
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <stdio.h>
#include <stdlib.h>


/* Erik Larsson 19/1-2019 */
#include <math.h>
#include "matrix.h"
#include "graphics.h"
#include <unistd.h>


/* Boilerplate code for X11 provided by Brian Hammond 2/9/96 */
Display *dis;
int screen;
Window win;
GC gc;

/* Boilerplate code for X11 provided by Brian Hammond 2/9/96 */
void init_x();
void close_x();
void redraw();

/* Erik Larsson 19/1-2019 */
int main () {

	init_x();

    
	while(1) {		

        redraw();
        XFlush(dis);
        usleep(1000000/10);
	}
}

/* Boilerplate code for X11 provided by Brian Hammond 2/9/96 */
void init_x() {
/* get the colors black and white (see section for details) */        
	unsigned long black,white;

	dis=XOpenDisplay((char *)0);
   	screen=DefaultScreen(dis);
	black=BlackPixel(dis,screen),
	white=WhitePixel(dis, screen);
   	win=XCreateSimpleWindow(dis,DefaultRootWindow(dis),0,0,	
		900, 900, 5,black, white);
	XSetStandardProperties(dis,win,"Graphics Engine","",None,NULL,0,NULL);
	XSelectInput(dis, win, ExposureMask|ButtonPressMask|KeyPressMask);
        gc=XCreateGC(dis, win, 0,0);        
	XSetBackground(dis,gc,white);
	XSetForeground(dis,gc,black);
	XClearWindow(dis, win);
	XMapRaised(dis, win);
};

/* Boilerplate code for X11 provided by Brian Hammond 2/9/96 */
void close_x() {
	XFreeGC(dis, gc);
	XDestroyWindow(dis,win);
	XCloseDisplay(dis);	
	exit(1);				
};

/* Erik Larsson 19/1-2019 */
void drawpoints(matrix *mat, matrix *adj){
    double offset = 200;
    // for(int i = 0; i<mat->col; i++){
    //     printf("x: %f, y: %f\n",mat->matrix[0][i], mat->matrix[1][i]);
    //     XDrawPoint(dis, win, gc, mat->matrix[0][i]+offset , offset - mat->matrix[1][i]);
    // }
    for(int i = 0; i<adj->rows; i++){
        for(int j = 0; j<adj->col; j++){
            if(adj->matrix[i][j] == 1){
            XDrawLine(dis, win, gc, mat->matrix[0][i]+offset, offset - mat->matrix[1][i],
            mat->matrix[0][j]+offset , offset - mat->matrix[1][j]);
                
            }
            
        }
    }
    

}

/* Erik Larsson 19/1-2019 */
void redraw() {
    static int counter = 0;
    int countermax = 60;
	XClearWindow(dis, win);
    matrix *torus = malloc(sizeof(matrix));
    matrix *adjacencymatrix = malloc(sizeof(matrix));
    createtorus(3.0, 20, 20, torus, adjacencymatrix);
    //createcube(torus, adjacencymatrix);
    double offset = 200;
    //matrix *translatedmatrix = malloc(sizeof(matrix));
    //translation(torus, translatedmatrix, offset, offset, 0);
    double scalingfactor = 10;
    scalexyz(torus, scalingfactor);
    //matrix *rottorus = malloc(sizeof(matrix));
    double radian = (double) (2 * M_PI* counter)/ (double) countermax;
    //rotate(torus, rottorus, radian,  0, 0);
    rotate(torus, radian,  0, 0);
    
    matrix *projectedtorus = malloc(sizeof(matrix));
    //projectpoints(rottorus, projectedtorus, 0, 0, -1);
    projectpoints(torus, projectedtorus, 0, 0, -1);
    freematrix(torus);
    free(torus);

    matrix *pp2d = malloc(sizeof(matrix));
    projectionpoints2d(projectedtorus, pp2d);
    freematrix(projectedtorus);
    free(projectedtorus);
    drawpoints(pp2d, adjacencymatrix);
    freematrix(pp2d);
    free(pp2d);
    freematrix(adjacencymatrix);
    free(adjacencymatrix);

    counter = (counter + 1) % countermax; 





   
};