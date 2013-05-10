#include <stdio.h>
#include <string.h>
#include "dict.h"

int main(int argc , char *argv[]) {
  //initialize dictionary
  Dict d = initDict();

  //try adding a string to the dictionary
  char *test_string = "I'm a test string ya'll";
  Entry e_string = addToDict(d, echar, "test_string", (void *)test_string);
  printf("Dict's string says: %s\n", e_string->value.str);

  //try adding an int to the dictionary
  int test_int = 42;
  int *tip = &test_int;
  Entry e_int = addToDict(d, eint, "test_int", (void *)tip);
  printf("Dict's int says: %d\n", e_int->value.num);

  //try adding a double to the dictionary
  double test_double = 42.0;
  double *tdp = &test_double;
  Entry e_double = addToDict(d, edouble, "test_double", (void *)tdp);
  printf("Dict's double says: %f\n", e_double->value.dub);

  //free the dict, which frees the entries as well
  freeDict(d);
  return 0;
}
