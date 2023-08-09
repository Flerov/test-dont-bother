#include <stdio.h>
#include <stdlib.h>
#include <string.h>


enum gen_types {
  INT,
  STR,
  FLT
};

typedef struct {
  enum gen_types type;
  union {
    int intValue;
    float floatValue;
    char* stringValue;
  };
} Variant;


#define INITINT(x) _Generic((x), int   : (x), default: 0)
#define INITSTR(x) _Generic((x), char* : (x), default: NULL)
#define INITFLT(x) _Generic((x), float : (x), default: 0)

void printIt(Variant v) {
  switch (v.type) {
    case (INT):
      printf("Integer type: %d\n", v.intValue);
      break;
    case (FLT):
      printf("Float type: %f\n", v.floatValue);
      break;
    case (STR):
      printf("String type: %s\n", v.stringValue);
      break;
    default:
      printf("Unknown tyoe\n");
      break;
  }
}

void freeVariant(Variant* v) {
  if (v->type == STR) {
    free(v->stringValue);
  }
}

#define INIT(x) \
  do { \
    _Generic((x), \
      int  : ({ Variant v = {.type = INT, .intValue = INITINT(x)}; printIt(v);}), \
      float: ({	Variant v = {.type = FLT, .floatValue = INITFLT(x)}; printIt(v);}), \
      char*: ({ Variant v = {.type = STR, .stringValue = (char*)malloc(strlen(INITSTR(x))+1)}; \
	        if (v.stringValue) strcpy(v.stringValue, INITSTR(x)); printIt(v); freeVariant(&v);}) \
    );\
  } while(0);

#define INITDYN(x) \
  do { \
    auto y = (x); \
  } while(0);

int main() {
  INIT(42);
  float x = 3.14f;
  INIT(x);
  char* y = "Hallo";
  INIT(y);

  //unsigned long long arbA = 0xffffffffff;
  //char* arbB = "TEST";
  //INITDYN(arbA);
}

