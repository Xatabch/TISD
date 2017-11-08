#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define UNCORRECT_SYMBOL -1;
#define OK 0;

struct colIndex {
  int Nk; //номера компонент с которых начинается описание столбца

  struct colIndex *next;
};

struct cscMatrix {
  int N;  //размер матрицы (N x N)
  int NZ; //количество ненулевых элементов

  //Массив значений (размер NZ)
  double *Value;
  //Массив номеров строк (Размер NZ)
  int *Row;
  //Массив индексов столбцов (размер N + 1)
  struct colIndex *colindex;
};

struct colIndex* add_end(struct colIndex *head, 
                                   struct colIndex *nk)
{
    struct colIndex *cur = head;

    if (!head)
        return nk;

    for ( ; cur->next; cur = cur->next)
        ;

    cur->next = nk;

    return head;
}

void push(struct colIndex **head, int data) {
  struct colIndex *tmp = malloc(sizeof(struct colIndex));
  tmp->Nk = data;
  tmp->next = (*head);
  (*head) = tmp;
}

int pop(struct colIndex **head) {
    struct colIndex* prev = NULL;
    int val;
    if (head == NULL) {
        exit(-1);
    }
    prev = (*head);
    val = prev->Nk;
    (*head) = (*head)->next;
    free(prev);
    return val;
}

struct cscMatrix *get_array_from_keyboard(int n,int m)
{
  FILE *f;
  int i = 0;
  int c;
  double num;
  struct cscMatrix *Matrix = malloc(sizeof(struct cscMatrix));
  Matrix->NZ = 0;
  Matrix->N = 0;

  f = fopen("in.txt","w");

  c = getchar();

