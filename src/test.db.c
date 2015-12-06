#include <stdlib.h>
#include <stdio.h>
#include <criterion/criterion.h>
#include "config.h"
#include "db.h"


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


#define STR_SIZE 128

Test(fread_string, tilde_terminates_na) {
  FILE * test_file = create_input("a string~");

  char result[STR_SIZE];
  fread_string_na(result, STR_SIZE, test_file);

  cr_assert_str_eq(result, "a string");
}

Test(fread_string, cr_insertion_na) {
  FILE * test_file = create_input("line one\nline two~");

  char result[STR_SIZE];
  fread_string_na(result, STR_SIZE, test_file);

  cr_assert_str_eq(result, "line one\n\rline two");
}

Test(fread_string, long_sting_na) {
  FILE * test_file = create_input("abcdefgh~");

  char result[5];
  fread_string_na(result, 5, test_file);

   /* fread_string saves two bytes at end for \0 and (presumably) a
     potential \r. */
  cr_assert_str_eq(result, "abc");
}
