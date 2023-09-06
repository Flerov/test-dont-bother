#include <stdio.h>

typedef struct {
  char* stringValue;
} Variant;

#define INITSTR(x) _Generic((x), char*	: (x), default: NULL)
#define REST($) { printf("%s\n", $.stringValue); }
#define CONSTRUCTOR($) ( { _Generic( ($), default: ( \
  { Variant tmp = { .stringValue=(char*)malloc(strlen(INITSTR($))+1) };\
    if (tmp.stringValue) strcpy(tmp.stringValue, INITSTR($)); tmp; } )); }\
)
#define test() ( { Variant var; var = CONSTRUCTOR("W"); REST(var); var; } )

int main() {
  Variant v = test();
  printf("%s\n", v.stringValue);
}