  for(i = 0; i< n; i++)
  {
    printf("Введите элементы %d-й строки через пробел: ",(i+1));
    while((c = getchar()) != '\n')
    {
      fprintf(f, "%c", c);
      if((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
      {
        printf("Вы ввели некорректный символы\n");
        return NULL;
      }
    }
    fprintf(f, "\r\n");
  }

  fclose(f);

  f = fopen("in.txt","r");
  if(!f)
  {
    printf("Ошибка файла\n");
    return NULL;
  }
  else
  {
    if(fscanf(f,"%lf",&num) == 1)
    {
      if(num != 0)
      {
        Matrix->NZ++;
      }
      while(fscanf(f,"%lf",&num) == 1)
        if(num != 0)
        {
          Matrix->NZ++;
        }
    }
  }

  fclose(f);

  Matrix->Value = malloc(Matrix->NZ * sizeof(double));
  i = 0;
  f = fopen("in.txt","r");
  if(!f)
  {
    printf("Ошибка файла\n");
    return NULL;
  }
  else
  {
    if(fscanf(f,"%lf",&num) == 1)
    {
      Matrix->N++;

      if(num != 0)
      {
        Matrix->Value[i] = num;
        i++;
      }
      while(fscanf(f,"%lf",&num) == 1)
      {
        Matrix->N++;

        if(num != 0)
        {
          Matrix->Value[i] = num;
          i++;
        }
      }
    }
  }
  fclose(f);

  if(Matrix->N != n * m)
  {
    printf("Неверное количество элементов\n");
    return NULL;
  }

  return Matrix;

  free(Matrix->Value);
  free(Matrix);
}

struct cscMatrix *get_ia(int m,struct cscMatrix *Matrix)
{
  FILE *f;
  int fill_rows = 0;;
  double num;
  int waddap = 0;
  int i = 0;
  Matrix->Row = malloc(Matrix->NZ * sizeof(int));

  f = fopen("in.txt","r");
  if(!f)
    return NULL;
  else
  {
    if(fscanf(f,"%lf",&num) == 1)
    {
      if(num != 0)
      {
        Matrix->Row[i] = waddap;
        i++;
      }

      fill_rows++;
      if(fill_rows == m)
      {
        waddap++;
        fill_rows = 0;
      }
      while(fscanf(f,"%lf",&num) == 1)
      {
        if(num != 0)
        {
          Matrix->Row[i] = waddap;
          i++;
        }

        fill_rows++;
        if(fill_rows >= m)
        {
          waddap++;
          fill_rows = 0;
        }
      }
    }
  }
  fclose(f);

  return Matrix;
  free(Matrix->Row);
}

struct cscMatrix *get_ja(int n, int m,struct cscMatrix *Matrix)
{
  int i = 0;
  int j = 0;

  FILE *f;
  double num;

  struct colIndex *head = NULL;
  double *matrix = malloc(Matrix->N * sizeof(double));

  f = fopen("in.txt","r");
  if(!f)
  {
    printf("Ошибка файла\n");
    return NULL;
  }
  else
  {
    if(fscanf(f,"%lf",&num) == 1)
    {
      matrix[i] = num;
      i++;
      while(fscanf(f,"%lf",&num) == 1)
      {
        matrix[i] = num;
        i++;
      }
    }
  }
  fclose(f);

  int *ia = calloc(m+1,sizeof(int));

  for(i = 0; i < m+1; i++)
    ia[i] = 0;

  ia[0] = Matrix->NZ + 1;

  j = 1;
  int c_n_z = Matrix->NZ;
  i = (n * m) - 1;
  while(i >= 0)
  {
    if(j == m + 1)
      j = 1;
    if(matrix[i] != 0)
    {
      ia[j] = c_n_z;
      c_n_z--;
    }
    j++;
    i--;
  }

  for(i = 0; i < m+1; i++)
  {
    if(ia[i] == 0)
    {
      ia[i] = ia[i-1];
    }
  }

  for(i = 0; i < m + 1; i++)
    push(&head,ia[i]);

  Matrix->colindex = malloc(sizeof(struct colIndex));
  Matrix->colindex = head;

  return Matrix;

  free(matrix);
  free(ia);
  free(head);

}

int main(void)
{
  int n = 0;
  int n1 = 0;
  int m = 0;

  struct cscMatrix *matrix;
  struct cscMatrix *vector_matrix;

  printf("Введите количество строк: ");
  scanf("%d",&n);
  if(n > 0)
  {
    printf("Введите количество столбцов: ");
    scanf("%d",&m);
    if(m > 0)
    {
      matrix = get_array_from_keyboard(n, m);
      if(matrix)
      {
        matrix = get_ia(m,matrix);
        printf("A: ");
        for(int i = 0; i < matrix->NZ;i++)
          printf("%f ", matrix->Value[i]);
        printf("\n");
        printf("N: %d\n",matrix->N);
        printf("NZ: %d\n",matrix->NZ);
        printf("IA: ");
        for(int i = 0; i < matrix->NZ;i++)
          printf("%d ", matrix->Row[i]+1);
        printf("\n");
        matrix = get_ja(n, m, matrix);
        for(  ;matrix->colindex; matrix->colindex = matrix->colindex->next)
          printf("%d\n", matrix->colindex->Nk);
      }

      printf("\n");

      printf("Введите количество строк для вектора-столбца: ");
      scanf("%d", &n1);
      if(n1 > 0)
      {
        vector_matrix = get_array_from_keyboard(n1, 1);
        if(vector_matrix)
        {
        vector_matrix = get_ia(1,vector_matrix);
        printf("B: ");
        for(int i = 0; i < vector_matrix->NZ;i++)
          printf("%f ", vector_matrix->Value[i]);
        printf("\n");
        printf("N: %d\n",vector_matrix->N);
        printf("NZ: %d\n",vector_matrix->NZ);
        printf("IB: ");
        for(int i = 0; i < vector_matrix->NZ;i++)
          printf("%d ", vector_matrix->Row[i]+1);
        printf("\n");
        vector_matrix = get_ja(n1, 1, vector_matrix);
        for(  ;vector_matrix->colindex; vector_matrix->colindex = vector_matrix->colindex->next)
          printf("%d\n", vector_matrix->colindex->Nk);
        }
      }
    }
    else
      printf("Некорректное количество столбцов\n");
  }
  else
    printf("Некорректное количество строк\n");

}