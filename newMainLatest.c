#include <stdio.h>

int testOne(int a) { return 5+a; }
float* testTwo(float* a) {
  float *test = (float*)malloc(sizeof(float));
  *test = 1.4+*a;
  return test;
}
void testThree() { printf("Hello\n"); }

typedef void* func();

int main() {
  func* foo = (func*)testOne;

  func* fee = (func*)testTwo;
  float* arg = (float*)malloc(sizeof(float));
  *arg = 1.1;

  func* faa = (func*)testThree;

  printf("%d\n", foo(5)); // arb function takes int
  printf("%f\n", *(float*)fee(arg)); // arb function takes float
  faa(); // arb function takes void
}