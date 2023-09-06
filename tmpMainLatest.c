#include <stdio.h>

typedef struct {
  char* stringValue;
  void* print;
} Variant;
int test_print(int a) { printf("Hello %d\n", a); return 42; }
#define INITSTR(x) _Generic((x), char* : (x), default: NULL)
#define REST($) { printf("%s\n", $.stringValue); }
#define CONSTRUCTOR($) ( { _Generic( ($), default: ( \
  { Variant tmp = { .print = test_print, .stringValue=(char*)malloc(strlen(INITSTR($))+1) }; \
    if (tmp.stringValue) strcpy(tmp.stringValue, INITSTR($)); tmp; } )); } \
)
#define test() ( { Variant var; var = CONSTRUCTOR("W"); REST(var); var; } )

typedef void* func(__VA_ARGS__);
int main() {
  Variant v = test();
  printf("%p\n", v.print);
  printf("%p\n", *test_print);
  func* t = (func*)v.print;
  int ret = t(5);
  printf("ret: %d\n", ret);
}
