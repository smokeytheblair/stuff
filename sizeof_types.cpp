#include <stdio.h>
#include <type_traits>

int main ()
{
  printf("pointer is %ld bytes\n", sizeof(void*));
  printf("std::nullptr_t is %ld bytes\n", sizeof(std::nullptr_t));
  printf("float is %ld bytes\n", sizeof(float));
  printf("double is %ld bytes\n", sizeof(double));
  printf("long long is %ld byte\n", sizeof(long long));
  printf("long is %ld bytes\n", sizeof(long));
  printf("int is %ld bytes\n", sizeof(int));
  printf("short is %ld bytes\n", sizeof(short));
  printf("char is %ld bytes\n", sizeof(char));
  return 0;
}
