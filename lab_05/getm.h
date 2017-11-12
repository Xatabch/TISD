//get_matrix
#ifndef __GETM_H__
#define __GETM_H__
double ** get_matrix(FILE *f,double ** (*alloc)(int,int),int n, int m);
#endif