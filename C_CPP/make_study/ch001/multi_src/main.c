#include <stdio.h>

extern const char *msg;

int main() {
  printf("%s", msg);
  return 0;
}