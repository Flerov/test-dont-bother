#include <stdio.h>
#include <string.h>
#pragma inline_depth(1)
#define FIRSTHANDLER(x) printf("First handler: %d\n", x)
#define SECONDHANDLER(x) printf("Second handler: %d\n", x)

#define SELECTED_FUNCTION(x) FIRSTHANDLER(x)
#pragma push_macro("SELECTED_FUNCTION")
//#pragma push_macro("SELECTED_FUNCTION")

#define PRINT(x) \
       	_Pragma("pop_macro(\"SELECTED_FUNCTION\")") \
	SELECTED_FUNCTION(x)

#define PUSH() \
       	_Pragma("push_macro(\"SELECTED_FUNCTION\")")

#define POP() \
	_Pragma("pop_macro(\"SELECTED_FUNCTION\")")
#define poison_function() \
	_Pragma("GCC poison SELECTED_FUNCTION")

//#undef SELECTED_FUNCTION
#define SELECTED_FUNCTION(x) SECONDHANDLER(x)
#pragma push_macro("SELECTED_FUNCTION")
//#undef SELECTED_FUNCTION
#define SELECTED_FUNCTION(x) \
  _Pragma("pop_macro(\"SELECTED_FUNCTION\")") \
  do { \
  printf("hiy\n"); \
  SELECTED_FUNCTION(x); \
  } while (0);
#pragma push_macro("SELECTED_FUNCTION")
#pragma push_macro("SELECTED_FUNCTION")
//#undef SELECTED_FUNCTION
#define SELECTED_FUNCTION(x) \
  do { \
  _Pragma("pop_macro(\"SELECTED_FUNCTION\")"); \
  printf("Called\n"); \
  printf("hello\n"); \
  } while (0); \
  _Pragma("push_macro(\"SELECTED_FUNCTION\")"); \
  _Pragma("push_macro(\"SELECTED_FUNCTION\")"); \
  SELECTED_FUNCTION(x); \

int main() {
  //POP();
  PUSH();
  PUSH();
  SELECTED_FUNCTION(42);
}
