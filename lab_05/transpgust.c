#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pushpop.h"

struct cscMatrix *transpgust(int m,struct cscMatrix *Matrix, int *LJ)
{
	int i = 0;
	int j = 0;
	int S = 0;
    int tmp = 0;
    int j1 = 0;
    int j2 = 0;
    int Col = 0;
    double V = 0;
    int RIndex = 0;
    int IIndex = 0;

	int *LJT = malloc((m+1) * sizeof(int));
    struct cscMatrix *matrixT = malloc(sizeof(struct cscMatrix));
    struct colIndex *head = NULL;
    matrixT->Value = malloc(Matrix->NZ * sizeof(double));
    matrixT->Row = malloc(Matrix->NZ * sizeof(int));
    matrixT->NZ = Matrix->NZ;

    memset(LJT, 0, (m+1) * sizeof(int));
    for(i = 0; i < Matrix->NZ; i++)
    	LJT[Matrix->Row[i] + 1]++;

    for(i = 1; i <= m+1; i++)
    {
    	tmp = LJT[i];
        LJT[i] = S;
        S = S + tmp;
    }

    for(i = 0; i < m; i++)
    {
    	j1 = LJ[i] ; j2 = LJ[i+1];
        Col = i;
        for(j = j1; j < j2; j++)
        {
           V = Matrix->Value[j];
           RIndex = Matrix->Row[j];
           IIndex = LJT[RIndex + 1];
           matrixT->Value[IIndex] = V;
           matrixT->Row[IIndex] = Col;
           LJT[RIndex + 1]++;
        }
    }

    for(i = m; i >= 0; i--)
    	push(&head,(LJT[i] + 1));

  	matrixT->colindex = malloc(sizeof(struct colIndex));
  	matrixT->colindex = head;

    return matrixT;
}