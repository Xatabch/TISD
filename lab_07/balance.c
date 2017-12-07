#include <stdio.h>

#include "main.h"
#include "rotateright.h"//// правый поворот вокруг p
#include "rotateleft.h"// левый поворот вокруг q
#include "helpfunc.h"//вспомогательные функции для построения авл деревьев

tree *balance(tree *p)
{
  fixheight(p);
  if(bfactor(p) >= 2)
  {
    printf("left\n");
    if(bfactor(p->right) < 0)
      p->right = rotateright(p->right);

    return rotateleft(p);
  }
   if(bfactor(p) <= -2)
   {
    printf("right\n");
     if(bfactor(p->left) > 0)
        p->left = rotateleft(p->left);

     return rotateright(p);

   }

  return p;
}