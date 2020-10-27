#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
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

extern int file_to_string(char *, char *);

char *temp_dir;
char template[256];
char *temp_file;

void setup_file_to_string(void) {
  sprintf(template, "silly-test.XXXXXX");
  temp_dir = mkdtemp(template);
  if (temp_dir == NULL) {
    perror("mkdtemp");
    return;
  }
  temp_file = (char *)malloc(strlen(template) + strlen("/file.txt") + 1);
  sprintf(temp_file, "%s/file.txt", temp_dir);
}

void teardown_file_to_string(void) {
  if (unlink(temp_file) != 0) {
    perror("unlink");
  }
  free(temp_file);
  temp_file = NULL;
  if (rmdir(temp_dir) != 0) {
    perror("rmdir");
  }
  temp_dir = NULL;
  template[0] = '\0';
}

Test(file_to_string, reads_contents, .init = setup_file_to_string,
     .fini = teardown_file_to_string) {
  char buf[256];
  FILE *fp;
  int result;

  fp = fopen(temp_file, "w");
  fwrite("contents\n", sizeof(char), strlen("contents\n"), fp);
  fclose(fp);
  
  result = file_to_string(temp_file, buf);
  cr_assert(result == 0);
  cr_assert(0 == strcmp(buf, "contents\n\r"));
}

Test(file_to_string, returns_empty_string_if_cannot_open,
     .init = setup_file_to_string, .fini = teardown_file_to_string) {
  char buf[256];
  int result;

  result = file_to_string(temp_file, buf);
  cr_assert(result == -1);
  cr_assert(strlen(buf) == 0);
}

Test(file_to_string, will_not_read_a_file_thats_too_big,
     .init = setup_file_to_string, .fini = teardown_file_to_string) {
  char buf[MAX_STRING_LENGTH];
  FILE *fp;
  int result;
  int i;

  if (!(fp = fopen(temp_file, "w"))) {
    perror("fopen");
  }
  for(i=0; i<MAX_STRING_LENGTH+2; i++) {
    fputc(' ', fp);
  }
  fputc('\n', fp);
  fclose(fp);

  result = file_to_string(temp_file, buf);
  cr_assert(result == -1);
  cr_assert(strlen(buf) == 0);
}

Test(file_to_string, only_inserts_carriage_return_after_newline,
     .init = setup_file_to_string, .fini = teardown_file_to_string) {
  char buf[256];
  FILE *fp;
  int result;
  int i;
  int crs;

  fp = fopen(temp_file, "w");
  for(i=0; i<110; i++) {
    fputc(' ', fp);
  }
  fputc('\n', fp);
  fclose(fp);
  
  result = file_to_string(temp_file, buf);
  cr_assert(result == 0);
  crs = 0;
  for(i=0; i<(int)strlen(buf); i++) {
    if (buf[i] == '\r') crs++;
  }
  cr_assert(crs == 1);
}
