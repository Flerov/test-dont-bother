#include <stdio.h>

#define myFunction_v1() printf("Hello from myFunction v1!\n")
#define myFunction_v2() printf("Hello from myFunction v2!\n")

#define SELECTED_FUNCTION myFunction_v1
#pragma push_macro("SELECTED_FUNCTION")
#define SELECTED_FUNCTION myFunction_v2

#define switch_function() \
	_Pragma("pop_macro(\"SELECTED_FUNCTION\")")

#define poison_function () \
	_Pragma("GCC poison SELECTED_FUNCTION")

/*
#ifdef SELECTED_FUNCTION
#undef SELECTED_FUNCTION
#define SELECTED_FUNCTION myFunction_v2
#endif
*/

int main() {
  SELECTED_FUNCTION();

  switch_function();

  SELECTED_FUNCTION();

  return 0;
}
