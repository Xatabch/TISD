//get_matrix_from_file
#ifndef __GETFILEARR_H__
#define __GETFILEARR_H__
double ** get_matrix_from_file(FILE *f,double ** (*alloc)(int,int), int n, int m);
#endif