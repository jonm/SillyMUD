#include <stdlib.h>
#include <stdio.h>
#include <criterion/criterion.h>
#include "config.h"
#include "db.h"


extern char *fread_string(FILE *f1);

FILE *create_input(const char*data) {
  FILE *fp = tmpfile();

  fwrite(data, strlen(data) + 1, 1, fp);
  rewind(fp);

  return fp;
}

Test(fread_string, tilde_terminates) {
  FILE * test_file = create_input("a string~");

  char * result = fread_string(test_file);

  cr_assert_str_eq(result, "a string");
}

Test(fread_string, cr_insertion) {
  FILE * test_file = create_input("line one\nline two~");

  char * result = fread_string(test_file);

  cr_assert_str_eq(result, "line one\n\rline two");
}

