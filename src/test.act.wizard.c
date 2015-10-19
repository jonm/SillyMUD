#include <stdio.h>
#include <criterion/criterion.h>

void dsearch(char *, char *);

Test(act_wizard, dsearch_simple) {
  char arg[255], dst[255];
  sprintf(arg, "Someone appears!");
  dsearch(arg, dst);
  cr_assert_str_eq(dst, "Someone appears!");
}

