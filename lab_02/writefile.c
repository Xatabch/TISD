#include <stdio.h>

void write_file(int delete)
{
  FILE *f_in;
  FILE *f_out;
  char str[200];
  int i;

  f_in = fopen("in.txt","w");
  f_out = fopen("out.txt","r");

  i = 0;
  //считал строку
  if(fgets(str,sizeof(str),f_out))
  {
    if((i+1) != delete)
      fprintf(f_in, "%s", str);
    i++;
    while(fgets(str,sizeof(str),f_out))
    {
      if((i+1) != delete)
        fprintf(f_in, "%s", str);
      i++;
    }
  }
  fclose(f_in);
  fclose(f_out);
}
