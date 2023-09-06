#include <stdio.h>

enum gen_types {
  INT,
  STR,
  FLT
};
#define Variant() { printf("HEY\n"); }
#pragma push_macro("Variant")
typedef struct {
  enum gen_types type;
  //union {
  //int intValue;
  //float floatValue;
  char* stringValue;
  char charValue;
  void* pValue;
} Variant;
#pragma push_macro("Variant")

#define INITINT(x) _Generic((x), int	: (x), default: 0)
#define INITSTR(x) _Generic((x), char*	: (x), default: NULL)
#define INITFLT(x) _Generic((x), float  : (x), default: 0)
#define INITP(x) _Generic((x), void* : (x), default: 0x0)
#define INITCHAR(x) _Generic((x), char : (x), default: NULL)

 
// { Variant tmp = { .type=INT, .intValue=INITINT($), .floatValue=INITFLT($), .stringValue=(char*)malloc(strlen(INITSTR($))+1) }; \

#define CONSTRUCTOR($, V) ( { _Generic( ($), default: ( \
  { Variant tmp = { .type=INT, .charValue=INITCHAR($), .pValue=INITP($), .stringValue=(char*)malloc(strlen(INITSTR($))+1) };\
    if (tmp.stringValue) strcpy(tmp.stringValue, INITSTR($)); tmp; } )); }\
)


#define test() ( { Variant var; var = CONSTRUCTOR("W", var); var; _Pragma("pop_macro(\"Variant\")") } )

int main() {
#pragma pop_macro("Variant")
  Variant v = test();
  printf("%s\n", v.stringValue);
#pragma pop_macro("Variant")
  Variant(); // var = test();
}

