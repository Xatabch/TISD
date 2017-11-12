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
        Matrix->Row[i] = waddap + 1;
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
          Matrix->Row[i] = waddap + 1;
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
      ia[i] = ia[i-1];
  }
  for(i = 0; i < m+1; i++)
    ia[i] -= 1;

  for(i = 0; i < m + 1; i++)
    push(&head,(ia[i] + 1));

  Matrix->colindex = malloc(sizeof(struct colIndex));
  Matrix->colindex = head;

  return Matrix;

  free(matrix);
  free(ia);
  free(head);

}

struct cscMatrix *transponse(int m, int n, struct cscMatrix *Matrix)
{
  FILE *f;
  int i = 0;
  int j = 0;
  int check = 0;
  double num;
  int str_count = 0;//определяет к какой строке принадлежит транспонированная матрица

  struct cscMatrix *TMatrix = malloc(sizeof(struct cscMatrix));
  TMatrix->N = Matrix->N;
  TMatrix->NZ = Matrix->NZ;
  TMatrix->Value = malloc(TMatrix->NZ * sizeof(double));
  TMatrix->Row = malloc(TMatrix->NZ * sizeof(int));
  int *ia = calloc((n+1), sizeof(int));
  struct colIndex *head = NULL;

  f = fopen("in.txt","r");
  if(!f)
  {
    printf("Ошибка открытия файла\n");
    return NULL;
  }
  else
  {
    if(fscanf(f, "%lf", &num) == 1)
    {

      if(num != 0)
      {
        TMatrix->Value[i] = num;
        TMatrix->Row[i] = str_count + 1;
        i++;
      }

      if(num != 0 && check == 0)
      {
        ia[j] = i;
        check = 1;
      }

      str_count++;

      if(str_count == m)
      {
        str_count = 0;
        j++;
        check = 0;
      }

      while(fscanf(f, "%lf", &num) == 1)
      {

        if(num != 0)
        {
          TMatrix->Value[i] = num;
          TMatrix->Row[i] = str_count + 1;
          i++;
        }

        if(num != 0 && check == 0)
        {
          ia[j] = i;
          check = 1;
        }

        str_count++;

        if(str_count == m)
        {
          str_count = 0;
          j++;
          check = 0;
        }
      }
    }

    ia[n] = TMatrix->NZ;

    /*for(i = 0; i < (n+1); i++)
      printf("[%d] ", ia[i]);*/

    for(i = n+1; i >= 0; i--)
    {
      if(ia[i] == 0)
        ia[i] = ia[i+1];
    }

    for(i = 0; i < n; i++)
      ia[i] = ia[i] - 1;

    for(i = n; i >= 0; i--)
      push(&head,(ia[i] + 1));

    TMatrix->colindex = malloc(sizeof(struct colIndex));
    TMatrix->colindex = head;
  }

  return TMatrix;

}

int *make_ip(int tmp1, int tmp2, int m, int *j)
{
  int *IP = calloc(m, sizeof(int));
  int i = 0;
  int k = 1;

  if(!IP)
    return NULL;
  else
  {
    for(i = tmp1; i < tmp2; i++)
    {
      IP[j[i] - 1] = k;
      k++;
    }
  }

  return IP;

  free(IP);

}

struct cscMatrix *multiply(int n, int m, struct cscMatrix *Matrix, struct cscMatrix *vector_matrix)
{
  int tmp1 = pop(&Matrix->colindex);
  int tmp2;
  int i = 0;
  int j = 0;
  int k = 0;
  int *IP;
  struct cscMatrix *Result = malloc(sizeof(struct cscMatrix));
  double *val = calloc(n, sizeof(double));
  double h = 0;
  struct colIndex *head = NULL;

  Result->NZ = 0;
  Result->N = n;
  IP = make_ip(0, vector_matrix->NZ, m, vector_matrix->Row);
  if(!IP)
  {
    printf("Error alloc memory\n");
    return NULL;
  }

  for(i = 0; i < n; i++)
  {
    tmp2 = pop(&Matrix->colindex);

    if(tmp1 != tmp2)
    {
      //printf("TMP1: %d\tTMP2: %d\n",tmp1,tmp2);
      //IP = make_ip((tmp1 - 1), (tmp2 - 1), m, Matrix->Row);
      /*for(int k = 0; k < m; k++)
        printf("%d ", IP[k]);*/
      //printf("\n");
      for(j = (tmp1 - 1); j < (tmp2 - 1); j++)
      {
        //printf("2MULT: %lf\n",Matrix->Value[j]);
        //printf("TRY: %d ", IP[Matrix->Row[j] - 1]);
        //printf("1MULT: %lf\n", vector_matrix->Value[IP[Matrix->Row[j] - 1]-1]);
        if(IP[Matrix->Row[j] - 1] > 0)
          h += vector_matrix->Value[IP[Matrix->Row[j] - 1]-1] * Matrix->Value[j];
      }
      //printf("\n");
      if(h > 0)
        Result->NZ++;
      //printf("\n%lf\n", h);
    }
    val[i] = h;
    h = 0;
    tmp1 = tmp2;
  }

