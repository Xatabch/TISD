#include <stdio.h>

void read_line(char *s,int n)
{
  int ch,i = 0;
  while((ch = getchar()) != '\n' && ch != EOF)
    if(i < n - 1)
      s[i++] = ch;
  s[i] = '\0';
}