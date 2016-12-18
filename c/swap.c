#include <stdio.h>

void __swap(int a,int b)
{
  int c = b;
  *(&b) = a;
  *(&a) = c;
}

int main()
{
  int a=1,b=9;
  __swap(a,b);
  printf("a = %d;b = %d\n",a,b);
}