  Result->Row = malloc(Result->NZ * sizeof(int));
  for (i = 0; i < n; i++)
  {
    if(val[i] != 0)
    {
      Result->Row[k] = i+1;
      k++;
    }
  }

  k = 0;
  Result->Value = malloc(Result->NZ * sizeof(double));
  for(i = 0; i < n; i++)
  {
    if(val[i] != 0)
    {
      Result->Value[k] = val[i];
      k++;
    }
  }
  /*printf("\n");
  printf("VAL: ");
  for (i = 0; i < n; i++)
    printf("%lf ", val[i]);
  printf("\nROW: ");
  for(i = 0; i < k; i++)
    printf("%d ", Result->Row[i]);*/
  push(&head,(Result->NZ+1));
  push(&head,Result->Row[0]);
  Result->colindex = malloc(sizeof(struct colIndex));
  Result->colindex = head;

  return Result;
}

int main(void)
{
  int n = 0;
  int n1 = 0;
  int m = 0;

  struct cscMatrix *matrix;
  struct cscMatrix *vector_matrix;
  struct cscMatrix *TMatrix;
  struct cscMatrix *Mult1;

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
        /*printf("A: ");
        for(int i = 0; i < matrix->NZ;i++)
          printf("%f ", matrix->Value[i]);
        printf("\n");
        printf("N: %d\n",matrix->N);
        printf("NZ: %d\n",matrix->NZ);
        printf("IA: ");
        for(int i = 0; i < matrix->NZ;i++)
          printf("%d ", matrix->Row[i]);
        printf("\n");
        matrix = get_ja(n, m, matrix);*/
        /*printf("JA: ");
        for(  ;matrix->colindex; matrix->colindex = matrix->colindex->next)
          printf("%d ", matrix->colindex->Nk);*/
        //printf("\n");

        TMatrix = transponse(m,n,matrix);
        if(TMatrix)
        {
          /*printf("\nTMatrix A: ");
          for(int i = 0; i < TMatrix->NZ;i++)
            printf("%f ", TMatrix->Value[i]);
          printf("\nTMatrix IA: ");
          for(int i = 0; i < TMatrix->NZ;i++)
            printf("%d ", TMatrix->Row[i]);*/
          /*printf("\nTMatrix JA: ");
          for(  ;TMatrix->colindex; TMatrix->colindex = TMatrix->colindex->next)
            printf("%d ", TMatrix->colindex->Nk);*/
        }
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
          /*printf("B: ");
          for(int i = 0; i < vector_matrix->NZ;i++)
            printf("%f ", vector_matrix->Value[i]);
          printf("\n");
          printf("N: %d\n",vector_matrix->N);
          printf("NZ: %d\n",vector_matrix->NZ);
          printf("IB: ");
          for(int i = 0; i < vector_matrix->NZ;i++)
            printf("%d ", vector_matrix->Row[i]);
          printf("\n");
          vector_matrix = get_ja(n1, 1, vector_matrix);*/
          /*printf("JB: ");
          for(  ;vector_matrix->colindex; vector_matrix->colindex = vector_matrix->colindex->next)
            printf("%d ", vector_matrix->colindex->Nk);*/

          printf("\n");

          Mult1 = multiply(n, m, TMatrix, vector_matrix);
          if(Mult1)
          {
            printf("Mult1: ");
            for(int i = 0; i < Mult1->NZ;i++)
              printf("%f ", Mult1->Value[i]);
            printf("\n");
            printf("N: %d\n",Mult1->N);
            printf("NZ: %d\n",Mult1->NZ);
            printf("IM: ");
            for(int i = 0; i < Mult1->NZ;i++)
              printf("%d ", Mult1->Row[i]);
            printf("\n");
            printf("JM: ");
            for(  ;Mult1->colindex; Mult1->colindex = Mult1->colindex->next)
              printf("%d ", Mult1->colindex->Nk);
          }


        }
      }
    }
    else
      printf("Некорректное количество столбцов\n");
  }
  else
    printf("Некорректное количество строк\n");

}