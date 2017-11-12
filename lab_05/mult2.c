#include <stdio.h>
#include <stdlib.h>

double ** mult(double ** (*alloc)(int,int),double ** matrix1,double ** matrix2,int n1,int m1,int n2, int m2)
{
  double ** matrix;
  matrix = alloc(n1,m2);

  for(int i = 0; i < n1;i++)
  {
    for(int j = 0; j < m2;j++)
    {
      matrix[i][j] = 0;
      for(int k = 0; k < n2; k++)
        matrix[i][j] += matrix1[i][k] * matrix2[k][j];
    }
  }

  return matrix;

}